#include <enet/enet.h>

#include "server/server.h"
#include "packet/packet.h"
#include "utils/logger.h"

using namespace std;

int main() {
    Logger::Info("REPS: An Open Source Growtopia Private Server!");
    REPS::Server::Initialize(17095);
    REPS::Server::HandleServer();
    return 0;
}