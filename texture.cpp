#include "texture.h"
#include "SkCanvas.h"
#include "texture_pool.h"
#include "app.h"
#include <windows.h>

namespace ui
{
void Texture::Draw() {
    OnDraw(TexturePool::GetInstance()->GetCanvas());
    CanvasToScreen();
} 

void Texture::CanvasToScreen() {
    auto scope_hdc = TexturePool::GetInstance()->GetScopeHdc();
    SkBitmap* bitmap = TexturePool::GetInstance()->GetBitmap();
    BITMAPINFO bmi;
    memset(&bmi, 0, sizeof(bmi));
    bmi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth       = bitmap->width();
    bmi.bmiHeader.biHeight      = -bitmap->height(); // top-down image
    bmi.bmiHeader.biPlanes      = 1;
    bmi.bmiHeader.biBitCount    = 32;
    bmi.bmiHeader.biCompression = BI_RGB;
    bmi.bmiHeader.biSizeImage   = 0;

    //
    // Do the SetDIBitsToDevice.
    //
    // TODO(wjmaclean):
    //       Fix this call to handle SkBitmaps that have rowBytes != width,
    //       i.e. may have padding at the end of lines. The SkASSERT below
    //       may be ignored by builds, and the only obviously safe option
    //       seems to be to copy the bitmap to a temporary (contiguous)
    //       buffer before passing to SetDIBitsToDevice().
    SkASSERT(bitmap->width() * bitmap->bytesPerPixel() == bitmap->rowBytes());
    bitmap->lockPixels();
    int ret = SetDIBitsToDevice(scope_hdc->GetHdc(),
        0, 0,
        bitmap->width(), bitmap->height(),
        0, 0,
        0, bitmap->height(),
        bitmap->getPixels(),
        &bmi,
        DIB_RGB_COLORS);
    (void)ret; // we're ignoring potential failures for now.
    bitmap->unlockPixels();
}

void Texture::SetSource(const std::string& source) {
    source_ = source;
}

SkBitmap* Texture::Bitmap() {
    return TexturePool::GetInstance()->GetBitmap(source_).get();
}
} // namespace ui