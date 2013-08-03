#ifndef TEXTURE_POOL
#define TEXTURE_POOL

#include <memory>

class SkCanvas;
class SkBitmap;
namespace ui
{
class TexturePool
{
public:
    static TexturePool* GetInstance();
    
    SkCanvas* GetCanvas();
    SkBitmap* GetBitmap();
protected:
    TexturePool():canvas_(nullptr) {}

private:
    std::shared_ptr<SkCanvas> canvas_;
    std::shared_ptr<SkBitmap> bitmap_;
};
}
#endif