#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

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

    virtual void Draw();
    void SetSource(const std::string& source);
    std::string Source() const {
        return source_;
    }

    virtual uint32_t GetInnerBitmapWidth() = 0;
    virtual uint32_t GetInnerBitmapHeight() = 0;
protected:
    virtual void OnDraw(SkCanvas* canvas) {}

    std::shared_ptr<BmpRenderTactics> GetRenderTactics();
    SkBitmap* Bitmap();

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