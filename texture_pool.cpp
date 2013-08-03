#include "texture_pool.h"
#include "SkCanvas.h"
#include "SkBitmap.h"
#include "app.h"

namespace ui
{
TexturePool* TexturePool::GetInstance() {
    static TexturePool pool;
    return &pool;
}

SkCanvas* TexturePool::GetCanvas() {
    if(canvas_ == nullptr) {
        canvas_ = std::make_shared<SkCanvas>(*GetBitmap());
    }
    return canvas_.get();
}

SkBitmap* TexturePool::GetBitmap() {
    if(bitmap_ == nullptr) {
        bitmap_ = std::make_shared<SkBitmap>();
        RECT rect;
        GetClientRect(App::GetInstance()->GetHwnd(), &rect);
        bitmap_->setConfig(SkBitmap::kARGB_8888_Config, rect.right - rect.left, rect.bottom - rect.top);
        bitmap_->allocPixels();
    }
    return bitmap_.get();
}
} // namespace ui