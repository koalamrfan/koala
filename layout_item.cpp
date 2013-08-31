#include "layout_item.h"

#include "widget.h"
#include "layout.h"
#include "layout_space.h"
#include "layout_base_item.h"

namespace ui
{
LayoutItem::LayoutItem(Widget* widget):layout_base_item_(widget) {
    type_ = kWidget;
}

LayoutItem::LayoutItem(Layout* layout):layout_base_item_(layout) {
    type_ = kLayout;
}

LayoutItem::LayoutItem(LayoutSpace* layout_space):layout_base_item_(layout_space) {
    type_ = kLayoutSpace;
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
    return layout_base_item_->PreferWidth();
}

void LayoutItem::SetPreferHeight(int height) {
    layout_base_item_->SetPreferHeight(height);
}

int LayoutItem::PreferHeight() {
    return layout_base_item_->PreferHeight();
}

void LayoutItem::SetLimitMinWidth(int width) {
    layout_base_item_->SetLimitMinWidth(width);
}

int LayoutItem::LimitMinWidth() {
    return layout_base_item_->LimitMinWidth();
}

void LayoutItem::SetLimitMinHeight(int height) {
    layout_base_item_->SetLimitMinHeight(height);
}

int LayoutItem::LimitMinHeight() {
    return layout_base_item_->LimitMinHeight();
}

void LayoutItem::SetLimitMaxWidth(int width) {
    layout_base_item_->SetLimitMaxWidth(width);
}

int LayoutItem::LimitMaxWidth() {
    return layout_base_item_->LimitMaxWidth();
}

void LayoutItem::SetLimitMaxHeight(int height) {
    layout_base_item_->SetLimitMaxHeight(height);
}

int LayoutItem::LimitMaxHeight() {
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

bool LayoutItem::IsEmpty() {
    if(GetWidget() && GetWidget()->IsVisible()) {
        return false;
    } else if(GetLayout() && !GetLayout()->IsEmpty()) {
        return false;
    } else if(GetLayoutSpace()) {
        return false;
    }
    return true;
}
} // namespace ui