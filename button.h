#ifndef BUTTON_H_
#define BUTTON_H_


#include "layout_item.h"
#include "widget.h"
#include <QPushButton>

namespace ui
{
class Button:public Widget
{
public:
    Button() {
        SetPreferWidth(200);
        SetPreferHeight(100);
    }

    virtual void SetText(const std::string& text) {
       
    }
};
} // namespace UI

#endif