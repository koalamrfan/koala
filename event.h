#ifndef EVENT_H_
#define EVENT_H_

#include <windows.h>
#include <stdint.h>
#include <memory>
#include <vector>

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
} // namespace ui

#endif