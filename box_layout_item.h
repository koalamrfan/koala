#ifndef BOX_LAYOUT_ITEM_H_
#define BOX_LAYOUT_ITEM_H_

#include "layout_item.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;

class BoxLayoutItem:public LayoutItem
{
public:
    BoxLayoutItem(Widget* widget);
    BoxLayoutItem(Layout* layout);
    BoxLayoutItem(LayoutSpace* layout_space);

    enum GapValid {
        kInValid   =  0,
        kWestValid =  1,
        kNorthValid = 2,
        kEastValid =  4,
        kSouthValid = 8
    };

    void SetWestSpace(uint32_t west_space);
    void SetNorthSpace(uint32_t north_space);
    void SetEastSpace(uint32_t east_space);
    void SetSouthSpace(uint32_t south_space);
    void SetAround(uint32_t west_space, 
                   uint32_t north_space, 
                   uint32_t east_space, 
                   uint32_t south_space);
    
    void SetValidGap(GapValid gap_valid, bool valid = true);
    bool IsValidGap(GapValid gap_valid) const;

    uint32_t WestSpace() const;
    uint32_t NorthSpace() const;
    uint32_t EastSpace() const;
    uint32_t SouthSpace() const;
    
    virtual uint32_t PreferWidth() override ;
    virtual uint32_t PreferHeight() override ;
    virtual uint32_t LimitMinWidth() override ;
    virtual uint32_t LimitMinHeight() override ;
    virtual uint32_t LimitMaxWidth() override ;
    virtual uint32_t LimitMaxHeight() override ;
    
    void CalculatePosition(int32_t container_x, 
		      int32_t container_y,
		      uint32_t container_width, 
		      uint32_t container_height);
protected:
    int32_t CalculateX(int32_t container_x, 
		    uint32_t container_width);
    int32_t CalculateY(int32_t container_y, 
		    uint32_t container_height);
    uint32_t CalculateWidth(uint32_t container_width);
    uint32_t CalculateHeight(uint32_t container_height);
private:
    uint32_t west_space_;
    uint32_t north_space_;
    uint32_t east_space_;
    uint32_t south_space_;
    uint16_t gap_valid_;
};

} // namespace ui
#endif