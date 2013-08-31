#ifndef LINEAR_BOX_LAYOUT_ITEM_H_
#define LINEAR_BOX_LAYOUT_ITEM_H_

#include "box_layout_item.h"
#include "stdint.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;

class LinearBoxLayoutItem:public BoxLayoutItem
{
public:
    LinearBoxLayoutItem(Widget* widget);
    LinearBoxLayoutItem(Layout* layout);
    LinearBoxLayoutItem(LayoutSpace* layout_space);
    
    void SetStrechFactor(int strech_factor);
    int StrechFactor() const;
    void SetStrongElastic();
    void SetWeakElastic();
    bool IsStrongElastic() const;
protected:
    int strech_factor_;
    bool    strong_elastic_;
};
} // namespace ui
#endif // LINEAR_BOX_LAYOUT_ITEM_H_