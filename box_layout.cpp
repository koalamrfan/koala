#include "box_layout.h"
#include "widget.h"
#include "layout.h"
#include "box_layout_item.h"
#include <algorithm>
#include <cassert>
#include <memory>
#include "linear_box_layout_item.h"

namespace ui
{
BoxLayout::BoxLayout() {

}

void BoxLayout::SetWestSpace(LayoutBaseItem *item, uint32_t west_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetWestSpace(west_space);
}

void BoxLayout::SetNorthSpace(LayoutBaseItem *item, uint32_t north_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetNorthSpace(north_space);
}

void BoxLayout::SetEastSpace(LayoutBaseItem *item, uint32_t east_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetEastSpace(east_space);
}

void BoxLayout::SetSouthSpace(LayoutBaseItem *item, uint32_t south_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetSouthSpace(south_space);
}

void BoxLayout::SetAround(LayoutBaseItem *item, 
                          uint32_t west_space, 
                          uint32_t north_space, 
                          uint32_t east_space, 
                          uint32_t south_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    SetWestSpace(bli->GetLayoutBaseItem(), west_space);
    SetNorthSpace(bli->GetLayoutBaseItem(), north_space);
    SetEastSpace(bli->GetLayoutBaseItem(), east_space);
    SetSouthSpace(bli->GetLayoutBaseItem(), south_space);
}

void BoxLayout::SetValidGap(LayoutBaseItem *item,
                            BoxLayoutItem::GapValid gap_valid, 
                            bool valid) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetValidGap(gap_valid, valid);
}

void BoxLayout::AddWidget(Widget* widget) {
    Layout::AddItem(std::make_shared<BoxLayoutItem>(widget));
}

bool BoxLayout::InsertWidget(uint32_t index, Widget *widget) {
    return Layout::InsertItem(index, std::make_shared<BoxLayoutItem>(widget));
}

bool BoxLayout::RemoveWidget(Widget *widget) {
    widget->SetParent(nullptr);
    return Layout::RemoveItem(widget);
}
    
void BoxLayout::AddLayout(Layout* layout) {
    Layout::AddItem(std::make_shared<BoxLayoutItem>(layout));
}

bool BoxLayout::InsertLayout(uint32_t index, Layout *layout) {
    return Layout::InsertItem(index, std::make_shared<BoxLayoutItem>(layout));
}

bool BoxLayout::RemoveLayout(Layout *layout) {
    layout->SetParentWidget(nullptr);
    return Layout::RemoveItem(layout);
}

bool BoxLayout::SkipUnVisibleWidget(BoxLayoutItem *item) {
    if(item->GetWidget() && !item->GetWidget()->IsVisible()) {
        return true;
    }
    return false;
}

uint32_t BoxLayout::CalculateLimitMinWidth() {
    uint32_t min_width = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }
        if(item->LimitMinWidth() > min_width) {
            min_width = item->LimitMinWidth();
        }
        iter++;
    }
    return min_width;
}

uint32_t BoxLayout::CalculateLimitMinHeight() {
    uint32_t min_height = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }
        if(item->LimitMinHeight() > min_height) {
            min_height = item->LimitMinHeight();
        }
        iter++;
    }
    return min_height;
}

uint32_t BoxLayout::CalculateLimitMaxWidth() {
    uint32_t max_width = MAX_LENGTH;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }
        if(item->LimitMaxWidth() < max_width) {
            max_width = item->LimitMaxWidth();
        }
        iter++;
    }
    return max_width;
}

uint32_t BoxLayout::CalculateLimitMaxHeight() {
    uint32_t max_height = MAX_LENGTH;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }
        if(item->LimitMaxHeight() < max_height) {
            max_height = item->LimitMaxHeight();
        }
        iter++;
    }
    return max_height;
}

uint32_t BoxLayout::CalculatePreferWidth() {
    uint32_t prefer_width = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }
        if(item->PreferWidth() > prefer_width) {
            prefer_width = item->PreferWidth();
        }
        iter++;
    }
    return prefer_width;
}

uint32_t BoxLayout::CalculatePreferHeight() {
    uint32_t prefer_height = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }
        if(item->PreferHeight() > prefer_height) {
            prefer_height = item->PreferHeight();
        }

        iter++;
    }
    return prefer_height;
}

void BoxLayout::Relayout() {
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }
        item->CalculatePosition(X(), Y(), Width(), Height());
        item->Relayout();
        iter++;
    }
}

bool BoxLayout::IsEmpty() {
    bool empty = true;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(SkipUnVisibleWidget(item)) {
            iter++;
            continue;
        }

        empty = false;
        iter++;
    }
    return empty;
}
} // namespace ui