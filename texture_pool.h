#ifndef TEXTURE_POOL
#define TEXTURE_POOL

#include "SkCanvas.h"
#include "SkBitmap.h"
#include <memory>

namespace ui
{
class Window;
class ScopeHdc;
class TexturePool
{
public:
    static TexturePool* GetInstance();
    
    void Init(Window* window);

    void ResizeCanvas(uint32_t width, uint32_t height);

    SkCanvas* GetCanvas();
    SkBitmap* GetBitmap();
    std::shared_ptr<ScopeHdc> GetScopeHdc() const;

protected:
    TexturePool():canvas_(nullptr) {}

private:
    std::shared_ptr<SkCanvas> canvas_;
    std::shared_ptr<SkBitmap> bitmap_;
    Window* window_;
};

class ScopeHdc
{
public:
    ScopeHdc(Window* window);
    ~ScopeHdc();

    HDC GetHdc() const {
        return hdc_;
    }
private:
    Window* window_;
    PAINTSTRUCT ps_;
    HDC hdc_;
};
}
#endif