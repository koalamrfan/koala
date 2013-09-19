#include "event_factory.h"
#include "event.h"
#include "mouse_event.h"

namespace ui
{
EventFactory* EventFactory::GetInstance() {
    static EventFactory factory;
    return &factory;
}

std::vector<std::shared_ptr<Event>> EventFactory::CreateEvent(UINT message, WPARAM wParam, LPARAM lParam) {
    std::vector<std::shared_ptr<Event>> null_events;
    switch(message) {
        case WM_MOUSEMOVE    :
        case WM_LBUTTONDOWN  :
        case WM_LBUTTONUP    :
        case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN  :
        case WM_RBUTTONUP    :
        case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN  :
        case WM_MBUTTONUP    :
        case WM_MBUTTONDBLCLK:
            auto mouse_events = MouseEvent::CreateEvent(message, wParam, lParam);
            if(!mouse_events.empty()) {
                pre_event_ = *mouse_events.rbegin();
                return mouse_events;
            } else {
                return null_events;
            }
    }
    return null_events;
}
} // namespace ui