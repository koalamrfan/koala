#include "event.h"
#include "event_target.h"

namespace ui
{

void Event::SetTarget(EventTarget* target) {
    target_ = target;
}

MouseEvent::MouseEvent(int32_t x, int32_t y) {
    x_ = x;
    y_ = y;
}

int32_t MouseEvent::X() {
    return x_;
}

int32_t MouseEvent::Y() {
    return y_;
}

} // namespace ui