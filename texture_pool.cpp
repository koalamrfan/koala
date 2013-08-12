#include "texture_pool.h"
#include "ywindow.h"
#include "SkImageDecoder.h"
#include <sstream>

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
        bitmap_->setIsOpaque(false);
    }
    
    return bitmap_.get();
}

std::vector<SkBitmap*> TexturePool::CreateBitmapFromSource(const std::string& source) {
    std::vector<SkBitmap*> bitmaps;
    auto sources = Storage::GetInstance()->GetActualSource(source);

    for(auto which_source : sources) {
        if(source2bitmap_.find(which_source) != source2bitmap_.end()) {
            bitmaps.push_back(source2bitmap_[which_source].get());
            continue;
        }

        auto bm = std::make_shared<SkBitmap>();
        bool decode = SkImageDecoder::DecodeFile(which_source.c_str(), bm.get(), SkBitmap::kARGB_8888_Config,
            SkImageDecoder::kDecodePixels_Mode);

        bm->setIsOpaque(false);

        if(decode) {
            source2bitmap_[which_source] = bm;
            bitmaps.push_back(bm.get());
        }
    }

    return bitmaps;
}

std::shared_ptr<ScopeHdc> TexturePool::CreateScopeHdc() const {
    return std::make_shared<ScopeHdc>(window_);
}

std::shared_ptr<BmpRenderTactics> TexturePool::CreatePng9Tactics() {
    return std::make_shared<Png9Tactics>();
}

std::shared_ptr<BmpRenderTactics> TexturePool::CreateNormalTactics() {
    return std::make_shared<NormalTactics>();
}

void TexturePool::ResizeCanvas(uint32_t width, uint32_t height) {
    if(bitmap_) {
        bitmap_ = std::make_shared<SkBitmap>();
        bitmap_->setConfig(SkBitmap::kARGB_8888_Config, width, height);
        bitmap_->allocPixels();
        bitmap_->setIsOpaque(false);

        canvas_ = std::make_shared<SkCanvas>(*GetBitmap());
    }
}

void TexturePool::CanvasToScreen(SkBitmap* bitmap) {
    auto scope_hdc = TexturePool::GetInstance()->CreateScopeHdc();
    if(bitmap == nullptr) {
        bitmap = TexturePool::GetInstance()->GetBitmap();
    }
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

ScopeHdc::ScopeHdc(Window* window) {
    hdc_ = BeginPaint(window->GetHwnd(), &ps_);
    window_ = window;
}

ScopeHdc::~ScopeHdc() {
    EndPaint(window_->GetHwnd(), &ps_);
}

void NormalTactics::Draw(SkCanvas* canvas, SkBitmap* bitmap, const SkRect& rect, const SkPaint& paint) {
    canvas->save();
    canvas->drawBitmapRect(*bitmap, rect, &paint);
    canvas->restore();
}

void Png9Tactics::Draw(SkCanvas* canvas, SkBitmap* bitmap, const SkRect& rect, const SkPaint& paint) {
    if(bitmap == nullptr) {
        return ;
    }

    canvas->save();

    int i = 0, j = 0;
    int x = -1, width = 0;
    int y = -1, height = 0;
    while(i<bitmap->width()) {
        if(*bitmap->getAddr32(i,0)) {
            if(x == -1) {
                x = i;
            }
            width++;
        }
        i++;
    }

    while(j<bitmap->height()) {
        if(*bitmap->getAddr32(0, j)) {
            if(y == -1) {
                y = j;
            }
            height++;
        }
        j++;
    }
    canvas->clipRect(rect);
    SkRect offset_rect = rect;
    offset_rect.fLeft -= 1;
    offset_rect.fTop  -= 1;
    auto center_rect = SkIRect::MakeXYWH(x, y, width, height);
    if(center_rect.left() == 0) {
        center_rect.fLeft = 1;
    }
    if(center_rect.top() == 0) {
        center_rect.fTop = 1;
    }

    canvas->drawBitmapNine(*bitmap, center_rect, offset_rect, &paint);
    canvas->restore();
}

Storage* Storage::GetInstance() {
    static Storage storage;
    return &storage;
}

std::vector<std::string> Storage::GetActualSource(const std::string& source) {
    std::vector<std::string> tokens;
    char tmp_source[1024];
    strncpy_s(tmp_source, source.c_str(), source.size());
    char *p = nullptr;
    char *token = strtok_s(tmp_source, ":", &p);
    while (token != NULL) {
        tokens.push_back(std::string("res\\") + std::string(token));
        token = strtok_s(NULL, ":", &p);
    }
    return tokens;
}
} // namespace ui