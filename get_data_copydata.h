#include <windows.h>
#include <windowsx.h>


#define HANDLE_WM_COPYDATA(hwnd, wParam, lParam, fn) ((fn)((hwnd), (HWND)(wParam), (COPYDATASTRUCT*)(lParam))?1L:0L)

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void OnDestroy(HWND);
BOOL OnCopyData(HWND, HWND, COPYDATASTRUCT*);
