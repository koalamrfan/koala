#include "widget.h"
#include <vector>
#include "layout.h"
#include "SkBitmap.h"

namespace ui
{
Widget::Widget():parent_(nullptr),
        parent_layout_(nullptr),
        layout_(nullptr) {
    
}

Widget::~Widget() {

}

void Widget::AddChild(Widget* widget) {
    auto iter = children_.begin();
    while (iter != children_.end()) {
        if(*iter == widget) {
            return ;
        }
        iter++;
    }
    children_.push_back(widget);
    widget->SetParent(this);
}

void Widget::RemoveChild(Widget* widget) {
    widget->SetParent(nullptr);
    auto iter = children_.begin();
    while (iter != children_.end()) {
	if(*iter == widget) {
	    children_.erase(iter);
	    break;
	}
	iter++;
    }
}

Widget* Widget::ChildAt(uint32_t index) {
    if(index < 0 || index >= ChildrenNum())
	return nullptr;
    return children_[index];
}

uint32_t Widget::ChildrenNum() const {
    return children_.size();
}

void Widget::SetParent(Widget* parent) {
    parent->AddChild(this);
    parent_ = parent;
}

Widget* Widget::Parent() const {
    return parent_;
}

void Widget::SetParentLayout(Layout* parent) {
    parent_layout_ = parent;
}

Layout* Widget::ParentLayout() const {
    return parent_layout_;
}

void Widget::SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height) {
    UpdateAutoRegion();
    LayoutBaseItem::SetGeometry(x, y, width, height);
}

void Widget::Show() {
    UpNotifyRelayout();
}

void Widget::Hide() {
    UpNotifyRelayout();
}

bool Widget::IsVisible() const{
    return true;
}

void Widget::SetLayout(Layout* layout) {
    layout_ = layout;
    layout_->SetParentWidget(this);
}

void Widget::ResetPreferLimitSize(bool deep) {
    if(BaseLayout()) {
      BaseLayout()->ResetPreferLimitSize(deep);
      
      SetPreferWidth(BaseLayout()->PreferWidth());
      SetPreferHeight(BaseLayout()->PreferHeight());
      SetLimitMinWidth(BaseLayout()->LimitMinWidth());
      SetLimitMinHeight(BaseLayout()->LimitMinHeight());
      SetLimitMaxWidth(BaseLayout()->LimitMaxWidth());
      SetLimitMaxHeight(BaseLayout()->LimitMaxHeight());
      
      ResizeAdaptLimitSize();
    }
}

void Widget::Relayout() {
    if(BaseLayout()) {
        if(Parent() == nullptr) {
            ResetPreferLimitSize(true);
        }
        BaseLayout()->SetGeometry(0, 0, Width(), Height());
        BaseLayout()->Relayout();
    }
}

void Widget::UpNotifyRelayout() {
    if(ParentLayout()) {
      ParentLayout()->RelayoutToAdapt();
    }
}

void Widget::RelayoutToAdapt() {
    ResetPreferLimitSize(false);
    if(ParentLayout()) {
      UpNotifyRelayout();
    } else {
      ResizeAdaptLimitSize();
      if(BaseLayout()) {
        BaseLayout()->SetGeometry(0, 0, Width(), Height());
        BaseLayout()->Relayout();
      }
    }
}

void Widget::ResizeAdaptLimitSize() {
    uint32_t width = Width(), height = Height();
    if(width < LimitMinWidth()) {
      width = LimitMinWidth();
    } else if(width > LimitMaxWidth()) {
      width = LimitMaxWidth();
    }
    
    if(height < LimitMinHeight()) {
      height = LimitMinHeight();
    } else if(height > LimitMaxHeight()) {
      height = LimitMaxHeight();
    }
    
    SetGeometry(X(), Y(), width, height);
}

void Widget::SetPreferWidth(uint32_t width) {
    LayoutBaseItem::SetPreferWidth(width);
    UpNotifyRelayout();
}

void Widget::SetPreferHeight(uint32_t height) {
    LayoutBaseItem::SetPreferHeight(height);
    UpNotifyRelayout();
}

void Widget::SetLimitMinWidth(uint32_t width) {
    LayoutBaseItem::SetLimitMinWidth(width);
    UpNotifyRelayout();
}

void Widget::SetLimitMinHeight(uint32_t height) {
    LayoutBaseItem::SetLimitMinHeight(height);
    UpNotifyRelayout();
}

void Widget::SetLimitMaxWidth(uint32_t width) {
    LayoutBaseItem::SetLimitMaxWidth(width);
    UpNotifyRelayout();
}

void Widget::SetLimitMaxHeight(uint32_t height) {
    LayoutBaseItem::SetLimitMaxHeight(height);
    UpNotifyRelayout();
}

Layout* Widget::BaseLayout() const {
    return layout_;
}

void Widget::Draw(const SkRect& clip_rect) {
    SkRect rect = SkRect::MakeXYWH(
        SkIntToScalar(X()),
        SkIntToScalar(Y()), 
        SkIntToScalar(Width()), 
        SkIntToScalar(Height())
        );
    if(!rect.intersect(clip_rect)) {
        return ;
    }
    Texture::Draw(clip_rect);
    if (children_.empty()) {
        return ;
    }
    auto iter = children_.begin();
    while (iter != children_.end()) {
         (*iter)->Draw(clip_rect);
         iter++;
    }
}

void Widget::SetRegion(const SkRegion& region) {
    region_ = region;
}

bool Widget::PointInRegion(int32_t x, int32_t y) {
    if(RegionMode() == VisualRegionMode::kAuto) {
        SkRect rect = GetAbsoluteRect();
        if(rect.contains(SkIntToScalar(x), SkIntToScalar(y))) {
            return PointInInnerBitmap(x - SkScalarFloorToInt(rect.x()), y - SkScalarFloorToInt(rect.y()));
        }
    } else if(RegionMode() == VisualRegionMode::kCustom){
        return region_.contains(x, y);
    } else {
        SkIRect rect = SkIRect::MakeXYWH(X(), Y(), Width(), Height());
        if(rect.contains(x, y)) {
            return true; 
        }
    }
    return false;
}

EventTarget* Widget::HitTest(int32_t x, int32_t y) {
    auto iter = children_.rbegin();
    while (iter != children_.rend()) {
        if((*iter)->HitTest(x, y)) {
            return *iter;
        }
        iter++;
    }
    
    if(IgnoreHitTest()) {
        return nullptr;
    }

    if(PointInRegion(x, y)) {
        return (EventTarget*)this;
    }

    return nullptr;
}

SkRect Widget::GetAbsoluteRect() {
    int32_t x = X(), y= Y();
    Widget* parent = Parent();
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

} // namespace ui