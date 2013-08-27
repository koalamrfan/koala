#include "widget.h"
#include "app.h"
#include "SkBitmap.h"
#include <vector>


namespace ui
{
Widget::Widget():parent_(nullptr),
        parent_layout_(nullptr),
        layout_(nullptr),
        auto_region_active_(true),
        region_mode_(HitRegionMode::kAuto) {
    
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

Widget* Widget::ChildAt(uint32_t index) {
    if(index < 0 || index >= ChildrenNum())
        return nullptr;
    return children_[index];
}

uint32_t Widget::ChildrenNum() const {
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

void Widget::AdjustSizes(bool deep) {
    if(BaseLayout()) {
        BaseLayout()->AdjustSizes(deep);

        SetPreferWidth(BaseLayout()->PreferWidth());
        SetPreferHeight(BaseLayout()->PreferHeight());
        SetLimitMinWidth(BaseLayout()->LimitMinWidth());
        SetLimitMinHeight(BaseLayout()->LimitMinHeight());
        SetLimitMaxWidth(BaseLayout()->LimitMaxWidth());
        SetLimitMaxHeight(BaseLayout()->LimitMaxHeight());

        AdaptLimitSize();
    }
}

void Widget::Relayout() {
    if(BaseLayout()) {
        if(Parent() == nullptr) {
            AdjustSizes(true);
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
    AdjustSizes(false);
    if(ParentLayout()) {
        UpNotifyRelayout();
    } else {
        AdaptLimitSize();
        if(BaseLayout()) {
            BaseLayout()->SetGeometry(0, 0, Width(), Height());
            BaseLayout()->Relayout();
        }
    }
}

void Widget::AdaptLimitSize() {
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
    if(IsVisible() == false) {
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

bool Widget::PointInRegion(int32_t x, int32_t y) {
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
        if(GeometryToAncestor().contains(x, y)) {
            return true; 
        }
    } else if(GetHitRegionMode() == HitRegionMode::kNothing) {
        return false;
    }
    return false;
}

Widget* Widget::HitTest(int32_t x, int32_t y) {
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

SkRect Widget::GeometryToAncestor() {
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

SkRegion Widget::Region() const {
    return region_;
}

void Widget::SetSource( const std::string& source ) {
    source_ = source;
}

std::string Widget::Source() const {
    return source_;
}

void Widget::Update() {
    RECT rect;
    SkRect sk_rect = GeometryToAncestor();
    rect.left = SkScalarFloorToInt(sk_rect.fLeft);
    rect.top = SkScalarFloorToInt(sk_rect.fTop);
    rect.right = SkScalarFloorToInt(sk_rect.fRight);
    rect.bottom = SkScalarFloorToInt(sk_rect.fBottom);
    InvalidateRect(App::GetInstance()->GetMainWindow()->GetHwnd(), &rect, FALSE);
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
    Update();
}

bool Widget::PointInInnerBitmap(int32_t x, int32_t y) {
    if(inner_bitmap_ == nullptr) {
        return false;
    }
    return 0 != *(inner_bitmap_->getAddr32(x, y));
}
} // namespace ui