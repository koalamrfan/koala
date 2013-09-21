#include "layout_item.h"

#include "widget.h"
#include "layout.h"
#include "layout_space.h"
#include "layout_base_item.h"

namespace ui
{
LayoutItem::LayoutItem():layout_base_item_(nullptr) {

}

LayoutItem::~LayoutItem() {
    delete layout_base_item_;
    layout_base_item_ = nullptr;
}

void LayoutItem::Init(Widget* widget) {
    type_ = kWidget;
    layout_base_item_ = widget;
}

void LayoutItem::Init(Layout* layout) {
    type_ = kLayout;
    layout_base_item_ = layout;
}

void LayoutItem::Init(LayoutSpace* layout_space) {
    type_ = kLayoutSpace;
    layout_base_item_ = layout_space;
}

void LayoutItem::Relayout() {
    layout_base_item_->Relayout();
}

void LayoutItem::AdjustSizes() {
    layout_base_item_->AdjustSizes();
}

void LayoutItem::Move(int x, int y) {
    layout_base_item_->Move(x, y);
}

void LayoutItem::ReSize(int width, int height) {
    layout_base_item_->ReSize(width, height);
}

void LayoutItem::SetGeometry(int x, int y, int width, int height) {
    layout_base_item_->SetGeometry(x, y, width, height);
}

int LayoutItem::X() {
    return layout_base_item_->X();
}

int LayoutItem::Y() {
    return layout_base_item_->Y();
}

int LayoutItem::Width() {
    return layout_base_item_->Width();
}

int LayoutItem::Height() {
    return layout_base_item_->Height();
}

void LayoutItem::SetPreferWidth(int width) {
    layout_base_item_->SetPreferWidth(width);
}

int LayoutItem::PreferWidth() {
    if(IsEmpty()) {
        return 0;
    }
    return layout_base_item_->PreferWidth();
}

void LayoutItem::SetPreferHeight(int height) {
    layout_base_item_->SetPreferHeight(height);
}

int LayoutItem::PreferHeight() {
    if(IsEmpty()) {
        return 0;
    }
    return layout_base_item_->PreferHeight();
}

void LayoutItem::SetLimitMinWidth(int width) {
    layout_base_item_->SetLimitMinWidth(width);
}

int LayoutItem::LimitMinWidth() {
    if(IsEmpty()) {
        return 0;
    }
    return layout_base_item_->LimitMinWidth();
}

void LayoutItem::SetLimitMinHeight(int height) {
    layout_base_item_->SetLimitMinHeight(height);
}

int LayoutItem::LimitMinHeight() {
    if(IsEmpty()) {
        return 0;
    }
    return layout_base_item_->LimitMinHeight();
}

void LayoutItem::SetLimitMaxWidth(int width) {
    layout_base_item_->SetLimitMaxWidth(width);
}

int LayoutItem::LimitMaxWidth() {
    if(IsEmpty()) {
        return MAX_LENGTH;
    }
    return layout_base_item_->LimitMaxWidth();
}

void LayoutItem::SetLimitMaxHeight(int height) {
    layout_base_item_->SetLimitMaxHeight(height);
}

int LayoutItem::LimitMaxHeight() {
    if(IsEmpty()) {
        return MAX_LENGTH;
    }
    return layout_base_item_->LimitMaxHeight();
}

Widget* LayoutItem::GetWidget() const {
    if(type_ == kWidget) {
        return reinterpret_cast<Widget *>(layout_base_item_);
    }
    return nullptr;
}

Layout* LayoutItem::GetLayout() const {
    if(type_ == kLayout) {
        return reinterpret_cast<Layout *>(layout_base_item_);
    }
    return nullptr;
}

LayoutSpace* LayoutItem::GetLayoutSpace() const {
    if(type_ == kLayoutSpace) {
        return reinterpret_cast<LayoutSpace *>(layout_base_item_);
    }
    return nullptr;
}

LayoutBaseItem* LayoutItem::GetLayoutBaseItem() const {
    return layout_base_item_;
}

void LayoutItem::UpNotifyRelayout() {

}

void LayoutItem::RelayoutToAdapt() {

}

bool LayoutItem::IsEmpty() const {
    if(GetWidget() && GetWidget()->IsVisible()) {
        return false;
    } else if(GetLayout() && !GetLayout()->IsEmpty()) {
        return false;
    } else if(GetLayoutSpace()) {
        return false;
    }
    return true;
}

bool LayoutItem::SetParentLayout(Layout* layout, int index) {
    if(layout == nullptr) {
        if(GetWidget()) {
            GetWidget()->SetParentLayout(nullptr);
        } else if(GetLayout()) {
            GetLayout()->SetParentLayout(nullptr);
        }
        return true;
    }

    if(index < 0) {
        index += layout->Count() + 1;
    }

    if(index < 0 || index > layout->Count()) {
        return false;
    }

    if(layout->FindItem(GetLayoutBaseItem())) {
        return false;
    }

    std::vector<std::shared_ptr<LayoutItem>>& brother_items = layout->GetLayoutItems();
    if(GetWidget()) {
        if(GetWidget()->ParentLayout() && GetWidget()->ParentLayout() == layout) {
            return false;
        } 
        GetWidget()->SetParent(layout->ParentWidget());
        GetWidget()->SetParentLayout(layout, index);
    } else if(GetLayout()) {
        if(GetLayout()->ParentLayout() && GetWidget()->ParentLayout() == layout) {
            return false;
        }
        GetLayout()->SetParentWidget(layout->ParentWidget());
        GetLayout()->SetParentLayout(layout, index);

    }
    return true;
}

Layout* LayoutItem::ParentLayout() const {
    if(GetWidget()) {
        return GetWidget()->ParentLayout();
    } else if(GetLayout()) {
        GetLayout()->ParentLayout();
    }
    return nullptr;
}
} // namespace ui