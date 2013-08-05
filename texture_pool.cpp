#include "texture_pool.h"
#include "ywindow.h"
#include "SkImageDecoder.h"

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
        bitmap_->setConfig(SkBitmap::kARGB_8888_Config, window_->Width(), window_->Height());
        bitmap_->allocPixels();
    }
    
    return bitmap_.get();
}

std::shared_ptr<SkBitmap> TexturePool::GetBitmap(const std::string& source) {
    if(source2bitmap_.find(source) != source2bitmap_.end()) {
        return source2bitmap_[source];
    }

    auto bm = std::make_shared<SkBitmap>();
    source2bitmap_[source] = bm;
    SkImageDecoder::DecodeFile(source.c_str(), bm.get(), SkBitmap::kARGB_8888_Config,
        SkImageDecoder::kDecodePixels_Mode);
    return bm;
}

std::shared_ptr<ScopeHdc> TexturePool::GetScopeHdc() const {
    return std::make_shared<ScopeHdc>(window_);
}

void TexturePool::ResizeCanvas(uint32_t width, uint32_t height) {
    if(bitmap_) {
        bitmap_ = std::make_shared<SkBitmap>();
        bitmap_->setConfig(SkBitmap::kARGB_8888_Config, width, height);
        bitmap_->allocPixels();

        canvas_ = std::make_shared<SkCanvas>(*GetBitmap());
    }
}

ScopeHdc::ScopeHdc(Window* window) {
    hdc_ = BeginPaint(window->GetHwnd(), &ps_);
    window_ = window;
}

ScopeHdc::~ScopeHdc() {
    EndPaint(window_->GetHwnd(), &ps_);
}
} // namespace ui