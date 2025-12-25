#include <enet/enet.h>

#include "server/server.h"
#include "packet/packet.h"
#include "utils/logger.h"
#include "text/scanner.h"
#include "events/event_manager.h"

#include "events/registered/action/quit/quit.h"

using namespace std;

int main() {
    Logger::Info("REPS: An Open Source Growtopia Private Server!");

    EventManager event_manager;
    event_manager.load_event("quit", REPS::events::registered::quit);

    REPS::Server::Initialize(17095);
    REPS::Server::HandleServer(event_manager);
    return 0;
}