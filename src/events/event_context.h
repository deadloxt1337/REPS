#pragma once
#include <string>
#include <enet/enet.h>
#include "text/scanner.h"

struct evt_ctx {
    ENetPeer* m_peer;
    ENetPacket* m_packet;  
    REPS::text::scanner* m_scanner; 
    std::string message;
    void* m_data; 
};
