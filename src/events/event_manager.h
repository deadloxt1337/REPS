#pragma once
#include <unordered_map>
#include <functional>
#include <string>

struct evt_ctx;

class EventManager {
public:
    using EventFn = std::function<void(evt_ctx&)>;

    void load_event(const std::string& name, EventFn fn) {
        events[name] = fn;
    }

    bool call(const std::string& name, evt_ctx& ctx) {
        if (auto it = events.find(name); it != events.end()) {
            it->second(ctx);
            return true;
        }
        return false;
    }

private:
    std::unordered_map<std::string, EventFn> events;
};
