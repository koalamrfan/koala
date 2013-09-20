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

void LinearBoxLayout::SetStrechFactor(LayoutBaseItem* item, int strech_factor) {
    LinearBoxLayoutItem *lbli = reinterpret_cast<LinearBoxLayoutItem *>(FindItem(item));
    assert(lbli);
    lbli->SetStrechFactor(strech_factor);
}

void LinearBoxLayout::SetStrongElastic(LayoutBaseItem* item) {
    LinearBoxLayoutItem *lbli = reinterpret_cast<LinearBoxLayoutItem *>(FindItem(item));
    assert(lbli);
    lbli->SetStrongElastic();
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
        if(helper.box_item->IsEmpty()) {
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

std::shared_ptr<LayoutItem> LinearBoxLayout::CreateLayoutItem() const {
    return std::make_shared<LinearBoxLayoutItem>();
}
} // namespace ui
