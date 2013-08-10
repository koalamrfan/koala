#include "mouse_event.h"
#include "ywindow.h"
#include "app.h"
#include "event_factory.h"

namespace ui
{
MouseEvent::MouseEvent():
    x_(0),
    y_(0),
    button_(MouseButton::kNone),
    action_(MouseAction::kNone) {

}

std::vector<std::shared_ptr<Event>> MouseEvent::CreateEvent(UINT message, WPARAM wParam, LPARAM lParam) {
    std::vector<std::shared_ptr<Event>> mouse_events;
    if(message < WM_MOUSEFIRST || message > WM_MOUSELAST)
        return mouse_events;

    auto window = App::GetInstance()->GetMainWindow();
    auto pre_event = EventFactory::GetInstance()->PreEvent();
    auto mouse_event = std::make_shared<MouseEvent>();
    mouse_event->SetXY(LOWORD(lParam), HIWORD(lParam));
    auto event_target = window->HiTest(mouse_event->X(), mouse_event->Y());
    if(!event_target) {
        return mouse_events;
    }
    mouse_events.push_back(mouse_event);
    mouse_event->SetTarget(event_target);

    if(message == WM_LBUTTONDOWN) {
        mouse_event->SetButton(MouseButton::kLeftButton);
        mouse_event->SetAction(MouseAction::kPress);
    } else if(message == WM_LBUTTONUP) {
        mouse_event->SetButton(MouseButton::kLeftButton);
        mouse_event->SetAction(MouseAction::kRelease);
        if(pre_event
            && pre_event->Type() == EventType::kMouseEvent 
            && event_target == pre_event->Target()
            && ((MouseEvent *)pre_event.get())->Action() == MouseAction::kPress
            ) {
                mouse_event->SetAction(MouseAction::kClick);
        }
    } else if(message == WM_RBUTTONDOWN) {
        mouse_event->SetButton(MouseButton::kRightButton);
        mouse_event->SetAction(MouseAction::kPress);
    } else if(message == WM_RBUTTONUP) {
        mouse_event->SetButton(MouseButton::kRightButton);
        mouse_event->SetAction(MouseAction::kRelease);
        if(pre_event
            && pre_event->Type() == EventType::kMouseEvent 
            && event_target == pre_event->Target()
            && ((MouseEvent *)pre_event.get())->Action() == MouseAction::kPress
            ) {
                mouse_event->SetAction(MouseAction::kClick);
        }
    } else if(message == WM_MBUTTONDOWN) {
        mouse_event->SetButton(MouseButton::kMiddleButton);
        mouse_event->SetAction(MouseAction::kPress);
    } else if(message == WM_MBUTTONUP) {
        mouse_event->SetButton(MouseButton::kMiddleButton);
        mouse_event->SetAction(MouseAction::kRelease);
        if(pre_event
            && pre_event->Type() == EventType::kMouseEvent 
            && event_target == pre_event->Target()
            && ((MouseEvent *)pre_event.get())->Action() == MouseAction::kPress
            ) {
                mouse_event->SetAction(MouseAction::kClick);
        }
    } else if(message == WM_LBUTTONDBLCLK) {
        mouse_event->SetButton(MouseButton::kLeftButton);
        mouse_event->SetAction(MouseAction::kDClick);
    } else if(message == WM_RBUTTONDBLCLK) {
        mouse_event->SetButton(MouseButton::kRightButton);
        mouse_event->SetAction(MouseAction::kDClick);
    } else if(message == WM_MBUTTONDBLCLK) {
        mouse_event->SetButton(MouseButton::kMiddleButton);
        mouse_event->SetAction(MouseAction::kDClick);
    } else if(message == WM_MOUSEMOVE) {
        mouse_event->SetAction(MouseAction::kMove);
        if(wParam & MK_LBUTTON) {
            mouse_event->SetButton(MouseButton::kLeftButton);
        } else if(wParam & MK_RBUTTON) {
            mouse_event->SetButton(MouseButton::kRightButton);
        } else if(wParam & MK_MBUTTON) {
            mouse_event->SetButton(MouseButton::kMiddleButton);
        }

        if(pre_event
            && pre_event->Type() == EventType::kMouseEvent 
            && event_target == pre_event->Target()
            && (((MouseEvent *)pre_event.get())->Action() == MouseAction::kPress 
                || ((MouseEvent *)pre_event.get())->Action() == MouseAction::kDrag)
            && ((MouseEvent *)pre_event.get())->Button() == mouse_event->Button()) {
                mouse_event->SetAction(MouseAction::kDrag);
        } else if(pre_event
            && pre_event->Type() == EventType::kMouseEvent 
            && event_target != pre_event->Target()
            && ((MouseEvent *)pre_event.get())->Action() == MouseAction::kDrag
            && ((MouseEvent *)pre_event.get())->Button() == mouse_event->Button()) {
                mouse_event->SetAction(MouseAction::kDragOver);
        } else if(pre_event
            && pre_event->Type() == EventType::kMouseEvent 
            && event_target != pre_event->Target()
            && ((MouseEvent *)pre_event.get())->Action() == MouseAction::kMove) {
                mouse_event->SetAction(MouseAction::kCome);
                ((MouseEvent *)pre_event.get())->SetAction(MouseAction::kLeave);
                mouse_events.push_back(pre_event);
        }
    }
    return mouse_events;
}

void MouseEvent::SetXY(int32_t x, int32_t y) {
    x_ = x;
    y_ = y;
}

int32_t MouseEvent::X() {
    return x_;
}

int32_t MouseEvent::Y() {
    return y_;
}

void MouseEvent::SetButton(MouseButton button) {
    button_ = button;
}

void MouseEvent::SetAction(MouseAction action) {
    action_ = action;
}
} // namespace ui