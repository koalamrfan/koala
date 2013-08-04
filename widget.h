#ifndef WIDGET_H_
#define WIDGET_H_

#include <vector>
#include "layout_base_item.h"
#include "texture.h"

namespace ui
{

class Layout;
class Widget:public LayoutBaseItem, public Texture
{
public:
    Widget();
    virtual ~Widget();

    virtual void AddChild(Widget* widget);
    virtual void RemoveChild(Widget* widget);
    Widget* ChildAt(uint32_t index);
    uint32_t ChildrenNum() const;
    void SetParent(Widget* parent);
    Widget* Parent() const;
    void SetParentLayout(Layout* parent);
    Layout* ParentLayout() const;
    Layout* BaseLayout() const;
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) override;
    virtual void Show();
    virtual void Hide();
    bool IsVisible() const;
    void SetLayout(Layout* layout);
    
    virtual void ResetPreferLimitSize(bool deep = true) override;
    virtual void Relayout() override;
    
    virtual void UpNotifyRelayout() override;
    virtual void RelayoutToAdapt() override;
    
    void ResizeAdaptLimitSize();

    virtual void SetPreferWidth(uint32_t width) override;
    virtual void SetPreferHeight(uint32_t height) override;
    virtual void SetLimitMinWidth(uint32_t width) override;
    virtual void SetLimitMinHeight(uint32_t height) override;
    virtual void SetLimitMaxWidth(uint32_t width) override;
    virtual void SetLimitMaxHeight(uint32_t height) override;

    virtual void OnDraw(SkCanvas* canvas) override;
protected:
    std::vector<Widget*> children_;
    std::vector<Layout*> layer_;
    Widget* parent_;
    Layout* parent_layout_;
};
} // namespace ui

#endif