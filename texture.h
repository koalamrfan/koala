#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <vector>

class SkCanvas;
class SkBitmap;
namespace ui
{
class Texture
{
public:
    virtual void Draw();
protected:
    virtual void OnDraw(SkCanvas* canvas) = 0;
    void CanvasToScreen();

    void SetSource(const std::string& source);
    SkBitmap* Bitmap();
private:
    std::string source_;
};
} // namespace ui
#endif