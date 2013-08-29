#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include "stdint.h"
#include "layout_base_item.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;

class LayoutItem
{
    enum ItemType
    {
      kWidget,
      kLayout,
      kLayoutSpace
    };
    
public:
    LayoutItem(Widget* widget);
    LayoutItem(Layout* layout);
    LayoutItem(LayoutSpace* layout_space);
    
    virtual ~LayoutItem() {}
public:
    virtual void Move(int32_t x, int32_t y) ;
    virtual void ReSize(uint32_t width, uint32_t height) ;
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) ;
    virtual int32_t X() ;
    virtual int32_t Y() ;
    virtual uint32_t Width() ;
    virtual uint32_t Height() ;
    virtual void SetPreferWidth(uint32_t width);
    virtual uint32_t PreferWidth();
    virtual void SetPreferHeight(uint32_t height);
    virtual uint32_t PreferHeight();
    virtual void SetLimitMinWidth(uint32_t width);
    virtual uint32_t LimitMinWidth();
    virtual void SetLimitMinHeight(uint32_t height);
    virtual uint32_t LimitMinHeight();
    virtual void SetLimitMaxWidth(uint32_t width);
    virtual uint32_t LimitMaxWidth();
    virtual void SetLimitMaxHeight(uint32_t height);
    virtual uint32_t LimitMaxHeight();

    void Relayout();

    virtual void AdjustSizes();

    virtual void UpNotifyRelayout();
    virtual void RelayoutToAdapt();

    bool IsEmpty();
public:    
    Widget* GetWidget() const;
    Layout* GetLayout() const;
    LayoutSpace* GetLayoutSpace() const;
    LayoutBaseItem* GetLayoutBaseItem() const;
private:
    LayoutBaseItem* layout_base_item_;
    ItemType type_;
};

} // namespace ui
#endif