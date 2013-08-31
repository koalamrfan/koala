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

    auto pre_event = EventFactory::GetInstance()->PreEvent();
    auto mouse_event = std::make_shared<MouseEvent>();
    mouse_event->SetXY(LOWORD(lParam), HIWORD(lParam));
    auto event_target = App::MainWindowHitest(mouse_event->X(), mouse_event->Y());
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
        mouse_events.push_back(mouse_event);
        if(pre_event
            && pre_event->Type() == EventType::kMouseEvent 
            && event_target == pre_event->Target()
            && ((MouseEvent *)pre_event.get())->Action() == MouseAction::kPress
            ) {
                auto cp_mouse_event = std::static_pointer_cast<MouseEvent>(mouse_event->Clone());
                cp_mouse_event->SetAction(MouseAction::kClick);
                mouse_events.push_back(cp_mouse_event);
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

void MouseEvent::SetXY(int x, int y) {
    x_ = x;
    y_ = y;
}

int MouseEvent::X() {
    return x_;
}

int MouseEvent::Y() {
    return y_;
}

void MouseEvent::SetButton(MouseButton button) {
    button_ = button;
}

void MouseEvent::SetAction(MouseAction action) {
    action_ = action;
}

std::shared_ptr<Event> MouseEvent::Clone() const{
    auto event = std::make_shared<MouseEvent>();
    event->SetXY(x_, y_);
    event->SetButton(button_);
    event->SetAction(action_);
    event->SetTarget(Target());
    return event;
}
} // namespace ui