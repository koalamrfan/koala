#ifndef EVENT_TARGET_H_
#define EVENT_TARGET_H_

namespace ui
{
class Event;
class EventTarget
{
public:
    virtual bool DoEvent(Event* event);
};
} // namespace ui
#endif