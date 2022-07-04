#include "threads_example.h"


char ClassName[] = "MainWindow";
char Title[] = "Some Example";
char ThreadClassName[] = "Thread";
char ThreadTitle[] = "SomeThread";

HINSTANCE hInstance;
HANDLE hThread;
int Count;


int WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, int) {
    MSG msg;
    hInstance = hInst;
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof wc);
    wc.lpfnWndProc = WndProc;
    wc.lpszClassName = ClassName;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    RegisterClass(&wc);
}
