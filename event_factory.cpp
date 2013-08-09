#include "event_factory.h"
#include "event.h"

namespace ui
{
EventFactory* EventFactory::GetInstance() {
    static EventFactory factory;
    return &factory;
}

std::shared_ptr<Event> EventFactory::CreateEvent(UINT message, WPARAM wParam, LPARAM lParam) {
    switch(message) {
    case WM_LBUTTONDOWN:
        auto mouse_event = std::make_shared<MouseEvent>(LOWORD(lParam), HIWORD(lParam));
        return mouse_event;
    }
    return nullptr;
}
} // namespace ui