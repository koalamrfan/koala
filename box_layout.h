#ifndef BOX_LAYOUT_H_
#define BOX_LAYOUT_H_

#include "layout.h"
#include "box_layout_item.h"

namespace ui
{
class Widget;
class Layout;
class LayoutBaseItem;
class LinearBoxLayoutItem;

class BoxLayout:public Layout
{  
public:
    BoxLayout();

    void SetWestSpace(LayoutBaseItem *item, int west_space);
    void SetNorthSpace(LayoutBaseItem *item, int north_space);
    void SetEastSpace(LayoutBaseItem *item, int east_space);
    void SetSouthSpace(LayoutBaseItem *item, int south_space);
    void SetAround(LayoutBaseItem *item, 
                   int west_space, 
                   int north_space, 
                   int east_space, 
                   int south_space);

    void SetValidGap(LayoutBaseItem *item,
                     BoxLayoutItem::GapValid gap_valid, 
                     bool valid = true);
    
    virtual void AddWidget(Widget* widget) override ;
    virtual bool InsertWidget(int index, Widget *widget) override ;
    virtual bool RemoveWidget(Widget *widget) override ;
    
    virtual void AddLayout(Layout* layout) override ;
    virtual bool InsertLayout(int index, Layout *layout) override ;
    virtual bool RemoveLayout(Layout *layout) override ;

protected:
    virtual int CalculateLimitMinWidth() override;
    virtual int CalculateLimitMinHeight() override;
    virtual int CalculateLimitMaxWidth() override;
    virtual int CalculateLimitMaxHeight() override;
    virtual int CalculatePreferWidth() override;
    virtual int CalculatePreferHeight() override;
    virtual void Relayout() override;
};

} // namespace ui

#endif // BOX_LATOUT_H_