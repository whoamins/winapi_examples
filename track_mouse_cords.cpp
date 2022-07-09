#include <windows.h>
#include <iostream>


int main() {
	HWND hwnd = GetConsoleWindow();
	LPPOINT pPnt = (LPPOINT)malloc(sizeof(*pPnt));

	do {
		system("cls");
		GetCursorPos(pPnt);
		std::cout << pPnt[0].x << std::endl;
		std::cout << pPnt[0].y << std::endl;
		Sleep(100);
	} while (GetKeyState(VK_ESCAPE) >= 0);
}
