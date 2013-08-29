#ifndef WIDGET_H_
#define WIDGET_H_

#include "layout_base_item.h"
#include "event.h"
#include "layout.h"
#include "texture_pool.h"
#include "SkRegion.h"
#include <string>
#include <memory>
#include <vector>

class SkCanvas;
class SkBitmap;
class SkRegion;

namespace ui
{
enum class HitRegionMode
{
    kEntirely = 0,
    kAuto,
    kCustom,
    kNothing
};

class Widget:public LayoutBaseItem
{
public:
    Widget();
    virtual ~Widget();

    Widget* ChildAt(uint32_t index);
    uint32_t ChildrenNum() const;
    void SetParent(Widget* parent);
    Widget* Parent() const;
    void SetParentLayout(Layout* parent);
    Layout* ParentLayout() const;
    Layout* BaseLayout() const;

    virtual void Show();
    virtual void Hide();
    bool IsVisible() const;
    void SetLayout(Layout* layout);
    
    virtual void AdjustSizes() override;
    

    virtual void SetPreferWidth(uint32_t width) override;
    virtual void SetPreferHeight(uint32_t height) override;
    virtual void SetLimitMinWidth(uint32_t width) override;
    virtual void SetLimitMinHeight(uint32_t height) override;
    virtual void SetLimitMaxWidth(uint32_t width) override;
    virtual void SetLimitMaxHeight(uint32_t height) override;

    void Draw(const SkRect& clip_rect);
    void SetRegion(const SkRegion& region);
    SkRegion Region() const;

    virtual SkRect GeometryToAncestor() const override;

    void UpdateAutoRegion();
    void SetSource(const std::string& source);
    std::string Source() const;

    void SetHitRegionMode(HitRegionMode region_mode);
    HitRegionMode GetHitRegionMode() const;

    std::vector<SkBitmap*> Bitmap();

    virtual bool DoEvent(Event* event) { return false; };
    Widget* HitTest(int32_t x, int32_t y);
protected:
    virtual void Relayout() override;
    virtual void AddChild(Widget* widget);
    virtual void RemoveChild(Widget* widget);
    bool DrawSelf( const SkRect& clip_rect );
    virtual void OnDraw(SkCanvas* canvas, const SkRect& clip_rect) = 0;
    void MakeInnerBitmap(const SkRect& clip_rect);
    std::shared_ptr<BmpRenderTactics> GetRenderTactics();
    
    bool PointInRegion(int32_t x, int32_t y);
    bool PointInInnerBitmap(int32_t x, int32_t y);

    std::vector<Widget*> children_;
    Layout* layout_;
    Widget* parent_;
    Layout* parent_layout_;
private:
    SkRegion region_;
    std::string source_;
    HitRegionMode region_mode_;
    std::shared_ptr<SkCanvas> inner_canvas_;
    std::shared_ptr<SkBitmap> inner_bitmap_;
    bool auto_region_active_;
};
} // namespace ui

#endif