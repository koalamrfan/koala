#include "event_target.h"

namespace ui
{
bool EventTarget::EventTarget::DoEvent(Event* event) {
    return false;
}
} // namespace ui