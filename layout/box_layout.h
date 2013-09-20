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
    void SetAroundInValid(LayoutBaseItem *item);
    void SetValidGap(LayoutBaseItem *item,
                     BoxLayoutItem::GapValid gap_valid, 
                     bool valid = true);
    virtual bool AddLayoutSpace(LayoutSpace* layout) override;
    virtual bool InsertLayoutSpace(int index, LayoutSpace *layout_space) override;
    virtual bool RemoveLayoutSpace(LayoutSpace *layout_space) override;

    virtual std::shared_ptr<LayoutItem> CreateLayoutItem() const override;
protected:
    virtual int CalculateLimitMinWidth() const override;
    virtual int CalculateLimitMinHeight() const override;
    virtual int CalculateLimitMaxWidth() const override;
    virtual int CalculateLimitMaxHeight() const override;
    virtual int CalculatePreferWidth() const override;
    virtual int CalculatePreferHeight() const override;
    virtual void Relayout() override;
};

} // namespace ui

#endif // BOX_LATOUT_H_