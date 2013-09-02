#include "box_layout_item.h"
#include <algorithm>
#include <cassert>

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

void BoxLayoutItem::SetWestSpace(int west_space) {
    west_space_ = west_space;
    SetValidGap(kWestValid);
}

void BoxLayoutItem::SetNorthSpace(int north_space) {
    north_space_ = north_space;
    SetValidGap(kNorthValid);
}

void BoxLayoutItem::SetEastSpace(int east_space) {
    east_space_ = east_space;
        SetValidGap(kEastValid);
}

void BoxLayoutItem::SetSouthSpace(int south_space) {
    south_space_ = south_space;
    SetValidGap(kSouthValid);
}

void BoxLayoutItem::SetAround(int west_space, 
                   int north_space, 
                   int east_space, 
                   int south_space) {
    SetWestSpace(west_space);
    SetNorthSpace(north_space);
    SetEastSpace(east_space);
    SetSouthSpace(south_space);
}

void BoxLayoutItem::SetAroundInValid() {
    gap_valid_ = GapValid::kInValid;
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

int BoxLayoutItem::WestSpace() const {
    return west_space_;
}

int BoxLayoutItem::NorthSpace() const {
    return north_space_;
}

int BoxLayoutItem::EastSpace() const {
    return east_space_;
}

int BoxLayoutItem::SouthSpace() const {
    return south_space_;
}

int BoxLayoutItem::PreferWidth() {
    int width = 0;
    if(IsValidGap(BoxLayoutItem::kWestValid) && IsValidGap(BoxLayoutItem::kEastValid)) {
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

    if(width < LimitMinWidth()) {
        width = LimitMinWidth();
    } else if(width > LimitMaxWidth()) {
        width = LimitMaxWidth();
    }
    return width;
}

int BoxLayoutItem::PreferHeight() {
    int height = 0;
    if(IsValidGap(BoxLayoutItem::kNorthValid) && IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(LayoutItem::PreferHeight() < MAX_LENGTH - NorthSpace() - SouthSpace()) {
            height = LayoutItem::PreferHeight() + NorthSpace() + SouthSpace();
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

    if(height < LimitMinHeight()) {
        height = LimitMinHeight();
    } else if(height > LimitMaxHeight()) {
        height = LimitMaxHeight();
    }
    return height;
}

int BoxLayoutItem::LimitMinWidth() {
    if(IsEmpty()) {
        return 0;
    }

    if(LayoutItem::LimitMinWidth() == 0) {
        return 0;
    }

    int width = LayoutItem::LimitMinWidth();
    if(IsValidGap(BoxLayoutItem::kWestValid) && IsValidGap(BoxLayoutItem::kEastValid)) {
        if(LayoutItem::LimitMinWidth() < MAX_LENGTH - WestSpace() - EastSpace()) {
            width = LayoutItem::LimitMinWidth() + WestSpace() + EastSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kWestValid)){
        if(LayoutItem::LimitMinWidth() < MAX_LENGTH - WestSpace()) {
            width = LayoutItem::LimitMinWidth() + WestSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        if(LayoutItem::LimitMinWidth() < MAX_LENGTH - EastSpace()) {
            width = LayoutItem::LimitMinWidth() + EastSpace();
        }
    }
    return width;
}

int BoxLayoutItem::LimitMinHeight() {
    if(IsEmpty()) {
        return 0;
    }

    if(LayoutItem::LimitMinHeight() == 0) {
        return 0;
    }

    int height = LayoutItem::LimitMinHeight();
    if(IsValidGap(BoxLayoutItem::kNorthValid) && IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(LayoutItem::LimitMinHeight() < MAX_LENGTH - NorthSpace() - SouthSpace()) {
            height = LayoutItem::LimitMinHeight() + NorthSpace() + SouthSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)) {
        if(LayoutItem::LimitMinHeight() < MAX_LENGTH - NorthSpace()) {
            height = LayoutItem::LimitMinHeight() + NorthSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(LayoutItem::LimitMinHeight() < MAX_LENGTH - SouthSpace()) {
            height = LayoutItem::LimitMinHeight() + SouthSpace();
        }
    }
    return height;
}

int BoxLayoutItem::LimitMaxWidth() {
    if(IsEmpty()) {
        return MAX_LENGTH;
    }

    if(LayoutItem::LimitMaxWidth() == 0) {
        return 0;
    }

    int width = LayoutItem::LimitMaxWidth();
    if(IsValidGap(BoxLayoutItem::kWestValid) && IsValidGap(BoxLayoutItem::kEastValid)) {
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
    }
    return width;
}

int BoxLayoutItem::LimitMaxHeight() {
    if(IsEmpty()) {
        return MAX_LENGTH;
    }

    if(LayoutItem::LimitMaxHeight() == 0) {
        return 0;
    }

    int height = LayoutItem::LimitMaxHeight();
    if(IsValidGap(BoxLayoutItem::kNorthValid) && IsValidGap(BoxLayoutItem::kSouthValid)) {
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
    }
    return height;
}

void BoxLayoutItem::CalculatePosition(int container_x, 
                                      int container_y,
                                      int container_width, 
                                      int container_height) {
    if(container_width < LimitMinWidth()) {
        int i =0;
    }

    assert(container_width >= LimitMinWidth());
    assert(container_height >= LimitMinHeight());
    assert(container_width <= LimitMaxWidth());
    assert(container_height <= LimitMaxHeight());
    assert(LimitMinWidth() <= LimitMaxWidth());
    assert(LimitMinHeight() <= LimitMaxHeight());

    SetGeometry(CalculateX(container_x, container_width),
                CalculateY(container_y, container_height),
                CalculateWidth(container_width),
                CalculateHeight(container_height));
}

int BoxLayoutItem::CalculateX(int container_x, 
                                  int container_width) {
    int width = (std::min)(PreferWidth(), container_width);
    int x = container_x + (container_width - width)/2;
    if(IsValidGap(BoxLayoutItem::kWestValid) && IsValidGap(BoxLayoutItem::kEastValid)) {
        x = container_x + WestSpace();
    } else if(IsValidGap(BoxLayoutItem::kWestValid)) {
        x = container_x + WestSpace();
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        width = (std::min)(PreferWidth(), container_width - EastSpace());
        x = container_x + container_width - EastSpace() - width;
    }
    return x;
}

int BoxLayoutItem::CalculateY(int container_y, 
                                  int container_height) {
    int height = (std::min)(PreferHeight(), container_height);
    int y = container_y + (container_height - height)/2;
    if(IsValidGap(BoxLayoutItem::kNorthValid) && IsValidGap(BoxLayoutItem::kSouthValid)) {
        y = container_y + NorthSpace();
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)) {
        y = container_y + NorthSpace();
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        height = (std::min)(PreferHeight(), container_height - SouthSpace());
        y = container_y + container_height - SouthSpace() - height;
    }
    return y;
}

int BoxLayoutItem::CalculateWidth(int container_width) {
    int width = (std::min)(PreferWidth(), container_width);
    if(IsValidGap(BoxLayoutItem::kWestValid) && IsValidGap(BoxLayoutItem::kEastValid)) {
        if(container_width < EastSpace() + WestSpace()) {
            width = 0;
        } else {
            width = container_width - EastSpace() - WestSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kWestValid)) {
        if(container_width < WestSpace()) {
            width = 0;
        } else {
            width = (std::min)(PreferWidth(), container_width - WestSpace());
        }
    } else if(IsValidGap(BoxLayoutItem::kEastValid)) {
        if(container_width < EastSpace()) {
            width = 0;
        } else {
            width = (std::min)(PreferWidth(), container_width - EastSpace());
        }
    }
    return width;
}

int BoxLayoutItem::CalculateHeight(int container_height) {
    int height = (std::min)(PreferHeight(), container_height);
    if(IsValidGap(BoxLayoutItem::kNorthValid) && IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(container_height < NorthSpace() + SouthSpace()) {
            height = 0;
        } else {
            height = container_height - NorthSpace() - SouthSpace();
        }
    } else if(IsValidGap(BoxLayoutItem::kNorthValid)) {
        if(container_height < NorthSpace()) {
            height = 0;
        } else {
            height = (std::min)(PreferHeight(), container_height - NorthSpace());
        }
    } else if(IsValidGap(BoxLayoutItem::kSouthValid)) {
        if(container_height < SouthSpace()) {
            height = 0;
        } else {
            height = (std::min)(PreferHeight(), container_height - SouthSpace());
        }
    }
    return height;
}
} // namespace ui