#include "app.h"
#include "texture_pool.h"

App* App::GetInstance() {
    static App app;
    return &app;
}

void App::Init(HWND hwnd) {
    hwnd_ = hwnd;
}