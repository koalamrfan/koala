#include "event.h"
#include "event_target.h"

namespace ui
{

void Event::SetTarget(EventTarget* target) {
    target_ = target;
}

} // namespace ui