#include "get_data_copydata.h"


char ClassName[] = "WinRcv";
char Title[] = "Some Prog";

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
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
    HWND hwnd = CreateWindow(ClassName, Title, WS_OVERLAPPEDWINDOW, 210, 10, 200, 100, HWND_DESKTOP,
                             nullptr, hInst, nullptr);
    ShowWindow(hwnd, SW_NORMAL);

    while(GetMessage(&msg, nullptr, 0, 0)) {
        DispatchMessage(&msg);
    }

    return 0;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        HANDLE_MSG(hwnd, WM_COPYDATA, OnCopyData);
        HANDLE_MSG(hwnd, WM_DESTROY, OnDestroy);
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
}


BOOL OnCopyData(HWND hwnd, HWND, COPYDATASTRUCT* pcds) {
    DWORD dwCnt;
    HANDLE hFile = CreateFile("C:\\Users\\000\\CLionProjects\\winapi_examples\\1.1.txt", GENERIC_WRITE, 0, nullptr,
                              CREATE_ALWAYS, 0, nullptr);
    WriteFile(hFile, pcds->lpData, pcds->cbData, &dwCnt, nullptr);
    CloseHandle(hFile);
    DestroyWindow(hwnd);
    return TRUE;
}

void OnDestroy(HWND) {
    PostQuitMessage(0);
}
