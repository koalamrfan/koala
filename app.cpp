#include "app.h"
#include "texture_pool.h"

namespace ui
{
App* App::GetInstance() {
    static App app;
    return &app;
}

void App::Init(HWND hwnd, uint32_t argc, TCHAR** argv) {
    window_ = std::make_shared<ui::Window>(hwnd);

    main(argc, argv);
}
} // namespace ui