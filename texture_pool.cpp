#include "texture_pool.h"

TexturePool* GetInstance() {
    static TexturePool pool;
    return &pool;
}

void TexturePool::Init(HWND hwnd) {
    hwnd_ = hwnd;
}