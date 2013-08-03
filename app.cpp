#include "app.h"
#include "texture_pool.h"
#include "ywindow.h"

App* App::GetInstance() {
    static App app;
    return &app;
}

void App::Init(HWND hwnd) {
    hwnd_ = hwnd;

    ui::Window *window = new ui::Window;
    window->Init();
}