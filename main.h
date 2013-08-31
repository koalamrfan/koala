#include "app.h"
#include <windows.h>
#include <tchar.h>

LRESULT CALLBACK KoalaWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, message, wParam, lParam);
}

HINSTANCE koala_hInst;
TCHAR szTitle[] = _T("Koala");
TCHAR szWindowClass[] = _T("Koala");

ATOM KoalaRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEX wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style            = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
    wcex.lpfnWndProc      = KoalaWndProc;
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

BOOL KoalaInitInstance(HINSTANCE hInstance, int nCmdShow, LPTSTR lpCmdLine)
{
    koala_hInst = hInstance; // Store instance handle in our global variable

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

    ui::App::GetInstance()->Init(hWnd, argc, argv);

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
    KoalaRegisterClass(hInstance);

    // Perform application initialization:
    if (!KoalaInitInstance (hInstance, nCmdShow, lpCmdLine)) {
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