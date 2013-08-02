#include "layout.h"
#include "layout_item.h"
#include "widget.h"
#include "layout_base_item.h"
#include <cassert>

namespace ui
{
void Layout::AddItem(SharedLayoutItem item) {
    InsertItem(layout_items_.size(), item);
}

bool Layout::InsertItem(uint32_t index, SharedLayoutItem item) {
    if(index < 0 || index > layout_items_.size())
	return false;
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if(*iter == item) {
	    return false;
	}
	iter++;
    }
    layout_items_.insert(layout_items_.begin()+index, item);
    
    if(item->GetWidget()) {
      item->GetWidget()->SetParentLayout(this);
    } else if(item->GetLayout()) {
      item->GetLayout()->SetParentLayout(this);
    }
    return true;
}

bool Layout::RemoveItem(SharedLayoutItem item) {
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if(*iter == item) {
	    layout_items_.erase(iter);
	    return true;
	}
	iter++;
    }
    
    
    return false;
}

Layout::SharedLayoutItem Layout::ItemAt(uint32_t  index) {
    if(index < 0 || index > layout_items_.size())
	return nullptr;
    return layout_items_[index];
}

void Layout::ResetPreferLimitSize(bool deep) {
    if(deep) {
      for(auto item:layout_items_) {
	item->ResetPreferLimitSize();
      }
    }
    SetLimitMinWidth(CalculateLimitMinWidth());
    SetLimitMinHeight(CalculateLimitMinHeight());
    SetLimitMaxWidth(CalculateLimitMaxWidth());
    SetLimitMaxHeight(CalculateLimitMaxHeight());
    SetPreferWidth(CalculatePreferWidth());
    SetPreferHeight(CalculatePreferHeight());
}

void Layout::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    LayoutBaseItem::SetGeometry(x, y, width, height);
}

void Layout::Move(int32_t x, int32_t y) {
    LayoutBaseItem::Move(x, y);
}

void Layout::ReSize(uint32_t width, uint32_t height){
    LayoutBaseItem::ReSize(width, height);
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

void Layout::Empty() {
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
	auto item = (*iter);

	if(item->GetWidget()) {
	    item->GetWidget()->SetParent(nullptr);
	} else if(item->GetLayout()) {
	    item->GetLayout()->SetParentWidget(nullptr);
	    item->GetLayout()->Empty();
	}
	iter++;
    }
    layout_items_.clear();
}

bool Layout::IsEmpty() {
    return layout_items_.empty();
}

void Layout::UpNotifyRelayout() {
    if(ParentLayout()) {
      ParentLayout()->RelayoutToAdapt();
    } else if(ParentWidget()) {
      ParentWidget()->RelayoutToAdapt();
    }
}

void Layout::RelayoutToAdapt() {
    if(NeedUpNotify()) {
      UpNotifyRelayout();
    } else {
      Relayout();
    }
}

bool Layout::NeedUpNotify() {
    uint32_t prefer_width = PreferWidth();
    uint32_t prefer_height = PreferHeight();
    uint32_t limit_min_width = LimitMinWidth();
    uint32_t limit_min_height = LimitMinHeight();
    uint32_t limit_max_width = LimitMaxWidth();
    uint32_t limit_max_height = LimitMaxHeight();
    
    ResetPreferLimitSize(false);
    
    if(prefer_width != PreferWidth()) return true;
    if(prefer_height != PreferHeight()) return true;
    if(limit_min_width != LimitMinWidth()) return true;
    if(limit_min_height != LimitMinHeight()) return true;
    if(limit_max_width != LimitMaxWidth()) return true;
    if(limit_max_height != LimitMaxHeight()) return true;
    return false;
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
} // namespace ui