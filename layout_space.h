#ifndef LAYOUT_SPACE_H_
#define LAYOUT_SPACE_H_

#include "layout_base_item.h"

namespace ui
{

class LayoutSpace:public LayoutBaseItem
{
public:
    virtual void ResetPreferLimitSize(bool deep) override {}
    virtual void Relayout() override {}
    virtual void UpNotifyRelayout() {}
    virtual void RelayoutToAdapt() {}
};  
}

#endif