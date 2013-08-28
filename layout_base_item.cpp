#include "layout_base_item.h"
#include "layout_adapt_manager.h"

namespace ui
{
LayoutBaseItem::LayoutBaseItem():
    x_(0),
    y_(0),
    width_(0),
    height_(0),
    prefer_width_(0),
    prefer_height_(0),
    limit_min_width_(0),
    limit_min_height_(0),
    limit_max_width_(MAX_LENGTH),
    limit_max_height_(MAX_LENGTH) {
      
}

LayoutBaseItem::~LayoutBaseItem() {
  
}

void LayoutBaseItem::Move(int32_t x, int32_t y) {
    x_ = x;
    y_ = y;
}

void LayoutBaseItem::ReSize(uint32_t width, uint32_t height) {
    width_ = width;
    height_ = height;
}

void LayoutBaseItem::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    Move(x, y);
    ReSize(width, height);
}

int32_t LayoutBaseItem::X() {
    return x_;
}

int32_t LayoutBaseItem::Y() {
    return y_;
}

uint32_t LayoutBaseItem::Width() {
    return width_;
}

uint32_t LayoutBaseItem::Height() {
    return height_;
}

SkRect  LayoutBaseItem::Geometry() {
    return SkRect::MakeXYWH(
        SkIntToScalar(X()),
        SkIntToScalar(X()), 
        SkIntToScalar(Width()), 
        SkIntToScalar(Height())
        );
}

void LayoutBaseItem::SetPreferWidth(uint32_t width) {
    prefer_width_ = width;
}

uint32_t LayoutBaseItem::PreferWidth() {
    return prefer_width_;
}

void LayoutBaseItem::SetPreferHeight(uint32_t height) {
    prefer_height_ = height;
}

uint32_t LayoutBaseItem::PreferHeight() {
    return prefer_height_;
}

void LayoutBaseItem::SetLimitMinWidth(uint32_t width) {
    limit_min_width_ = width;
}

uint32_t LayoutBaseItem::LimitMinWidth() {
    return limit_min_width_;
}

void LayoutBaseItem::SetLimitMinHeight(uint32_t height) {
    limit_min_height_ = height;
}

uint32_t LayoutBaseItem::LimitMinHeight() {
    return limit_min_height_;
}

void LayoutBaseItem::SetLimitMaxWidth(uint32_t width) {
    limit_max_width_ = width;
}

uint32_t LayoutBaseItem::LimitMaxWidth() {
    return limit_max_width_;
}

void LayoutBaseItem::SetLimitMaxHeight(uint32_t height) {
    limit_max_height_ = height;
}

uint32_t LayoutBaseItem::LimitMaxHeight() {
    return limit_max_height_;
}

void LayoutBaseItem::Dolayout() {
    LayoutAdaptManager::GetInstance()->CloseAdapt();
    Relayout();
    LayoutAdaptManager::GetInstance()->OpenAdapt();
}

} // namespace ui