#include "layout.h"
#include "layout_item.h"
#include "widget.h"
#include "layout_base_item.h"
#include "app.h"
#include "layout_adapt_manager.h"
#include <cassert>


namespace ui
{
void Layout::AddItem(SharedLayoutItem item) {
    InsertItem(layout_items_.size(), item);
}

bool Layout::InsertItem(uint32_t index, SharedLayoutItem item) {
    if(index < 0) {
        index += Count();
    }
    if(index < 0 || index > Count())
        return false;
    if(FindItem(item->GetLayoutBaseItem())) {
        return false;
    }
    layout_items_.insert(layout_items_.begin()+index, item);
    if(Widget* widget = item->GetWidget()) {
        if(widget->ParentLayout()) {
            auto result = widget->ParentLayout()->RemoveWidget(widget);
            assert(result);
        }
        widget->SetParent(ParentWidget());
        widget->SetParentLayout(this);
    } else if(Layout* layout = item->GetLayout()) {
        if(layout->ParentLayout()) {
            auto result = layout->ParentLayout()->RemoveLayout(layout);
            assert(result);
        }
        layout->SetParentWidget(ParentWidget());
        layout->SetParentLayout(this);
    }
    NotifyRelayout();
    return true;
}

bool Layout::RemoveItem(LayoutBaseItem *item) {
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
        if((*iter)->GetLayoutBaseItem() == item) {
            layout_items_.erase(iter);
            NotifyRelayout();
            return true;
        }
        iter++;
    }
    NotifyRelayout();
    return false;
}

uint32_t Layout::Count() const {
    return layout_items_.size();
}

Layout::SharedLayoutItem Layout::ItemAt(uint32_t  index) {
    if (index < 0) {
        index += Count();
    }
    if (index < 0 || index > Count()) {
        return nullptr;
    }
    return layout_items_[index];
}

void Layout::AdjustSizes() {
    for(auto item:layout_items_) {
        item->AdjustSizes();
    }
    SetLimitMinWidth(CalculateLimitMinWidth());
    SetLimitMinHeight(CalculateLimitMinHeight());
    SetLimitMaxWidth(CalculateLimitMaxWidth());
    SetLimitMaxHeight(CalculateLimitMaxHeight());
    SetPreferWidth(CalculatePreferWidth());
    SetPreferHeight(CalculatePreferHeight());
}

void Layout::SetPreferWidth(uint32_t width) {
    LayoutBaseItem::SetPreferWidth(width);
}

void Layout::SetPreferHeight(uint32_t height) {
    LayoutBaseItem::SetPreferHeight(height);
}

void Layout::SetLimitMinWidth(uint32_t width) {
    LayoutBaseItem::SetLimitMinWidth(width);
}

void Layout::SetLimitMinHeight(uint32_t height) {
    LayoutBaseItem::SetLimitMinHeight(height);
}

void Layout::SetLimitMaxWidth(uint32_t width) {
    LayoutBaseItem::SetLimitMaxWidth(width);
}

void Layout::SetLimitMaxHeight(uint32_t height) {
    LayoutBaseItem::SetLimitMaxHeight(height);
}

void Layout::SetParentWidget(Widget* widget) {
    if(parent_widget_ == widget) {
        return ;
    }
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        auto item = (*iter);
        if(item->GetWidget()) {
            item->GetWidget()->SetParent(widget);
        } else if(item->GetLayout()) {
            item->GetLayout()->SetParentWidget(widget);
        }
        iter++;
    }
    parent_widget_ = widget;
}

Widget* Layout::ParentWidget() const {
    return parent_widget_;
}

void Layout::SetParentLayout(Layout* parent) {
    parent_layout_ = parent;
}

Layout* Layout::ParentLayout() const {
    return parent_layout_;
}

bool Layout::IsEmpty() {
    bool empty = true;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        if((*iter)->IsEmpty()) {
            iter++;
            continue;
        }
        empty = false;
        iter++;
    }
    return empty;
}

LayoutItem* Layout::FindItem(LayoutBaseItem *item) {
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
        LayoutBaseItem *bli = (*iter)->GetLayoutBaseItem();
        if(bli == item) {
            return iter->get();
        }
        iter++;
    }
    return nullptr;
}

SkRect Layout::GeometryToAncestor() const {
    int32_t x = X(), y= Y();
    Widget* parent = ParentWidget();
    while(parent) {
        x += parent->X();
        y += parent->Y();
        parent = parent->Parent();
    }
    return SkRect::MakeXYWH(
        SkIntToScalar(x),
        SkIntToScalar(y), 
        SkIntToScalar(Width()), 
        SkIntToScalar(Height())
        );
}
} // namespace ui