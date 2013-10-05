#include "layout.h"
#include "layout_item.h"
#include "widget.h"
#include "layout_base_item.h"
#include "app.h"
#include "layout_adapt_manager.h"
#include "layout_space.h"
#include <cassert>


namespace ui
{
bool Layout::AddWidget(Widget* widget) {
    return InsertWidget(-1, widget);
}

bool Layout::InsertWidget(int index, Widget *widget) {
    auto layoutitem = CreateLayoutItem();
    layoutitem->Init(widget);
    return Layout::InsertItem(index, layoutitem);
}

bool Layout::RemoveWidget(Widget *widget) {
    widget->SetParent(nullptr);
    return Layout::RemoveItem(widget);
}

bool Layout::AddLayout(Layout* layout) {
    return InsertLayout(-1, layout);
}

bool Layout::InsertLayout(int index, Layout *layout) {
    auto layoutitem = CreateLayoutItem();
    layoutitem->Init(layout);
    return Layout::InsertItem(index, layoutitem);
}

bool Layout::RemoveLayout(Layout *layout) {
    return Layout::RemoveItem(layout);
}

bool Layout::AddLayoutSpace(LayoutSpace* layout_space) {
    return InsertLayoutSpace(-1, layout_space);
}

bool Layout::InsertLayoutSpace(int index, LayoutSpace *layout_space) {
    auto layoutitem = CreateLayoutItem();
    layoutitem->Init(layout_space);
    return Layout::InsertItem(index, layoutitem);
}

bool Layout::RemoveLayoutSpace(LayoutSpace *layout_space) {
    return Layout::RemoveItem(layout_space);
}

bool Layout::AddItem(std::shared_ptr<LayoutItem> item) {
    return InsertItem(-1, item);
}

bool Layout::InsertItem(int index, std::shared_ptr<LayoutItem> item) {
    if(item == nullptr) {
        return false;
    }
    return item->SetParentLayout(this, index);
}

bool Layout::RemoveItem(LayoutBaseItem *item) {
    if(item == nullptr) {
        return false;
    }
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
        if((*iter)->GetLayoutBaseItem() == item) {
            layout_items_.erase(iter);
            return true;
        }
        iter++;
    }
    return false;
}

int Layout::Count() const {
    return layout_items_.size();
}

LayoutItem* Layout::ItemAt(int  index) const {
    if (index < 0) {
        index += Count();
    }
    if (index < 0 || index >= Count()) {
        return nullptr;
    }
    return layout_items_[index].get();
}

void Layout::AdjustSizes() {
    for(auto item:layout_items_) {
        item->AdjustSizes();
    }
    SetLimitMinWidth(CalculateLimitMinWidth());
    SetLimitMinHeight(CalculateLimitMinHeight());
    SetLimitMaxWidth(CalculateLimitMaxWidth());
    SetLimitMaxHeight(CalculateLimitMaxHeight());
    SetPreferWidth(CalculatePreferWidth());
    SetPreferHeight(CalculatePreferHeight());

    assert(LimitMinWidth() <= LimitMaxWidth());
    assert(LimitMinHeight() <= LimitMaxHeight());
    assert(LimitMinWidth() <= PreferWidth());
    assert(PreferWidth() <= LimitMaxWidth());
    assert(LimitMinHeight() <= PreferHeight());
    assert(PreferHeight() <= LimitMaxHeight());
}

void Layout::SetParentWidget(Widget* widget) {
    if(parent_widget_ == widget) {
        return ;
    }
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        auto item = (*iter);
        if(item->GetWidget()) {
            item->GetWidget()->SetParent(widget);
        } else if(item->GetLayout()) {
            item->GetLayout()->SetParentWidget(widget);
        }
        iter++;
    }
    parent_widget_ = widget;
}

Widget* Layout::ParentWidget() const {
    return parent_widget_;
}

bool Layout::SetParentLayout(Layout* parent, int index) {
    if(parent == nullptr) {
        if(ParentLayout() != nullptr) {
            std::vector<std::shared_ptr<LayoutItem>>& bother_items = ParentLayout()->GetLayoutItems();
            auto iter = bother_items.begin();
            while (iter != bother_items.end()) {
                if((*iter)->GetLayout() == this) {
                    bother_items.erase(iter);
                    parent_layout_ = nullptr;
                    return true;
                }
                iter++;
            }
        }
        return false;
    }

    if(index < 0) {
        index += parent->Count() + 1;
    }

    if(index < 0 || index > parent->Count()) {
        return false;
    }

    if(ParentLayout()) {
        std::vector<std::shared_ptr<LayoutItem>>& brother_items = ParentLayout()->GetLayoutItems();
        bool erase = false;
        auto iter = brother_items.begin();
        while (iter != brother_items.end()) {
            if((*iter)->GetLayoutBaseItem() == this) {
               erase = true;
               brother_items.erase(iter);
               break;
            }
            iter++;
        }

        if(!erase) {
            return false;
        }
    } else if(ParentWidget()) {
        ParentWidget()->layout_ = nullptr;
    }
    std::shared_ptr<LayoutItem> moved_layout_item = parent->CreateLayoutItem();
    moved_layout_item->Init(this);
    std::vector<std::shared_ptr<LayoutItem>>& new_brother_items = parent->GetLayoutItems();
    new_brother_items.insert(new_brother_items.begin()+index, moved_layout_item);
    parent_layout_ = parent;
    return true;
}

Layout* Layout::ParentLayout() const {
    return parent_layout_;
}

bool Layout::IsEmpty() const{
    bool empty = true;
    auto iter = layout_items_.begin();
    while(iter != layout_items_.end()) {
        if((*iter)->IsEmpty()) {
            iter++;
            continue;
        }
        empty = false;
        iter++;
    }
    return empty;
}

LayoutItem* Layout::FindItem(LayoutBaseItem *item) const{
    auto iter = layout_items_.begin();
    while (iter != layout_items_.end()) {
        LayoutBaseItem *bli = (*iter)->GetLayoutBaseItem();
        if(bli == item) {
            return iter->get();
        }
        iter++;
    }
    return nullptr;
}

SkRect Layout::GeometryToAncestor() const {
    int x = X(), y= Y();
    Widget* parent = ParentWidget();
    while(parent) {
        x += parent->X();
        y += parent->Y();
        parent = parent->Parent();
    }
    return SkRect::MakeXYWH(
        SkIntToScalar(x),
        SkIntToScalar(y), 
        SkIntToScalar(Width()), 
        SkIntToScalar(Height())
        );
}

std::vector<std::shared_ptr<LayoutItem>>& Layout::GetLayoutItems(){
    return layout_items_;
}
} // namespace ui