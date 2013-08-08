#ifndef EVENT_H_
#define EVENT_H_

namespace ui
{
class EventTarget;
class Event
{
public:
    void SetTarget(EventTarget* target);
    EventTarget* Target() const {
        return target_;
    }
private:
    EventTarget* target_;

};
} // namespace ui

#endif