#include "clocks.h"
#include <iostream>

char currentTime[100];
HWND hwndMain;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    char ClassName[] = "MainWindow";
    char Title[] = "Current Time";
    MSG msg;
    WNDCLASS wc;

    ZeroMemory(&wc, sizeof wc);

    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = GetStockBrush(LTGRAY_BRUSH);
    wc.lpszClassName = ClassName;
    RegisterClass(&wc);

    hwndMain = CreateWindowEx(WS_EX_TOPMOST, ClassName, Title, WS_CAPTION|WS_SYSMENU,
                              0, 0, XSIZE, YSIZE, HWND_DESKTOP, nullptr, hInst,
                              nullptr);
    ShowWindow(hwndMain, SW_SHOWNORMAL);

    while(GetMessage(&msg, nullptr, 0, 0))
        DispatchMessage(&msg);

    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hwnd, WM_TIMER, OnTimer);
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hwnd, WM_GETMINMAXINFO, OnGetMinMaxInfo);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        default:
            return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT) {
    OutDateTime();
    SetTimer(hwnd, 1, 1000, nullptr);

    return TRUE;
}

void OnPaint(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    SetBkMode(hdc, TRANSPARENT);
    TextOut(hdc, 5, 0, currentTime, static_cast<int>(strlen(currentTime)));
    EndPaint(hwnd, &ps);
}

void OnGetMinMaxInfo(HWND, LPMINMAXINFO lpmmi) {
    // Fixed window size

    lpmmi -> ptMinTrackSize.x = XSIZE;
    lpmmi -> ptMinTrackSize.y = YSIZE;
    lpmmi -> ptMaxTrackSize.x = XSIZE;
    lpmmi -> ptMaxTrackSize.y = YSIZE;
}

void OnDestroy(HWND hwnd) {
    KillTimer(hwnd, 1);
    PostQuitMessage(0);
}

void OnTimer(HWND, UINT) {
    OutDateTime();
}

void OutDateTime() {
    SYSTEMTIME SystemTime;
    GetLocalTime(&SystemTime);
    char buf[100];
    sprintf(buf, "%d.", SystemTime.wDay);
    strcpy(currentTime, buf);
    sprintf(buf, "%d.", SystemTime.wMonth);
    strcat(currentTime, buf);
    sprintf(buf, "%d ", SystemTime.wYear);
    strcat(currentTime, buf);
    sprintf(buf, "%d:", SystemTime.wHour);
    strcat(currentTime, buf);
    sprintf(buf, "%d:", SystemTime.wMinute);
    strcat(currentTime, buf);
    sprintf(buf, "%d", SystemTime.wSecond);
    strcat(currentTime, buf);

    InvalidateRect(hwndMain, nullptr, TRUE);
}


