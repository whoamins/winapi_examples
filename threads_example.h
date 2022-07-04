#include <windows.h>
#include <windowsx.h>


#define MI_EXIT 101
#define MI_NEW 102

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnCommand(HWND, int, HWND, UINT);
void OnDestroy(HWND);
void OnPaint(HWND);
DWORD WINAPI Thread(LPVOID);
LRESULT CALLBACK ThreadWndProc(HWND, UINT, WPARAM, LPARAM);
void ThreadOnDestroy(HWND);
void ThreadOnPaint(HWND);




