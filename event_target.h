#ifndef EVENT_TARGET_H_
#define EVENT_TARGET_H_

namespace ui
{
class Event;
class EventTarget
{
public:
    EventTarget();

    virtual bool DoEvent(Event* event);

    void SetIgnoreHitest(bool ignore_hitest = true) {
        ignore_hitest_ = ignore_hitest;
    }

    bool IgnoreHitTest() const {
        return ignore_hitest_;
    }
private:
    bool ignore_hitest_;
};
} // namespace ui
#endif