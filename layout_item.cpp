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

void LayoutItem::Dolayout() {
    layout_base_item_->Dolayout();
}

void LayoutItem::AdjustSizes(bool deep) {
    layout_base_item_->AdjustSizes(deep);
}

void LayoutItem::Move(int32_t x, int32_t y) {
    layout_base_item_->Move(x, y);
}

void LayoutItem::ReSize(uint32_t width, uint32_t height) {
    layout_base_item_->ReSize(width, height);
}

void LayoutItem::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    layout_base_item_->SetGeometry(x, y, width, height);
}

int32_t LayoutItem::X() {
    return layout_base_item_->X();
}

int32_t LayoutItem::Y() {
    return layout_base_item_->Y();
}

uint32_t LayoutItem::Width() {
    return layout_base_item_->Width();
}

uint32_t LayoutItem::Height() {
    return layout_base_item_->Height();
}

void LayoutItem::SetPreferWidth(uint32_t width) {
    layout_base_item_->SetPreferWidth(width);
}

uint32_t LayoutItem::PreferWidth() {
    return layout_base_item_->PreferWidth();
}

void LayoutItem::SetPreferHeight(uint32_t height) {
    layout_base_item_->SetPreferHeight(height);
}

uint32_t LayoutItem::PreferHeight() {
    return layout_base_item_->PreferHeight();
}

void LayoutItem::SetLimitMinWidth(uint32_t width) {
    layout_base_item_->SetLimitMinWidth(width);
}

uint32_t LayoutItem::LimitMinWidth() {
    return layout_base_item_->LimitMinWidth();
}

void LayoutItem::SetLimitMinHeight(uint32_t height) {
    layout_base_item_->SetLimitMinHeight(height);
}

uint32_t LayoutItem::LimitMinHeight() {
    return layout_base_item_->LimitMinHeight();
}

void LayoutItem::SetLimitMaxWidth(uint32_t width) {
    layout_base_item_->SetLimitMaxWidth(width);
}

uint32_t LayoutItem::LimitMaxWidth() {
    return layout_base_item_->LimitMaxWidth();
}

void LayoutItem::SetLimitMaxHeight(uint32_t height) {
    layout_base_item_->SetLimitMaxHeight(height);
}

uint32_t LayoutItem::LimitMaxHeight() {
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
} // namespace ui