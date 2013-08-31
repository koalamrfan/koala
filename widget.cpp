#include "widget.h"
#include "app.h"
#include "SkBitmap.h"
#include "layout_adapt_manager.h"
#include <vector>


namespace ui
{
Widget::Widget():parent_(nullptr),
        parent_layout_(nullptr),
        layout_(nullptr),
        auto_region_active_(true),
        region_mode_(HitRegionMode::kAuto),
        visible_(true) {
    
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
}

void Widget::RemoveChild(Widget* widget) {
    auto iter = children_.begin();
    while (iter != children_.end()) {
        if(*iter == widget) {
            children_.erase(iter);
            break;
        }
        iter++;
    }
}

Widget* Widget::ChildAt(int index) {
    if(index < 0 || index >= ChildrenNum())
        return nullptr;
    return children_[index];
}

int Widget::ChildrenNum() const {
    return children_.size();
}

void Widget::SetParent(Widget* parent) {
    if(parent !=  nullptr) {
        parent->AddChild(this);
    }
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

void Widget::SetGeometry(int x, int y, int width, int height) {
    UpdateAutoRegion();
    LayoutBaseItem::SetGeometry(x, y, width, height);
}

void Widget::Show() {
    visible_ = true;
    NotifyRelayout();
}

void Widget::Hide() {
    visible_ = false;
    NotifyRelayout();
}

bool Widget::IsVisible() const{
    return visible_;
}

void Widget::SetLayout(Layout* layout) {
    layout_ = layout;
    layout_->SetParentWidget(this);
}

void Widget::AdjustSizes() {
    if(BaseLayout()) {
        BaseLayout()->AdjustSizes();
        LayoutBaseItem::SetLimitMinWidth(BaseLayout()->LimitMinWidth());
        LayoutBaseItem::SetLimitMinHeight(BaseLayout()->LimitMinHeight());
        LayoutBaseItem::SetLimitMaxWidth(BaseLayout()->LimitMaxWidth());
        LayoutBaseItem::SetLimitMaxHeight(BaseLayout()->LimitMaxHeight());

        if(PreferWidth() == 0) {
            LayoutBaseItem::SetPreferWidth(BaseLayout()->PreferWidth());
        } else if(PreferWidth() < LimitMinWidth()) {
            LayoutBaseItem::SetPreferWidth(LimitMinWidth());
        } else if(PreferWidth() > LimitMaxWidth()) {
            LayoutBaseItem::SetPreferWidth(LimitMaxWidth());
        }

        if(PreferHeight() == 0) {
            LayoutBaseItem::SetPreferHeight(BaseLayout()->PreferHeight());
        } else if(PreferHeight() < LimitMinHeight()) {
            LayoutBaseItem::SetPreferHeight(LimitMinHeight());
        } else if(PreferHeight() > LimitMaxHeight()) {
            LayoutBaseItem::SetPreferHeight(LimitMaxHeight());
        }
    }
}

void Widget::Relayout() {
    if(BaseLayout()) {
        BaseLayout()->SetGeometry(0, 0, Width(), Height());
        BaseLayout()->Relayout();
    }
}

void Widget::SetPreferWidth(int width) {
    LayoutBaseItem::SetPreferWidth(width);
    NotifyRelayout();
}

void Widget::SetPreferHeight(int height) {
    LayoutBaseItem::SetPreferHeight(height);
    NotifyRelayout();
}

void Widget::SetLimitMinWidth(int width) {
    LayoutBaseItem::SetLimitMinWidth(width);
    NotifyRelayout();
}

void Widget::SetLimitMinHeight(int height) {
    LayoutBaseItem::SetLimitMinHeight(height);
    NotifyRelayout();
}

void Widget::SetLimitMaxWidth(int width) {
    LayoutBaseItem::SetLimitMaxWidth(width);
    NotifyRelayout();
}

void Widget::SetLimitMaxHeight(int height) {
    LayoutBaseItem::SetLimitMaxHeight(height);
    NotifyRelayout();
}

Layout* Widget::BaseLayout() const {
    return layout_;
}

void Widget::Draw(const SkRect& clip_rect) {
    if(!IsVisible()) {
        return ;
    }
    if(!DrawSelf(clip_rect)) {
        return ;
    }
    if (children_.empty()) {
        return ;
    }
    auto iter = children_.begin();
    while (iter != children_.end()) {
         (*iter)->Draw(clip_rect);
         iter++;
    }
}

bool Widget::DrawSelf(const SkRect& clip_rect) {
    SkRect relative_clip_rect = GeometryToAncestor();
    if(relative_clip_rect.intersect(clip_rect)) {
        auto canvas = TexturePool::GetInstance()->GetCanvas();
        canvas->save();
        canvas->clipRect(clip_rect);
        if(auto_region_active_ && region_mode_ == HitRegionMode::kAuto) {
            MakeInnerBitmap(clip_rect);
            auto_region_active_ = false;
        }
        canvas->translate(SkIntToScalar(GeometryToAncestor().x()), 
            SkIntToScalar(GeometryToAncestor().y()));
        relative_clip_rect.offsetTo(relative_clip_rect.x() - GeometryToAncestor().x(), 
                                    relative_clip_rect.y() - GeometryToAncestor().y());
        OnDraw(canvas, clip_rect);
        canvas->restore();
        return true;
    }
    return false;
}

void Widget::SetRegion(const SkRegion& region) {
    region_ = region;
}

bool Widget::PointInRegion(int x, int y) {
    if(GetHitRegionMode() == HitRegionMode::kAuto) {
        if(GeometryToAncestor().contains(SkIntToScalar(x), SkIntToScalar(y))) {
            return PointInInnerBitmap(x - SkScalarFloorToInt(GeometryToAncestor().x()),
                y - SkScalarFloorToInt(GeometryToAncestor().y()));
        }
    } else if(GetHitRegionMode() == HitRegionMode::kCustom) {
        SkRegion region_to_ancestor = region_;
        region_to_ancestor.translate(SkScalarFloorToInt(GeometryToAncestor().x()),
                                     SkScalarFloorToInt(GeometryToAncestor().y()));
        return region_to_ancestor.contains(x, y);
    } else if(GetHitRegionMode() == HitRegionMode::kEntirely) {
        if(GeometryToAncestor().contains(SkIntToScalar(x), 
                                         SkIntToScalar(y))) {
            return true; 
        }
    } else if(GetHitRegionMode() == HitRegionMode::kNothing) {
        return false;
    }
    return false;
}

Widget* Widget::HitTest(int x, int y) {
    if(!IsVisible()) {
        return nullptr;
    }
    auto iter = children_.rbegin();
    while (iter != children_.rend()) {
        if((*iter)->PointInRegion(x, y)) {
            return (*iter)->HitTest(x, y);
        }
        iter++;
    }
    if(PointInRegion(x, y)) {
        return this;
    }
    return nullptr;
}

SkRect Widget::GeometryToAncestor() const {
    int x = X(), y= Y();
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

SkRegion Widget::Region() const {
    return region_;
}

void Widget::SetSource( const std::string& source ) {
    source_ = source;
}

std::string Widget::Source() const {
    return source_;
}

void Widget::SetHitRegionMode(HitRegionMode region_mode) {
    region_mode_ = region_mode;
}

ui::HitRegionMode Widget::GetHitRegionMode() const {
    return region_mode_;
}

void Widget::MakeInnerBitmap(const SkRect& clip_rect) {
    inner_bitmap_ = std::make_shared<SkBitmap>();
    inner_bitmap_->setConfig(SkBitmap::kARGB_8888_Config, 
                             SkScalarFloorToInt(GeometryToAncestor().width()), 
                             SkScalarFloorToInt(GeometryToAncestor().height()));
    inner_bitmap_->allocPixels();
    inner_canvas_ = std::make_shared<SkCanvas>(*inner_bitmap_);
    inner_canvas_->clear(SK_AlphaTRANSPARENT);
    OnDraw(inner_canvas_.get(), clip_rect);
    /*auto canvas = TexturePool::GetInstance()->GetCanvas();
    SkPaint paint;
    canvas->drawBitmapRect(*inner_bitmap_, rect, &paint);*/
}

std::vector<SkBitmap*> Widget::Bitmap() {
    return TexturePool::GetInstance()->CreateBitmapFromSource(source_);
}



std::shared_ptr<BmpRenderTactics> Widget::GetRenderTactics() {
    auto extentd = source_.substr(source_.size() - 6);
    if(extentd == ".9.png") {
        return TexturePool::GetInstance()->CreatePng9Tactics();
    }else {
        return TexturePool::GetInstance()->CreateNormalTactics();
    }
    return nullptr;
}

void Widget::UpdateAutoRegion() {
    auto_region_active_ = true;
}

bool Widget::PointInInnerBitmap(int x, int y) {
    if(inner_bitmap_ == nullptr) {
        return false;
    }
    return 0 != *(inner_bitmap_->getAddr32(x, y));
}
} // namespace ui