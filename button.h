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
        fake_widget_ = new QPushButton;
	SetPreferWidth(200);
	SetPreferHeight(100);
    }

    virtual void SetText(const std::string& text) {
        ((QPushButton *)fake_widget_)->setText(text.c_str());
    }
};
} // namespace UI

#endif