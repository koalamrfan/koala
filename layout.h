#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "layout_base_item.h"
#include <vector>
#include <memory>

namespace ui
{
class Widget;
class LayoutItem;
  
class Layout:public LayoutBaseItem
{
    friend class Widget;
    friend class LayoutItem;
    
    typedef std::shared_ptr<LayoutItem> SharedLayoutItem;
public:
    virtual void AddWidget(Widget* widget) = 0;
    virtual bool InsertWidget(uint32_t index, Widget *widget) = 0;
    virtual bool RemoveWidget(Widget *widget) = 0;
    
    virtual void AddLayout(Layout* layout) = 0;
    virtual bool InsertLayout(uint32_t index, Layout *layout) = 0;
    virtual bool RemoveLayout(Layout *layout) = 0;
    
    uint32_t Count() const;

    void SetParentWidget(Widget* parent);
    Widget* ParentWidget() const;
    
    void SetParentLayout(Layout* parent);
    Layout* ParentLayout() const;
    
    virtual SkRect GeometryToAncestor() const override;
    bool IsEmpty();
    
    virtual void AdjustSizes() override;

protected:
    Layout():parent_widget_(nullptr), parent_layout_(nullptr) {}

    virtual void AddItem(SharedLayoutItem item);
    virtual bool InsertItem(uint32_t index, SharedLayoutItem item);
    virtual bool RemoveItem(LayoutBaseItem *item);
    virtual SharedLayoutItem ItemAt(uint32_t index);
    virtual LayoutItem* FindItem(LayoutBaseItem *item);

    virtual uint32_t CalculateLimitMinWidth() = 0;
    virtual uint32_t CalculateLimitMinHeight() = 0;
    virtual uint32_t CalculateLimitMaxWidth() = 0;
    virtual uint32_t CalculateLimitMaxHeight() = 0;
    virtual uint32_t CalculatePreferWidth() = 0;
    virtual uint32_t CalculatePreferHeight() = 0;

    std::vector<SharedLayoutItem> layout_items_;
private:
    Widget* parent_widget_;
    Layout* parent_layout_;
};
} // namespace ui

#endif // #ifndef LAYOUT_H