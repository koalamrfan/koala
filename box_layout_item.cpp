#include "box_layout_item.h"
#include <algorithm>

namespace ui
{
BoxLayoutItem::BoxLayoutItem(Widget* widget):
    LayoutItem(widget),
    west_space_(0),
    north_space_(0),
    east_space_(0),
    south_space_(0),
    gap_valid_(0) {

}
    
BoxLayoutItem::BoxLayoutItem(Layout* layout):
    LayoutItem(layout),
    west_space_(0),
    north_space_(0),
    east_space_(0),
    south_space_(0),
    gap_valid_(0) {

}

BoxLayoutItem::BoxLayoutItem(LayoutSpace* layout_space):
    LayoutItem(layout_space),
    west_space_(0),
    north_space_(0),
    east_space_(0),
    south_space_(0),
    gap_valid_(0) {

}

void BoxLayoutItem::SetWestSpace(uint32_t west_space) {
    west_space_ = west_space;
    SetValidGap(kWestValid);
}

void BoxLayoutItem::SetNorthSpace(uint32_t north_space) {
    north_space_ = north_space;
    SetValidGap(kNorthValid);
}

void BoxLayoutItem::SetEastSpace(uint32_t east_space) {
    east_space_ = east_space;
        SetValidGap(kEastValid);
}

void BoxLayoutItem::SetSouthSpace(uint32_t south_space) {
    south_space_ = south_space;
    SetValidGap(kSouthValid);
}

void BoxLayoutItem::SetAround(uint32_t west_space, 
                   uint32_t north_space, 
                   uint32_t east_space, 
                   uint32_t south_space) {
    SetWestSpace(west_space);
    SetNorthSpace(north_space);
    SetEastSpace(east_space);
    SetSouthSpace(south_space);
}

void BoxLayoutItem::SetValidGap(GapValid gap_valid, bool valid) {
    if(valid) {
        gap_valid_ |= gap_valid;
    } else {
        gap_valid_ &= ~gap_valid;
    }
}

bool BoxLayoutItem::IsValidGap(GapValid gap_valid) const {
    return (gap_valid_ & gap_valid) == gap_valid;
}

uint32_t BoxLayoutItem::WestSpace() const {
    return west_space_;
}

uint32_t BoxLayoutItem::NorthSpace() const {
    return north_space_;
}

uint32_t BoxLayoutItem::EastSpace() const {
    return east_space_;
}

uint32_t BoxLayoutItem::SouthSpace() const {
    return south_space_;
}

uint32_t BoxLayoutItem::PreferWidth() {
    uint32_t width = 0;
    if(IsValidGap(BoxLayoutItem::kWestValid) && !IsValidGap(BoxLayoutItem::kEastValid)) {
        if(LayoutItem::PreferWidth() < MAX_LENGTH - EastSpace() - WestSpace()) {
            width = LayoutItem::PreferWidth() + EastSpace() + WestSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kWestValid)){
        if(LayoutItem::PreferWidth() < MAX_LENGTH - WestSpace()) {
            width = LayoutItem::PreferWidth() + WestSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        if(LayoutItem::PreferWidth() < MAX_LENGTH - EastSpace()) {
            width = LayoutItem::PreferWidth() + EastSpace();
        }
    } else {
        width = LayoutItem::PreferWidth();
    }
    return width;
}

uint32_t BoxLayoutItem::PreferHeight() {
    uint32_t height = 0;
    if(IsValidGap(BoxLayoutItem::kNorthValid) && !IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(LayoutItem::PreferHeight() < MAX_LENGTH - NorthSpace() - EastSpace()) {
            height = LayoutItem::PreferHeight() + NorthSpace() + EastSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)){
        if(LayoutItem::PreferHeight() < MAX_LENGTH - NorthSpace()) {
            height = LayoutItem::PreferHeight() + NorthSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(LayoutItem::PreferHeight() < MAX_LENGTH - SouthSpace()) {
            height = LayoutItem::PreferHeight() + SouthSpace();
        }
    } else {
        height = LayoutItem::PreferHeight();
    }
    return height;
}

uint32_t BoxLayoutItem::LimitMinWidth() {
    uint32_t width = 0;
    if(IsValidGap(BoxLayoutItem::kWestValid) && !IsValidGap(BoxLayoutItem::kEastValid)) {
        width = LayoutItem::LimitMinWidth() + WestSpace() + EastSpace();
    } else if(IsValidGap(BoxLayoutItem::kWestValid)){
        width = LayoutItem::LimitMinWidth() + WestSpace();
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        width = LayoutItem::LimitMinWidth() + EastSpace();
    } else {
        width = LayoutItem::LimitMinWidth();
    }
    return width;
}

uint32_t BoxLayoutItem::LimitMinHeight() {
    uint32_t height = 0;
    if(IsValidGap(BoxLayoutItem::kNorthValid) && !IsValidGap(BoxLayoutItem::kSouthValid)) {
        height = LayoutItem::LimitMinHeight() + NorthSpace() + SouthSpace();
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)) {
        height = LayoutItem::LimitMinHeight() + NorthSpace();
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        height = LayoutItem::LimitMinHeight() + SouthSpace();
    } else {
        height = LayoutItem::LimitMinHeight();
    }
    return height;
}

uint32_t BoxLayoutItem::LimitMaxWidth() {
    uint32_t width = MAX_LENGTH;
    if(IsValidGap(BoxLayoutItem::kWestValid) && !IsValidGap(BoxLayoutItem::kEastValid)) {
        if(LayoutItem::LimitMaxWidth() < MAX_LENGTH - EastSpace() - WestSpace()) {
            width = LayoutItem::LimitMaxWidth() + EastSpace() + WestSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kWestValid)){
        if(LayoutItem::LimitMaxWidth() < MAX_LENGTH - WestSpace()) {
            width = LayoutItem::LimitMaxWidth() + WestSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        if(LayoutItem::LimitMaxWidth() < MAX_LENGTH - EastSpace()) {
            width = LayoutItem::LimitMaxWidth() + EastSpace();
        }
    } else {
        width = LayoutItem::LimitMaxWidth();
    }
    return width;
}

uint32_t BoxLayoutItem::LimitMaxHeight() {
    uint32_t height = MAX_LENGTH;
    if(IsValidGap(BoxLayoutItem::kNorthValid) && !IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(LayoutItem::LimitMaxHeight() < MAX_LENGTH - NorthSpace() - SouthSpace()) {
            height = LayoutItem::LimitMaxHeight() + NorthSpace() + SouthSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)){
        if(LayoutItem::LimitMaxHeight() < MAX_LENGTH - NorthSpace()) {
            height = LayoutItem::LimitMaxHeight() + NorthSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(LayoutItem::LimitMaxHeight() < MAX_LENGTH - SouthSpace()) {
            height = LayoutItem::LimitMaxHeight() + SouthSpace();
        }
    } else {
        height = LayoutItem::LimitMaxHeight();
    }
    return height;
}

void BoxLayoutItem::CalculatePosition(int32_t container_x, 
                                      int32_t container_y,
                                      uint32_t container_width, 
                                      uint32_t container_height) {
    SetGeometry(CalculateX(container_x, container_width),
    CalculateY(container_y, container_height),
    CalculateWidth(container_width),
    CalculateHeight(container_height));
}

int32_t BoxLayoutItem::CalculateX(int32_t container_x, 
                                  uint32_t container_width) {
    uint32_t width = (std::min)(GetSuitWidth(), container_width);
    int32_t x = container_x + (container_width - width)/2;
    if(IsValidGap(BoxLayoutItem::kWestValid) && IsValidGap(BoxLayoutItem::kEastValid)) {
        x = container_x + WestSpace();
    } else if(IsValidGap(BoxLayoutItem::kWestValid)) {
        x = container_x + WestSpace();
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        width = (std::min)(GetSuitWidth(), container_width - EastSpace());
        x = container_x + container_width - EastSpace() - width;
    }
    return x;
}

int32_t BoxLayoutItem::CalculateY(int32_t container_y, 
                                  uint32_t container_height) {
    uint32_t height = (std::min)(GetSuitHeight(), container_height);
    int32_t y = container_y + (container_height - height)/2;
    if(IsValidGap(BoxLayoutItem::kNorthValid) && IsValidGap(BoxLayoutItem::kSouthValid)) {
        y = container_y + NorthSpace();
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)) {
        y = container_y + NorthSpace();
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        height = (std::min)(GetSuitHeight(), container_height - SouthSpace());
        y = container_y + container_height - SouthSpace() - height;
    }
    return y;
}

uint32_t BoxLayoutItem::CalculateWidth(uint32_t container_width) {
    uint32_t width = (std::min)(GetSuitWidth(), container_width);
    if(IsValidGap(BoxLayoutItem::kWestValid) && IsValidGap(BoxLayoutItem::kEastValid)) {
        width = container_width - EastSpace() - WestSpace();
    } else if(IsValidGap(BoxLayoutItem::kWestValid)) {
        width = (std::min)(GetSuitWidth(), container_width - WestSpace());
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        width = (std::min)(GetSuitWidth(), container_width - EastSpace());
    }
    return (std::max)((uint32_t)0, width);
}

uint32_t BoxLayoutItem::CalculateHeight(uint32_t container_height) {
    uint32_t height = (std::min)(GetSuitHeight(), container_height);
    if(IsValidGap(BoxLayoutItem::kNorthValid) && IsValidGap(BoxLayoutItem::kSouthValid)) {
        height = container_height - NorthSpace() - SouthSpace();
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)) {
        height = (std::min)(GetSuitHeight(), container_height - NorthSpace());
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        height = (std::min)(GetSuitHeight(), container_height - SouthSpace());
    }
    return (std::max)((uint32_t)0, height);
}

uint32_t BoxLayoutItem::GetSuitWidth() {
    if(PreferWidth() < LimitMinWidth()) {
        return LimitMinWidth();
    } else if(PreferWidth() > LimitMaxWidth()) {
        return LimitMaxWidth();
    }
    return PreferWidth();
}

uint32_t BoxLayoutItem::GetSuitHeight() {
    if(PreferHeight() < LimitMinHeight()) {
        return LimitMinHeight();
    } else if(PreferHeight() > LimitMaxHeight()) {
        return LimitMaxHeight();
    }
    return PreferHeight();
}
} // namespace ui