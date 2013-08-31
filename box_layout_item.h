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

    void SetWestSpace(int west_space);
    void SetNorthSpace(int north_space);
    void SetEastSpace(int east_space);
    void SetSouthSpace(int south_space);
    void SetAround(int west_space, 
                   int north_space, 
                   int east_space, 
                   int south_space);
    
    void SetValidGap(GapValid gap_valid, bool valid = true);
    bool IsValidGap(GapValid gap_valid) const;

    int WestSpace() const;
    int NorthSpace() const;
    int EastSpace() const;
    int SouthSpace() const;
    
    virtual int PreferWidth() override ;
    virtual int PreferHeight() override ;
    virtual int LimitMinWidth() override ;
    virtual int LimitMinHeight() override ;
    virtual int LimitMaxWidth() override ;
    virtual int LimitMaxHeight() override ;
    
    void CalculatePosition(int container_x, 
                           int container_y,
                           int container_width, 
                           int container_height);
protected:
    int CalculateX(int container_x, int container_width);
    int CalculateY(int container_y, int container_height);
    int CalculateWidth(int container_width);
    int CalculateHeight(int container_height);
private:
    int west_space_;
    int north_space_;
    int east_space_;
    int south_space_;
    int gap_valid_;
};

} // namespace ui
#endif