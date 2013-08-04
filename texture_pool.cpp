#include "texture_pool.h"
#include "ywindow.h"

namespace ui
{
TexturePool* TexturePool::GetInstance() {
    static TexturePool pool;
    return &pool;
}

void TexturePool::Init(Window* window) {
    window_ = window;
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
        GetClientRect(window_->GetHwnd(), &rect);
        bitmap_->setConfig(SkBitmap::kARGB_8888_Config, rect.right - rect.left, rect.bottom - rect.top);
        bitmap_->allocPixels();
    }
    return bitmap_.get();
}

std::shared_ptr<ScopeHdc> TexturePool::GetScopeHdc() const {
    return std::make_shared<ScopeHdc>(window_);
}

ScopeHdc::ScopeHdc(Window* window) {
    hdc_ = BeginPaint(window->GetHwnd(), &ps_);
    window_ = window;
}

ScopeHdc::~ScopeHdc() {
    EndPaint(window_->GetHwnd(), &ps_);
}
} // namespace ui