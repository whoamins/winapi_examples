#include "menu.h"

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    char ClassName[] = "MainWindow";
    char Title[] = "Some program";
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
        HANDLE_MSG(hwnd, WM_CREATE, OnCreate);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        HANDLE_MSG(hwnd, WM_COMMAND, OnCommand);
        HANDLE_MSG(hwnd, WM_PAINT, OnPaint);
        HANDLE_MSG(hwnd, WM_RBUTTONDOWN, OnRButtonDown);
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT) {
    LPCSTR menuOptions[4] = {"Background", "Blue", "Green", "Exit"};
    HMENU hMenu = CreateMenu();
    HMENU hPopupMenu = CreatePopupMenu();
    AppendMenu(hPopupMenu, MF_STRING, MI_BLUE, menuOptions[1]);
    AppendMenu(hPopupMenu, MF_STRING, MI_GREEN, menuOptions[2]);
    AppendMenu(hPopupMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(hPopupMenu, MF_STRING, MI_EXIT, menuOptions[3]);
    AppendMenu(hMenu, MF_POPUP, reinterpret_cast<UINT_PTR>(hPopupMenu), menuOptions[0]);
    SetMenu(hwnd, hMenu);

    return TRUE;
}

void OnDestroy(HWND) {
    PostQuitMessage(0);
}

void OnCommand(HWND hwnd, int id, HWND, UINT) {
    if (id == MI_BLUE) {
        BG = 1;
        InvalidateRect(hwnd, nullptr, TRUE);
    } else if (id == MI_GREEN) {
        BG = 2;
        InvalidateRect(hwnd, nullptr, TRUE);
    } else if (id == MI_EXIT) {
        DestroyWindow(hwnd);
    }
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

void OnRButtonDown(HWND hwnd, BOOL, int x, int y, UINT) {
    LPCSTR menuOptions[3] = {"Background: Blue", "Background: Green", "Background: Exit"};
    RECT rect;
    HMENU hPopupMenu = CreatePopupMenu();
    AppendMenu(hPopupMenu, MF_STRING, MI_BLUE, menuOptions[0]);
    AppendMenu(hPopupMenu, MF_STRING, MI_GREEN, menuOptions[1]);
    AppendMenu(hPopupMenu, MF_SEPARATOR, 0, nullptr);
    AppendMenu(hPopupMenu, MF_STRING, MI_EXIT, menuOptions[2]);
    GetWindowRect(hwnd, &rect);
    TrackPopupMenu(hPopupMenu, TPM_LEFTALIGN|TPM_LEFTBUTTON, msg.pt.x, msg.pt.y, 0, hwnd, nullptr);
}
