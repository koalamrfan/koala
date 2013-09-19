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

    void Move(int x, int y);
    void ReSize(int width, int height);
    virtual void SetGeometry(int x, int y, int width, int height);
    int X() const;
    int Y() const;
    int Width() const;
    int Height() const;
    SkRect Geometry() const;
    virtual SkRect GeometryToAncestor() const = 0;
    virtual void SetPreferWidth(int width);
    virtual int PreferWidth();
    virtual void SetPreferHeight(int height);
    virtual int PreferHeight();
    virtual void SetLimitMinWidth(int width);
    virtual int LimitMinWidth();
    virtual void SetLimitMinHeight(int height);
    virtual int LimitMinHeight();
    virtual void SetLimitMaxWidth(int width);
    virtual int LimitMaxWidth();
    virtual void SetLimitMaxHeight(int height);
    virtual int LimitMaxHeight();
    void Dolayout();
    virtual void AdjustSizes() = 0;
    void Update(const SkRect& clip_rect) const;
    void Update() const;
    // adapt
    void NotifyRelayout() const;

protected:
    virtual void Relayout() = 0;
private:
    int x_;
    int y_;
    int width_;
    int height_;

    int prefer_width_;
    int prefer_height_;

    int limit_min_width_;
    int limit_min_height_;
    int limit_max_width_;
    int limit_max_height_;
};
} // namesapce ui

#endif // LAYOUT_BASE_ITEM