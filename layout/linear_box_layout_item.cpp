#include "linear_box_layout_item.h"
#include "widget.h"
#include "layout.h"
#include "layout_space.h"
#include "box_layout.h"

namespace ui
{
LinearBoxLayoutItem::LinearBoxLayoutItem():
    strech_factor_(1),
    strong_elastic_(false) {

}

void LinearBoxLayoutItem::SetStrechFactor(int strech_factor) {
    strech_factor_ = strech_factor;
}

int LinearBoxLayoutItem::StrechFactor() const {
    return strech_factor_;
}

void LinearBoxLayoutItem::SetStrongElastic() {
    strong_elastic_ = true;
}

void LinearBoxLayoutItem::SetWeakElastic() {
    strong_elastic_ = false;
}

bool LinearBoxLayoutItem::IsStrongElastic() const {
    return strong_elastic_;
}
} // namespace ui