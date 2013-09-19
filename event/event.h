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

class Widget;
class Event
{
public:
    Event();

    void SetTarget(Widget* target);
    Widget* Target() const {
        return target_;
    }

    virtual std::shared_ptr<Event> Clone() const = 0;
    virtual EventType Type() const = 0;
private:
    Widget* target_;

};
} // namespace ui

#endif