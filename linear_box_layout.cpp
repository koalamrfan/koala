#include "linear_box_layout.h"
#include "linear_box_layout_item.h"
#include "box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include <memory>
#include "widget.h"
#include "layout_space.h"

namespace ui
{
LinearBoxLayout::LinearBoxLayout() {
  
}

void LinearBoxLayout::SetStrechFactor(LayoutBaseItem* item, uint32_t strech_factor) {
    LinearBoxLayoutItem *lbli = reinterpret_cast<LinearBoxLayoutItem *>(FindItem(item));
    assert(lbli);
    lbli->SetStrechFactor(strech_factor);
}

void LinearBoxLayout::SetStrongElastic(LayoutBaseItem* item) {
    LinearBoxLayoutItem *lbli = reinterpret_cast<LinearBoxLayoutItem *>(FindItem(item));
    assert(lbli);
    lbli->SetStrongElastic();
}

void LinearBoxLayout::SetWeakElastic(LayoutBaseItem* item) {
    LinearBoxLayoutItem *lbli = reinterpret_cast<LinearBoxLayoutItem *>(FindItem(item));
    assert(lbli);
    lbli->SetWeakElastic();
}

void LinearBoxLayout::AddWidget(Widget* widget) {
    Widget* parent = ParentWidget();
    assert(parent);
    parent->AddChild(widget);
    Layout::AddItem(std::make_shared<LinearBoxLayoutItem>(widget));
}

bool LinearBoxLayout::InsertWidget(uint32_t index, Widget *widget) {
    Widget* parent = ParentWidget();
    assert(parent);
    parent->AddChild(widget);
    return Layout::InsertItem(index, std::make_shared<LinearBoxLayoutItem>(widget));
}
void SetStrechFactor(LayoutBaseItem* item, uint32_t strech_factor);
    void SetStrongElastic(LayoutBaseItem* item);
    void SetWeakElastic(LayoutBaseItem* item);
bool LinearBoxLayout::RemoveWidget(Widget *widget) {
    Widget* parent = ParentWidget();
    assert(parent);
    parent->RemoveChild(widget);
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if((*iter)->GetWidget() == widget) {
	    layout_items_.erase(iter);
	    return true;
	}
	iter++;
    }
    return false;
}
    
void LinearBoxLayout::AddLayout(Layout* layout) {
    Widget* parent = ParentWidget();
    assert(parent);
    layout->SetParentWidget(parent);
    Layout::AddItem(std::make_shared<LinearBoxLayoutItem>(layout));
}

bool LinearBoxLayout::InsertLayout(uint32_t index, Layout *layout) {
    Widget* parent = ParentWidget();
    assert(parent);
    layout->SetParentWidget(parent);
    return Layout::InsertItem(index, std::make_shared<LinearBoxLayoutItem>(layout));
}

bool LinearBoxLayout::RemoveLayout(Layout *layout) {
    layout->SetParentWidget(nullptr);
    layout->Empty();
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if((*iter)->GetLayout() == layout) {
	    layout_items_.erase(iter);
	    return true;
	}
	iter++;
    }
    return false;
}

void LinearBoxLayout::AddSpace(LayoutSpace* space) {
    Layout::AddItem(std::make_shared<LinearBoxLayoutItem>(space));
}

bool LinearBoxLayout::InsertSpace(uint32_t index, LayoutSpace *space) {
    return Layout::InsertItem(index, std::make_shared<LinearBoxLayoutItem>(space));
}

bool LinearBoxLayout::RemoveSpace(LayoutSpace *space) {
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
	if((*iter)->GetLayoutSpace() == space) {
	    layout_items_.erase(iter);
	    return true;
	}
	iter++;
    }
    return false;
}

LinearBoxLayout::~LinearBoxLayout() {
    
}

void LinearBoxLayout::Relayout() {
    BoxToAllocHelper();
    if(IsUnderPrefer()) {
	DoUnderPrefer();
    } else {
	DoExceedPrefer();
    }
    AllocHelperToBox();
}

void LinearBoxLayout::BoxToAllocHelper() {
    alloc_sections_.clear();
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
	AllocHelper helper;
	helper.box_item = reinterpret_cast<LinearBoxLayoutItem *>(iter->get());
	if(SkipUnVisibleWidget(helper.box_item)) {
	  iter++;
	  continue;
	}
	alloc_sections_.push_back(helper);
	iter++;
    }
}

bool LinearBoxLayout::IsStrongWeakAllInNoAlloc() {
    bool has_strong = false;
    bool has_weak   = false;

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	if(iter->status == AllocHelper::kNoAlloc) {
	    if(iter->box_item->IsStrongElastic()) {
		has_strong = true;
	    } else {
		has_weak = true;
	    }
	} 
	iter++;
    }

    if(has_strong && has_weak) {
	return true;
    }

    return false;
}

void LinearBoxLayout::ResetTempAllocToNoAlloc() {
    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	if(iter->status == AllocHelper::kTempAlloc) {
	    iter->status = AllocHelper::kNoAlloc;
	}
	iter++;
    }
}
} // namespace ui
