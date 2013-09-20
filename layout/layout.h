#ifndef LAYOUT_H_
#define LAYOUT_H_

#include "layout_base_item.h"
#include <vector>
#include <memory>

namespace ui
{
class Widget;
class LayoutSpace;
class LayoutItem;
class Layout : public LayoutBaseItem
{
    friend class Widget;
    friend class LayoutItem;
public:
    virtual bool AddWidget(Widget* widget) = 0;
    virtual bool InsertWidget(int index, Widget *widget) = 0;
    virtual bool RemoveWidget(Widget *widget) = 0;
    
    virtual bool AddLayout(Layout* layout) = 0;
    virtual bool InsertLayout(int index, Layout *layout) = 0;
    virtual bool RemoveLayout(Layout *layout) = 0;

    virtual bool AddLayoutSpace(LayoutSpace* layout) = 0;
    virtual bool InsertLayoutSpace(int index, LayoutSpace *layout) = 0;
    virtual bool RemoveLayoutSpace(LayoutSpace *layout) = 0;
    
    int Count() const;

    Widget* ParentWidget() const;
    Layout* ParentLayout() const;
    
    virtual SkRect GeometryToAncestor() const override;
    bool IsEmpty() const;
    
    virtual void AdjustSizes() override;

    virtual std::shared_ptr<LayoutItem> CreateLayoutItem() const = 0;
protected:
    Layout():parent_widget_(nullptr), parent_layout_(nullptr) {}

    // layout_item operator
    bool AddItem(std::shared_ptr<LayoutItem> item);
    bool InsertItem(int index, std::shared_ptr<LayoutItem> item);
    bool RemoveItem(LayoutBaseItem *item);
    LayoutItem* ItemAt(int index) const;
    LayoutItem* FindItem(LayoutBaseItem *item) const;

    void SetParentWidget(Widget* parent);
    bool SetParentLayout(Layout* parent, int index = -1);

    virtual int CalculateLimitMinWidth() const = 0;
    virtual int CalculateLimitMinHeight() const = 0;
    virtual int CalculateLimitMaxWidth() const = 0;
    virtual int CalculateLimitMaxHeight() const = 0;
    virtual int CalculatePreferWidth() const = 0;
    virtual int CalculatePreferHeight() const = 0;

    std::vector<std::shared_ptr<LayoutItem>>& GetLayoutItems();
    std::vector<std::shared_ptr<LayoutItem>> layout_items_;
private:
    Widget* parent_widget_;
    Layout* parent_layout_;
};
} // namespace ui

#endif // #ifndef LAYOUT_H