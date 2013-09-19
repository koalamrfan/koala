#include "hboxlayout.h"
#include "layout.h"
#include "box_layout.h"
#include <vector>
#include <algorithm>
#include <cassert>
#include "linear_box_layout_item.h"

namespace ui
{
HBoxLayout::HBoxLayout() {

}

int HBoxLayout::CalculateLimitMinWidth() {
    int width = 0;
    for (auto item:layout_items_) {
        width += item->LimitMinWidth();
    }
    return width;
}

int HBoxLayout::CalculateLimitMinHeight() {
    int height = 0;
    for (auto item:layout_items_) {
        if(item->LimitMinHeight() > height) {
            height = item->LimitMinHeight();
        }
    }
    return height;
}

int HBoxLayout::CalculateLimitMaxWidth() {
    int width = MAX_LENGTH;
    for (auto item:layout_items_) {
        if(width < MAX_LENGTH - item->LimitMaxWidth()) {
            width += item->LimitMaxWidth();
        }
    }
    return width;
}

int HBoxLayout::CalculateLimitMaxHeight() {
    int height = MAX_LENGTH;
    for (auto item:layout_items_) {
        if(item->LimitMaxHeight() < height) {
            height = item->LimitMaxHeight();
        }
    }
    return height;
}

int HBoxLayout::CalculatePreferWidth() {
    int width = 0;
    for (auto item:layout_items_) {
        width += item->PreferWidth();
    }
    return width;
}

int HBoxLayout::CalculatePreferHeight() {
    int height = 0;
    for (auto item:layout_items_) {
        if(item->PreferHeight() > height) {
            height = item->PreferHeight();
        }
    }
    return height;
}

bool HBoxLayout::IsUnderPrefer() {
    return Width() < PreferWidth();
}

void HBoxLayout::DoUnderPrefer() {
    int alloc_size = Width();
    int sum_factor = 0;

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
        sum_factor += iter->box_item->PreferWidth();
        iter++;
    }
    AllocSectionByStrechFactor(Width(), sum_factor);
}

void HBoxLayout::DoExceedPrefer() {
    int alloc_size = Width();
    int sum_factor = 0;

    bool strong = IsStrongWeakAllInNoAlloc();

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
        assert(iter->box_item);
        if(iter->box_item->StrechFactor() == 0 || (strong && !iter->box_item->IsStrongElastic())) {
            iter->section = iter->box_item->PreferWidth();
            iter->status = AllocHelper::kAlloc;
            alloc_size -= iter->section;
        } else {
            sum_factor += iter->box_item->StrechFactor();
        }
        iter++;
    }
    AllocSectionByStrechFactor(alloc_size, sum_factor);
}

void HBoxLayout::AllocHelperToBox() {
    auto iter = alloc_sections_.begin();
    int pre_x = X();
    while(iter != alloc_sections_.end()) {
        assert(iter->box_item);
        iter->box_item->CalculatePosition(pre_x, Y(), iter->section, Height()) ;
        iter->box_item->Relayout();
        pre_x += iter->section;
        iter++;
    }
}

void HBoxLayout::AllocSectionByStrechFactor(int alloc_size, int sum_factor) {
    auto first = alloc_sections_.begin();
    while(first != alloc_sections_.end()) {
        if(first->status == AllocHelper::kNoAlloc) {
            break;
        }
        first++;
    }

    if(first != alloc_sections_.end()) {
        assert(first->box_item);

        int strech_factor = 0;
        if(IsUnderPrefer()) {
            strech_factor = first->box_item->PreferWidth();
        } else {
            strech_factor = first->box_item->StrechFactor();
        }

        bool alloc = false;
        first->section = (int)((float)alloc_size/sum_factor*strech_factor);
        if(first->section < first->box_item->LimitMinWidth()) {
            first->section = first->box_item->LimitMinWidth();
            alloc = true;
        } else if (first->section > first->box_item->LimitMaxWidth() && !IsUnderPrefer()) {
            first->section = first->box_item->LimitMaxWidth();
            alloc = true;
        } else if(first->section < first->box_item->PreferWidth() && !IsUnderPrefer()){
            first->section = first->box_item->PreferWidth();
            alloc = true;
        } else {
            first->status = AllocHelper::kTempAlloc;
            alloc = false;
        }
        int new_sum_factor = sum_factor;
        if(alloc) {
            first->status = AllocHelper::kAlloc;
            ResetTempAllocToNoAlloc();

            alloc_size = Width();
            new_sum_factor = 0;

            auto iter = alloc_sections_.begin();
            while(iter != alloc_sections_.end()) {
                if(iter->status != AllocHelper::kNoAlloc) {
                    alloc_size -= iter->section;
                } else {
                    if(IsUnderPrefer()) {
                        new_sum_factor += iter->box_item->PreferWidth();
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