#include "event.h"
#include "event_target.h"

namespace ui
{
Event::Event():target_(nullptr) {

}

void Event::SetTarget(EventTarget* target) {
    target_ = target;
}
} // namespace ui