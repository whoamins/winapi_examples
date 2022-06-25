#include <iostream>
#include <Windows.h>
#include <windowsx.h>

LRESULT CALLBACK WndProc(
        HWND,
        UINT,
        WPARAM,
        LPARAM
);

void OnDestroy(HWND);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    char ClassName[] = "MainWindow";
    char Title[] = "Some Window";
    MSG Msg;
    WNDCLASS wc;

    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(nullptr, IDI_INFORMATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
    wc.lpszClassName = ClassName;
    RegisterClass(&wc);

    HWND hwnd =  CreateWindow(ClassName, Title, WS_OVERLAPPEDWINDOW, 300, 300, 300, 100, HWND_DESKTOP,
                              nullptr, hInst, nullptr);
    ShowWindow(hwnd, SW_SHOWNORMAL);

    while(GetMessage(&Msg, nullptr, 0, 0))
        DispatchMessage(&Msg);

    return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    // How I can use it with if/else block? I have this error:
    // 'case' statement not in switch statement

    switch (msg) {
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        default:
            return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
}


void OnDestroy(HWND hwnd) {
    MessageBox(nullptr, "Bye!", ":(", MB_OK);
    PostQuitMessage(0);
}
