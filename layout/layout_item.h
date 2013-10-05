#ifndef LAYOUT_ITEM_H_
#define LAYOUT_ITEM_H_

#include "stdint.h"
#include "layout_base_item.h"
#include <memory>

namespace ui
{
class Widget;
class Layout;
class LayoutSpace;

class LayoutItem : public std::enable_shared_from_this<LayoutItem>
{
    enum ItemType
    {
      kWidget,
      kLayout,
      kLayoutSpace
    };
public:
    LayoutItem();
    virtual ~LayoutItem();
    void Init(Widget* widget);
    void Init(Layout* layout);
    void Init(LayoutSpace* layout_space);
public:
    virtual void Move(int x, int y) ;
    virtual void ReSize(int width, int height) ;
    virtual void SetGeometry(int x, int y, int width, int height) ;
    virtual int X() ;
    virtual int Y() ;
    virtual int Width() ;
    virtual int Height() ;
    virtual void SetPreferWidth(int width);
    virtual int PreferWidth();
    virtual void SetPreferHeight(int height);
    virtual int PreferHeight();
    virtual void SetLimitMinWidth(int width);
    virtual int LimitMinWidth();
    virtual void SetLimitMinHeight(int height);
    virtual int LimitMinHeight();
    virtual void SetLimitMaxWidth(int width);
    virtual int LimitMaxWidth();
    virtual void SetLimitMaxHeight(int height);
    virtual int LimitMaxHeight();

    void Relayout();

    virtual void AdjustSizes();

    virtual void UpNotifyRelayout();
    virtual void RelayoutToAdapt();

    bool IsEmpty() const;

    bool SetParentLayout(Layout* layout, int index = -1);
    Layout* ParentLayout() const;
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