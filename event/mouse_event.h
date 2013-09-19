#ifndef MOUSE_EVENT_H_
#define MOUSE_EVENT_H_

#include "event.h"
#include <vector>

namespace ui
{
enum class MouseButton
{
    kNone,
    kLeftButton,
    kRightButton,
    kMiddleButton
};

enum class MouseAction
{
    // basic
    kNone,
    kPress,
    kRelease,
    kMove,
    kDClick,

    // advance
    kClick,
    kCome,
    kLeave,
    kDrag,
    kDragOver
};

class MouseEvent : public Event
{
public:
    MouseEvent();

    virtual std::shared_ptr<Event> Clone() const;

    static std::vector<std::shared_ptr<Event>> CreateEvent(UINT message, WPARAM wParam, LPARAM lParam);

    int X();
    int Y();

    void SetXY(int x, int y);

    void SetButton(MouseButton button);
    MouseButton Button() const {
        return button_;
    }

    void SetAction(MouseAction action);
    MouseAction Action() const {
        return action_;
    }

    virtual EventType Type() const override {
        return EventType::kMouseEvent;
    }

private:
    int x_;
    int y_;
    MouseButton button_;
    MouseAction action_;
};
} // namespace ui

#endif