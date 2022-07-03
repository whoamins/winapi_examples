#include <windows.h>
#include <windowsx.h>

#define XSIZE 140
#define YSIZE 50

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL OnCreate(HWND, LPCREATESTRUCT);
void OnPaint(HWND);
void OnTimer(HWND, UINT);
void OnGetMinMaxInfo(HWND, LPMINMAXINFO);
void OnDestroy(HWND);
void OutDateTime();
