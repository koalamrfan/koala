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

void BoxLayout::SetWestSpace(LayoutBaseItem *item, int west_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetWestSpace(west_space);
}

void BoxLayout::SetNorthSpace(LayoutBaseItem *item, int north_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetNorthSpace(north_space);
}

void BoxLayout::SetEastSpace(LayoutBaseItem *item, int east_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetEastSpace(east_space);
}

void BoxLayout::SetSouthSpace(LayoutBaseItem *item, int south_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetSouthSpace(south_space);
}

void BoxLayout::SetAround(LayoutBaseItem *item, 
                          int west_space, 
                          int north_space, 
                          int east_space, 
                          int south_space) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    SetWestSpace(bli->GetLayoutBaseItem(), west_space);
    SetNorthSpace(bli->GetLayoutBaseItem(), north_space);
    SetEastSpace(bli->GetLayoutBaseItem(), east_space);
    SetSouthSpace(bli->GetLayoutBaseItem(), south_space);
}

void BoxLayout::SetAroundInValid(LayoutBaseItem *item) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetAroundInValid();
}

void BoxLayout::SetValidGap(LayoutBaseItem *item,
                            BoxLayoutItem::GapValid gap_valid, 
                            bool valid) {
    BoxLayoutItem *bli = reinterpret_cast<BoxLayoutItem *>(FindItem(item));
    assert(bli);
    bli->SetValidGap(gap_valid, valid);
}

bool BoxLayout::AddLayoutSpace(LayoutSpace* layout) {
    return false;
}

bool BoxLayout::InsertLayoutSpace(int index, LayoutSpace *layout) {
    return false;
}

bool BoxLayout::RemoveLayoutSpace(LayoutSpace *layout) {
    return false;
}

int BoxLayout::CalculateLimitMinWidth() const {
    int min_width = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(item->IsEmpty()) {
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

int BoxLayout::CalculateLimitMinHeight() const {
    int min_height = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(item->IsEmpty()) {
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

int BoxLayout::CalculateLimitMaxWidth() const {
    int max_width = MAX_LENGTH;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(item->IsEmpty()) {
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

int BoxLayout::CalculateLimitMaxHeight() const {
    int max_height = MAX_LENGTH;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(item->IsEmpty()) {
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

int BoxLayout::CalculatePreferWidth() const {
    int prefer_width = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(item->IsEmpty()) {
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

int BoxLayout::CalculatePreferHeight() const {
    int prefer_height = 0;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        BoxLayoutItem *item = reinterpret_cast<BoxLayoutItem*>(iter->get());
        if(item->IsEmpty()) {
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
        if(!item->IsEmpty()) {
            item->CalculatePosition(X(), Y(), Width(), Height());
            item->Relayout();
        }
        iter++;
    }
}

std::shared_ptr<LayoutItem> BoxLayout::CreateLayoutItem() const {
    return std::make_shared<BoxLayoutItem>();
}
} // namespace ui