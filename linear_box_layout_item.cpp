#include "linear_box_layout_item.h"
#include "widget.h"
#include "layout.h"
#include "layout_space.h"
#include "box_layout.h"

namespace ui
{

LinearBoxLayoutItem::LinearBoxLayoutItem(Widget* widget):
    BoxLayoutItem(widget),
    strech_factor_(1),
    strong_elastic_(false) {
}

LinearBoxLayoutItem::LinearBoxLayoutItem(Layout* layout):
    BoxLayoutItem(layout),
    strech_factor_(1),
    strong_elastic_(false) {
      
    SetAround(0, 0, 0, 0);  
}

LinearBoxLayoutItem::LinearBoxLayoutItem(LayoutSpace* layout_space):
    BoxLayoutItem(layout_space),
    strech_factor_(1),
    strong_elastic_(false){
    
    SetAround(0, 0, 0, 0);  
}

void LinearBoxLayoutItem::SetStrechFactor(uint32_t strech_factor) {
    strech_factor_ = strech_factor;
}

uint32_t LinearBoxLayoutItem::StrechFactor() const {
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