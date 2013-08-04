#include "app.h"
#include <windows.h>
#include <tchar.h>
#include "texture_pool.h"

App* App::GetInstance() {
    static App app;
    return &app;
}

void App::Init(HWND hwnd, uint32_t argc, TCHAR** argv) {
    window_ = std::make_shared<ui::Window>(hwnd);

    main(argc, argv);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

HINSTANCE hInst;
TCHAR szTitle[] = _T("Koala");
TCHAR szWindowClass[] = _T("Koala");



ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style            = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc      = WndProc;
    wcex.cbClsExtra       = 0;
    wcex.cbWndExtra       = 0;
    wcex.hInstance        = hInstance;
    wcex.hIcon            = NULL;
    wcex.hCursor          = ::LoadCursor(0, IDC_ARROW);
    wcex.hbrBackground    = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName     = NULL;
    wcex.lpszClassName    = szWindowClass;
    wcex.hIconSm          = NULL;

    return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow, LPTSTR lpCmdLine)
{
    hInst = hInstance; // Store instance handle in our global variable

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        return FALSE;
    }

    TCHAR* argv[4096];
    uint32_t argc = 0;
    TCHAR exename[1024], *next;
    int exenameLen = GetModuleFileName(NULL, exename, SK_ARRAY_COUNT(exename));
    // we're ignoring the possibility that the exe name exceeds the exename buffer
    (void) exenameLen;
    argv[argc++] = exename;
    TCHAR* arg = _tcstok_s(lpCmdLine, _T(" "), &next);
    while (arg != NULL) {
        argv[argc++] = arg;
        arg = _tcstok_s(NULL, _T(" "), &next);
    }

    App::GetInstance()->Init(hWnd, argc, argv);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);

    MSG msg;

    // Initialize global strings
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow, lpCmdLine)) {
        return FALSE;
    }

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (true) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}