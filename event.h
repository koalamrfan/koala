#ifndef EVENT_H_
#define EVENT_H_

#include <stdint.h>

namespace ui
{
enum class EventType
{
    kNoneEvent,
    kMouseEvent
};

class EventTarget;
class Event
{
public:
    void SetTarget(EventTarget* target);
    EventTarget* Target() const {
        return target_;
    }

    virtual EventType Type() const = 0;
private:
    EventTarget* target_;

};

class MouseEvent : public Event
{
public:
    MouseEvent(int32_t x, int32_t y);

    int32_t X();
    int32_t Y();

    virtual EventType Type() const override {
        return EventType::kMouseEvent;
    }
private:
    int32_t x_;
    int32_t y_;
};

} // namespace ui

#endif