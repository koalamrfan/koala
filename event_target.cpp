#include "event_target.h"

namespace ui
{
EventTarget::EventTarget():ignore_hitest_(false) {

}

bool EventTarget::DoEvent(Event* event) {
    return false;
}
} // namespace ui