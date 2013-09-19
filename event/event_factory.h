#ifndef EVENT_FACTORY_H_
#define EVENT_FACTORY_H_

#include <windows.h>
#include "event.h"
#include <memory>
#include <vector>

namespace ui
{
class EventFactory
{
public:
    static EventFactory* GetInstance();
    std::vector<std::shared_ptr<Event>> CreateEvent(UINT message, WPARAM wParam, LPARAM lParam);
    std::shared_ptr<Event> PreEvent() const {
        return pre_event_;
    }
protected:
    EventFactory() {}

private:
    std::shared_ptr<Event> pre_event_;
};
} // namespace ui
#endif