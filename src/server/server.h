#include <enet/enet.h>
#include "events/event_manager.h"

namespace REPS {
    namespace Server {
        void Initialize(int port);
        void HandleServer(EventManager& manager);
    }
}
