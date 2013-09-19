#include "layout_base_item.h"
#include "layout_adapt_manager.h"
#include "layout_item.h"
#include "app.h"

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

void LayoutBaseItem::Move(int x, int y) {
    x_ = x;
    y_ = y;
}

void LayoutBaseItem::ReSize(int width, int height) {
    width_ = width;
    height_ = height;
}

void LayoutBaseItem::SetGeometry(int x, int y, int width, int height) {
    Move(x, y);
    ReSize(width, height);
}

int LayoutBaseItem::X() const {
    return x_;
}

int LayoutBaseItem::Y() const {
    return y_;
}

int LayoutBaseItem::Width() const {
    return width_;
}

int LayoutBaseItem::Height() const {
    return height_;
}

SkRect  LayoutBaseItem::Geometry() const {
    return SkRect::MakeXYWH(
        SkIntToScalar(X()),
        SkIntToScalar(X()), 
        SkIntToScalar(Width()), 
        SkIntToScalar(Height())
        );
}

void LayoutBaseItem::SetPreferWidth(int width) {
    prefer_width_ = width;
}

int LayoutBaseItem::PreferWidth() {
    return prefer_width_;
}

void LayoutBaseItem::SetPreferHeight(int height) {
    prefer_height_ = height;
}

int LayoutBaseItem::PreferHeight() {
    return prefer_height_;
}

void LayoutBaseItem::SetLimitMinWidth(int width) {
    limit_min_width_ = width;
}

int LayoutBaseItem::LimitMinWidth() {
    return limit_min_width_;
}

void LayoutBaseItem::SetLimitMinHeight(int height) {
    limit_min_height_ = height;
}

int LayoutBaseItem::LimitMinHeight() {
    return limit_min_height_;
}

void LayoutBaseItem::SetLimitMaxWidth(int width) {
    limit_max_width_ = width;
}

int LayoutBaseItem::LimitMaxWidth() {
    return limit_max_width_;
}

void LayoutBaseItem::SetLimitMaxHeight(int height) {
    limit_max_height_ = height;
}

int LayoutBaseItem::LimitMaxHeight() {
    return limit_max_height_;
}

void LayoutBaseItem::Dolayout() {
    AdjustSizes();
    LayoutAdaptManager::GetInstance()->CloseAdapt();
    Relayout();
    LayoutAdaptManager::GetInstance()->OpenAdapt();
    Update();
}

void LayoutBaseItem::Update() const {
    Update(GeometryToAncestor());
}

void LayoutBaseItem::Update(const SkRect& clip_rect) const {
    App::Update(clip_rect);    
}

void LayoutBaseItem::NotifyRelayout() const {
    LayoutAdaptManager::GetInstance()->Drive();
}

} // namespace ui