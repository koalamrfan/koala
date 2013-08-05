#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

#include "texture_pool.h"

class SkCanvas;
class SkBitmap;
namespace ui
{
class Texture
{
public:
    virtual void Draw();
    void SetSource(const std::string& source);
    std::string Source() const {
        return source_;
    }
protected:
    virtual void OnDraw(SkCanvas* canvas) = 0;
    void CanvasToScreen();

    std::shared_ptr<BmpRenderTactics> GetRenderTactics();
    SkBitmap* Bitmap();
private:
    std::string source_;
};
} // namespace ui
#endif