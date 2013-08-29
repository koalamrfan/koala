#ifndef LAYOUT_BASE_ITEM_H_
#define LAYOUT_BASE_ITEM_H_

#include <stdint.h>
#include "SkRect.h"

namespace ui
{

#define MAX_LENGTH INT32_MAX

class LayoutItem;
class LayoutBaseItem
{
    friend class LayoutItem;
public:
    LayoutBaseItem();

    virtual ~LayoutBaseItem();

    void Move(int32_t x, int32_t y);
    void ReSize(uint32_t width, uint32_t height);
    virtual void SetGeometry(int32_t x, int32_t y, uint32_t width, uint32_t height);
    int32_t X() const;
    int32_t Y() const;
    uint32_t Width() const;
    uint32_t Height() const;
    SkRect Geometry() const;
    virtual SkRect GeometryToAncestor() const = 0;
    virtual void SetPreferWidth(uint32_t width);
    virtual uint32_t PreferWidth();
    virtual void SetPreferHeight(uint32_t height);
    virtual uint32_t PreferHeight();
    virtual void SetLimitMinWidth(uint32_t width);
    virtual uint32_t LimitMinWidth();
    virtual void SetLimitMinHeight(uint32_t height);
    virtual uint32_t LimitMinHeight();
    virtual void SetLimitMaxWidth(uint32_t width);
    virtual uint32_t LimitMaxWidth();
    virtual void SetLimitMaxHeight(uint32_t height);
    virtual uint32_t LimitMaxHeight();
    void Dolayout();
    virtual void AdjustSizes() = 0;
    void Update(const SkRect& clip_rect) const;
    void Update() const;
    // adapt
    void NotifyRelayout() const;

protected:
    virtual void Relayout() = 0;
private:
    int32_t x_;
    int32_t y_;
    uint32_t width_;
    uint32_t height_;

    uint32_t prefer_width_;
    uint32_t prefer_height_;

    uint32_t limit_min_width_;
    uint32_t limit_min_height_;
    uint32_t limit_max_width_;
    uint32_t limit_max_height_;
};
} // namesapce ui

#endif // LAYOUT_BASE_ITEM