#include "enet/enet.h"
#include "packet/packet.h"
#include "utils/logger.h"
#include "events/event_manager.h"
#include "events/event_context.h"
#include "events/registered/action/action.h"
#include "text/scanner.h"

ENetHost* server;
using namespace std;

int GetMessage(ENetPacket* packet) {
    if (packet->dataLength > 3u) {
        return *(packet->data);
    }
    return 0;
}

namespace REPS {
namespace Server {

void Initialize(int port) {
    if (enet_initialize() != 0) {
        Logger::Error("An error occurred while initializing ENet");
        exit(EXIT_FAILURE);
    }

    Logger::Info("Initializing Enet Server!");

    ENetAddress address;
    enet_address_set_host(&address, "0.0.0.0");
    address.port = port;

    server = enet_host_create(&address, 128, 2, 0, 0);
    if (!server) {
        Logger::Error("An error occurred while trying to create an ENet server host");
        exit(EXIT_FAILURE);
    }

    server->checksum = enet_crc32;
    enet_host_compress_with_range_coder(server);
    enet_host_set_using_new_packet(server, 1U);

    Logger::Info("Server initialized and running on port: {}", port);
}

void HandleServer(EventManager& manager) {
    ENetEvent event;

    while (true) {
        while (enet_host_service(server, &event, 2000) > 0) { // 16
            ENetPeer* peer = event.peer;

            switch (event.type) {

            case ENET_EVENT_TYPE_CONNECT: {
                char client_ip[16];
                enet_address_get_host_ip(&peer->address, client_ip, sizeof(client_ip));
                Logger::Info("A new client connected from {}", client_ip);
                break;
            }

            case ENET_EVENT_TYPE_RECEIVE: {
                uint8_t msg_type = GetMessage(event.packet);

                std::string payload = REPS::PacketDecoder::DataToString(
                    event.packet->data + 4,
                    event.packet->dataLength - 4
                );

                if (msg_type == 2 || msg_type == 3) {
                    Logger::Info("Received a message from client: {}", payload);
                } else {
                    Logger::Debug("Other message from client: {}", payload);
                }

                evt_ctx ctx{};
                ctx.m_peer   = peer;
                ctx.m_packet = event.packet;
                ctx.m_data   = &manager;

                ctx.m_scanner = new REPS::text::scanner(payload);

                REPS::events::registered::action(ctx);

                delete ctx.m_scanner;
                enet_packet_destroy(event.packet);
                break;
            }

            case ENET_EVENT_TYPE_DISCONNECT:
                peer->data = nullptr;
                enet_peer_reset(peer);
                Logger::Info("Client disconnected");
                break;

            case ENET_EVENT_TYPE_NONE:
                break;
            }
        }
    }
}

} 
} 
