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

uint32_t HBoxLayout::CalculateLimitMinWidth() {
    uint32_t width = 0;
    for (auto item:layout_items_) {
	width += item->LimitMinWidth();
    }
    return width;
}

uint32_t HBoxLayout::CalculateLimitMinHeight() {
    uint32_t height = 0;
    for (auto item:layout_items_) {
	if(item->LimitMinHeight() > height) {
	    height = item->LimitMinHeight();
	}
    }
    return height;
}

uint32_t HBoxLayout::CalculateLimitMaxWidth() {
    uint32_t width = MAX_LENGTH;
    for (auto item:layout_items_) {
	if(width < MAX_LENGTH - item->LimitMaxWidth()) {
	    width += item->LimitMaxWidth();
	}
    }
    return width;
}

uint32_t HBoxLayout::CalculateLimitMaxHeight() {
    uint32_t height = MAX_LENGTH;
    for (auto item:layout_items_) {
	if(item->LimitMaxHeight() < height) {
	    height = item->LimitMaxHeight();
	}
    }
    return height;
}

uint32_t HBoxLayout::CalculatePreferWidth() {
    uint32_t width = 0;
    for (auto item:layout_items_) {
	width += std::max(item->LimitMinWidth(), item->PreferWidth());
    }
    return width;
}

uint32_t HBoxLayout::CalculatePreferHeight() {
    uint32_t height = 0, hign_height = 0;
    for (auto item:layout_items_) {
	hign_height = std::max(item->LimitMinHeight(), item->PreferHeight());
	if(hign_height > height) {
	    height = hign_height;
	}
    }
    return height;
}

bool HBoxLayout::IsUnderPrefer() {
    return Width() < PreferWidth();
}

void HBoxLayout::DoUnderPrefer() {
    uint32_t alloc_size = Width();
    uint32_t sum_factor = 0;

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	if(iter->box_item->LimitMinWidth() > iter->box_item->PreferWidth()) {
	    iter->section = iter->box_item->LimitMinWidth();
	    iter->status = AllocHelper::kAlloc;
	    alloc_size -= iter->section;
	} else {
	    sum_factor += iter->box_item->PreferWidth();
	}
	iter++;
    }

    iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	if(iter->status == AllocHelper::kNoAlloc) {
	    iter->section = (uint32_t)((float)alloc_size/sum_factor*iter->box_item->PreferWidth());
	}
	iter++;
    }
}

void HBoxLayout::DoExceedPrefer() {
    uint32_t alloc_size = Width();
    uint32_t sum_factor = 0;

    bool strong = IsStrongWeakAllInNoAlloc();

    auto iter = alloc_sections_.begin();
    while(iter != alloc_sections_.end()) {
	assert(iter->box_item);
	if(iter->box_item->StrechFactor() == 0 || (strong && !iter->box_item->IsStrongElastic())) {
	    if(iter->box_item->PreferWidth() < iter->box_item->LimitMinWidth()) {
	      iter->section = iter->box_item->LimitMinWidth();
	    } else if(iter->box_item->PreferWidth() > iter->box_item->LimitMaxWidth()) {
	      iter->section = iter->box_item->LimitMaxWidth();
	    } else {
	      iter->section = iter->box_item->PreferWidth();
	    }
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
    int32_t pre_x = X();
    while(iter != alloc_sections_.end()) {
	assert(iter->box_item);
	iter->box_item->CalculatePosition(pre_x, Y(), iter->section, Height()) ;
	iter->box_item->Relayout();
	pre_x += iter->section;
	iter++;
    }
}

void HBoxLayout::AllocSectionByStrechFactor(uint32_t alloc_size, uint32_t sum_factor) {
    auto first = alloc_sections_.begin();
    while(first != alloc_sections_.end()) {
	if(first->status == AllocHelper::kNoAlloc) {
	    break;
	}
	first++;
    }

    if(first != alloc_sections_.end()) {
	bool alloc = false;
	if(first->status == AllocHelper::kNoAlloc) {
	    assert(first->box_item);
	    first->section = (uint32_t)((float)alloc_size/sum_factor*first->box_item->StrechFactor());
	    if(first->section < first->box_item->LimitMinWidth()) {
		first->section = first->box_item->LimitMinWidth();
		alloc = true;
	    } else if (first->section > first->box_item->LimitMaxWidth()) {
		first->section = first->box_item->LimitMaxWidth();
		alloc = true;
	    } else if(first->section < first->box_item->PreferWidth()){
		first->section = first->box_item->PreferWidth();
		alloc = true;
	    } else {
		first->status = AllocHelper::kTempAlloc;
		alloc = false;
	    }

	    if(alloc) {
		first->status = AllocHelper::kAlloc;
		ResetTempAllocToNoAlloc();

		alloc_size = Width();
		sum_factor = 0;

		auto iter = alloc_sections_.begin();
		while(iter != alloc_sections_.end()) {
		    if(iter->status != AllocHelper::kNoAlloc) {
			alloc_size -= iter->section;
		    } else {
			sum_factor += iter->box_item->StrechFactor();
		    }
		    iter++;
		}
	    } else {
		alloc_size -= first->section;
		sum_factor -= first->box_item->StrechFactor();
	    }
	    
	    AllocSectionByStrechFactor(alloc_size, sum_factor);
	}
    }
}
} // namespace ui