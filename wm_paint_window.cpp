#include <iostream>
#include <Windows.h>
#include <windowsx.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnPaint(HWND);
void OnDestroy(HWND);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    char ClassName[] = "MainWindow";
    char Title[] = "Some program";
    MSG msg;
    WNDCLASS wc;

    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = GetStockBrush(BLACK_BRUSH);
    wc.lpszClassName = ClassName;
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(ClassName, Title, WS_OVERLAPPEDWINDOW, 10, 10, 300, 100,
                             HWND_DESKTOP, nullptr, hInst, nullptr);
    ShowWindow(hwnd, SW_SHOWNORMAL);

    while(GetMessage(&msg, nullptr, 0, 0))
        DispatchMessage(&msg);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void OnPaint(HWND hwnd) {
    char Text[] = "Some text";
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    TextOut(hdc, 5, 30, Text, static_cast<int>(strlen(Text)));
    EndPaint(hwnd, &ps);
}

void OnDestroy(HWND) {
    PostQuitMessage(0);
}

