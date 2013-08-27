#include "event.h"

namespace ui
{
Event::Event():target_(nullptr) {

}

void Event::SetTarget(Widget* target) {
    target_ = target;
}
} // namespace ui