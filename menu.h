#include <Windows.h>
#include <windowsx.h>

#define MI_BLUE 100
#define MI_GREEN 101
#define MI_EXIT 102

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND, LPCREATESTRUCT);
void OnDestroy(HWND);
void OnCommand(HWND, int, HWND, UINT);
void OnPaint(HWND);
void OnRButtonDown(HWND, BOOL, INT, INT, UINT);

MSG msg;
int BG = 1;