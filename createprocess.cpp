#include "createprocess.h"

char ClassName[] = "MainWindow";
char Title[] = "Some Title";

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    MSG Msg;
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = GetStockBrush(LTGRAY_BRUSH);
    wc.lpszClassName = ClassName;
    RegisterClass(&wc);

    HWND hwnd = CreateWindow(ClassName, Title, WS_OVERLAPPEDWINDOW, 100, 300, 310, 100, HWND_DESKTOP,
                             nullptr, hInst, nullptr);
    ShowWindow(hwnd, SW_NORMAL);

    while(GetMessage(&Msg, nullptr, 0, 0))
        DispatchMessage(&Msg);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) {
        HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

void OnDestroy(HWND) {
    PostQuitMessage(0);
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT) {
    LPCSTR menuOptions[4] = {"NewProcess", "Start New Process", "Green", "Exit"};
    HMENU hMenu = CreateMenu();
    HMENU hPopupMenu = CreatePopupMenu();
    AppendMenu(hPopupMenu, MF_STRING, MI_NEW, menuOptions[1]);
    AppendMenu(hPopupMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(hPopupMenu, MF_STRING, MI_EXIT, menuOptions[3]);
    AppendMenu(hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hPopupMenu), menuOptions[0]);
    SetMenu(hwnd, hMenu);

    return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND, UINT) {
    if (id == MI_NEW) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof si);
        si.cb = sizeof(si);
        BOOL bSuccess = CreateProcess("C:\\Windows\\System32\\calc.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);

        if (bSuccess) {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
        }
    } else if (id == MI_EXIT)
        DestroyWindow(hwnd);
}

void OnPaint(HWND hwnd) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(hwnd, &ps);
    HBRUSH BlueBrush = CreateSolidBrush(RGB(100, 100, 255));
    HBRUSH GreenBrush = CreateSolidBrush(RGB(100, 255, 100));

    if (BG == 1) {
        FillRect(hdc, &ps.rcPaint, BlueBrush);
    } else if (BG == 2) {
        FillRect(hdc, &ps.rcPaint, GreenBrush);
    }

    EndPaint(hwnd, &ps);
}

