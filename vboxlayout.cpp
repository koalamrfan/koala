#include "vboxlayout.h"
#include "layout.h"
#include "box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include "linear_box_layout_item.h"

namespace ui
{ 
VBoxLayout::VBoxLayout() {
  
}

uint32_t VBoxLayout::CalculateLimitMinWidth() {
    uint32_t width = 0;
    for (auto item:layout_items_) {
        if(item->LimitMinWidth() > width) {
            width = item->LimitMinWidth();
        }
    }
    return width;
}

uint32_t VBoxLayout::CalculateLimitMinHeight() {
    uint32_t height = 0;
    for (auto item:layout_items_) {
        height += item->LimitMinHeight();
    }
    return height;
}

uint32_t VBoxLayout::CalculateLimitMaxWidth() {
    uint32_t width = MAX_LENGTH;
    for (auto item:layout_items_) {
        if(item->LimitMaxWidth() < width) {
            width = item->LimitMaxWidth();
        }
    }
    return width;
}

uint32_t VBoxLayout::CalculateLimitMaxHeight() {
    uint32_t height = MAX_LENGTH;
    for (auto item:layout_items_) {
        if(height < MAX_LENGTH - item->LimitMaxHeight()) {
            height += item->LimitMaxHeight();
        }
    }
    return height;
}

uint32_t VBoxLayout::CalculatePreferWidth() {
    uint32_t width = 0;
    for (auto item:layout_items_) {
        if(item->PreferWidth() > width) {
            width = item->PreferWidth();
        }
    }
    return width;
}

uint32_t VBoxLayout::CalculatePreferHeight() {
    uint32_t height = 0;
    for (auto item:layout_items_) {
        height += item->PreferHeight();
    }
    return height;
}

bool VBoxLayout::IsUnderPrefer() {
    return Height() < PreferHeight();
}

void VBoxLayout::DoUnderPrefer() {
    uint32_t alloc_size = Height();
    uint32_t sum_factor = 0;

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
        sum_factor += iter->box_item->PreferHeight();
        iter++;
    }

    AllocSectionByStrechFactor(Width(), sum_factor);
}

void VBoxLayout::DoExceedPrefer() {
    uint32_t alloc_size = Height();
    uint32_t sum_factor = 0;

    bool strong = IsStrongWeakAllInNoAlloc();

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
        assert(iter->box_item);
        if(iter->box_item->StrechFactor() == 0 || (strong && !iter->box_item->IsStrongElastic())) {
            iter->section = iter->box_item->PreferHeight();
            iter->status = AllocHelper::kAlloc;
            alloc_size -= iter->section;
        } else {
            sum_factor += iter->box_item->StrechFactor();
        }
        iter++;
    }
    AllocSectionByStrechFactor(alloc_size, sum_factor);
}

void VBoxLayout::AllocHelperToBox() {
    auto iter = alloc_sections_.begin();
    int32_t pre_y = Y();
    while(iter != alloc_sections_.end()) {
        assert(iter->box_item);
        iter->box_item->CalculatePosition(X(), pre_y, Width(), iter->section);
        iter->box_item->Relayout();
        pre_y += iter->section;
        iter++;
    }
}

void VBoxLayout::AllocSectionByStrechFactor(uint32_t alloc_size, uint32_t sum_factor) {
    auto first = alloc_sections_.begin();
    while(first != alloc_sections_.end()) {
        if(first->status == AllocHelper::kNoAlloc) {
            break;
        }
        first++;
    }

    if(first != alloc_sections_.end()) {
        assert(first->box_item);
        uint32_t strech_factor = 0;
        if(IsUnderPrefer()) {
            strech_factor = first->box_item->PreferHeight();
        } else {
            strech_factor = first->box_item->StrechFactor();
        }

        bool alloc = false;
        first->section = (uint32_t)((float)alloc_size/sum_factor*strech_factor);
        if(first->section < first->box_item->LimitMinHeight()) {
            first->section = first->box_item->LimitMinHeight();
            alloc = true;
        } else if (first->section > first->box_item->LimitMaxHeight() && !IsUnderPrefer()) {
            first->section = first->box_item->LimitMaxHeight();
            alloc = true;
        } else if(first->section < first->box_item->PreferHeight() && !IsUnderPrefer()){
            first->section = first->box_item->PreferHeight();
            alloc = true;
        } else {
            first->status = AllocHelper::kTempAlloc;
            alloc = false;
        }

        uint32_t new_sum_factor = sum_factor;
        if(alloc) {
            first->status = AllocHelper::kAlloc;
            ResetTempAllocToNoAlloc();

            alloc_size = Height();
            new_sum_factor = 0;

            auto iter = alloc_sections_.begin();
            while(iter != alloc_sections_.end()) {
                if(iter->status != AllocHelper::kNoAlloc) {
                    alloc_size -= iter->section;
                } else {
                    if(IsUnderPrefer()) {
                        new_sum_factor += iter->box_item->PreferHeight();
                    } else {
                        new_sum_factor += iter->box_item->StrechFactor();
                    }
                }
                iter++;
            }
        } else {
            alloc_size -= first->section;
            new_sum_factor -= strech_factor;
        }
        AllocSectionByStrechFactor(alloc_size, new_sum_factor);
    }
}
} // namespace ui