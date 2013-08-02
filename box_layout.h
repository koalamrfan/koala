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
    friend class LinearBoxLayoutItem;
public:
    BoxLayout();

    void SetWestSpace(LayoutBaseItem *item, uint32_t west_space);
    void SetNorthSpace(LayoutBaseItem *item, uint32_t north_space);
    void SetEastSpace(LayoutBaseItem *item, uint32_t east_space);
    void SetSouthSpace(LayoutBaseItem *item, uint32_t south_space);
    void SetAround(LayoutBaseItem *item, 
                   uint32_t west_space, 
                   uint32_t north_space, 
                   uint32_t east_space, 
                   uint32_t south_space);

    void SetValidGap(LayoutBaseItem *item,
                     BoxLayoutItem::GapValid gap_valid, 
                     bool valid = true);
    
    virtual void AddWidget(Widget* widget) override ;
    virtual bool InsertWidget(uint32_t index, Widget *widget) override ;
    virtual bool RemoveWidget(Widget *widget) override ;
    
    virtual void AddLayout(Layout* layout) override ;
    virtual bool InsertLayout(uint32_t index, Layout *layout) override ;
    virtual bool RemoveLayout(Layout *layout) override ;

    virtual bool IsEmpty();
protected:
    virtual uint32_t CalculateLimitMinWidth() override;
    virtual uint32_t CalculateLimitMinHeight() override;
    virtual uint32_t CalculateLimitMaxWidth() override;
    virtual uint32_t CalculateLimitMaxHeight() override;
    virtual uint32_t CalculatePreferWidth() override;
    virtual uint32_t CalculatePreferHeight() override;
    virtual void Relayout() override;

    bool SkipUnVisibleWidget(BoxLayoutItem *item);
};

} // namespace ui

#endif // BOX_LATOUT_H_