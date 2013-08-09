#ifndef EVENT_FACTORY_H_
#define EVENT_FACTORY_H_

#include <windows.h>
#include "event.h"
#include <memory>

namespace ui
{
class EventFactory
{
public:
    static EventFactory* GetInstance();
    std::shared_ptr<Event> CreateEvent(UINT message, WPARAM wParam, LPARAM lParam);
protected:
    EventFactory() {}
};
} // namespace ui
#endif