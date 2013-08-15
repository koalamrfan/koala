#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>
#include <memory>

#include "texture_pool.h"

class SkCanvas;
class SkBitmap;
class SkRegion;

namespace ui
{
enum class VisualRegionMode
{
    kEntirely = 0,
    kAuto,
    kCustom
};

class Texture
{
public:
    Texture();

    virtual void Draw(const SkRect& clip_rect);

    void Update();
    void SetSource(const std::string& source);
    std::string Source() const {
        return source_;
    }

    virtual SkRect GetInnerBitmapRect() = 0;

protected:
    virtual void OnDraw(SkCanvas* canvas, const SkRect& clip_rect) = 0;
    void MakeInnerBitmap(const SkRect& clip_rect);

    std::shared_ptr<BmpRenderTactics> GetRenderTactics();
    std::vector<SkBitmap*> Bitmap();

    void SetRegionMode(VisualRegionMode region_mode);
    VisualRegionMode RegionMode() const {
        return region_mode_;
    }
    
    void UpdateAutoRegion();
    bool PointInInnerBitmap(int32_t x, int32_t y);
private:
    SkRegion region_;

    std::string source_;
    VisualRegionMode region_mode_;
    std::shared_ptr<SkCanvas> inner_canvas_;
    std::shared_ptr<SkBitmap> inner_bitmap_;
    bool auto_region_active_;
};
} // namespace ui
#endif