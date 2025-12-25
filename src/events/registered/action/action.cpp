#include "action.h"
#include "events/event_manager.h"
#include "utils/logger.h"
#include <string>

namespace REPS::events::registered
{
    void action(evt_ctx& ctx)
    {
        EventManager* manager = static_cast<EventManager*>(ctx.m_data);

        if (!ctx.m_scanner) {
            Logger::Warn("No scanner attached to event context!");
            return;
        }

        std::string action_name;
        if (ctx.m_scanner->try_get("action", action_name))
        {
            if (!manager->call(action_name, ctx))
            {
                Logger::Warn("Action sent by client not found: {}", action_name);
            }
            else Logger::Action("Handling action: {}", action_name);
        }
        else
        {
            Logger::Warn("Invalid data sent to server");
        }
    }
}
