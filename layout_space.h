#ifndef LAYOUT_SPACE_H_
#define LAYOUT_SPACE_H_

#include "layout_base_item.h"

namespace ui
{

class LayoutSpace:public LayoutBaseItem
{
public:
    virtual void AdjustSizes() override {}
    virtual void UpNotifyRelayout() {}

protected:
    virtual void Relayout() override {}
};  
}

#endif