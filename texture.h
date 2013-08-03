#ifndef TEXTURE_H
#define TEXTURE_H

class SkCanvas;

namespace ui
{
class Texture
{
public:
    virtual void Draw();
protected:
    virtual void OnDraw(SkCanvas* canvas) = 0;
    void CanvasToScreen();
};
} // namespace ui
#endif