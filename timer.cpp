#include "timer.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpstr, int) {
    int time = atoi(lpstr);
    SetTimer(nullptr, 1, time * 1000, TimerProc);
    MSG msg;

    while(GetMessage(&msg, nullptr, 0, 0)) {
        DispatchMessage(&msg);
    }

    return 0;
}

VOID CALLBACK TimerProc(HWND, UINT, UINT_PTR idEvent, DWORD) {
    char text[100];
    KillTimer(nullptr, idEvent);
    sprintf(text, "Time is up!", time);
    MessageBox(nullptr, text, "Ping-ping", MB_ICONINFORMATION);
    PostQuitMessage(0);
}
