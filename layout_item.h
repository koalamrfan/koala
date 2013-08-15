#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include "stdint.h"
#include "layout_base_item.h"

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;

class LayoutItem : public LayoutBaseItem
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
    virtual void Move(int32_t x, int32_t y) override ;
    virtual void ReSize(uint32_t width, uint32_t height) override ;
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) override ;
    virtual int32_t X() override ;
    virtual int32_t Y() override ;
    virtual uint32_t Width() override ;
    virtual uint32_t Height() override ;
    virtual void SetPreferWidth(uint32_t width) override ;
    virtual uint32_t PreferWidth() override ;
    virtual void SetPreferHeight(uint32_t height) override ;
    virtual uint32_t PreferHeight() override ;
    virtual void SetLimitMinWidth(uint32_t width) override ;
    virtual uint32_t LimitMinWidth() override ;
    virtual void SetLimitMinHeight(uint32_t height) override ;
    virtual uint32_t LimitMinHeight() override ;
    virtual void SetLimitMaxWidth(uint32_t width) override ;
    virtual uint32_t LimitMaxWidth() override ;
    virtual void SetLimitMaxHeight(uint32_t height) override ;
    virtual uint32_t LimitMaxHeight() override ;

    virtual void Relayout()  override ;
    virtual void ResetPreferLimitSize(bool deep)  override ;

    virtual void UpNotifyRelayout() override;
    virtual void RelayoutToAdapt() override;
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