#ifndef BUTTON_H_
#define BUTTON_H_


#include "layout_item.h"
#include "widget.h"

namespace ui
{
class Panel:public Widget
{
public:
    Panel() {
        SetPreferWidth(200);
        SetPreferHeight(100);
    }

    virtual void OnDraw(SkCanvas* canvas) override;
    
};
} // namespace UI

#endif