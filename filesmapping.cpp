#include <windows.h>
#include <iostream>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) {
    struct GOODS {
        int Number;
        int Price;
    };

    char Text[100];
    HANDLE hFile = CreateFile("C:\\Users\\whoam\\CLionProjects\\win32_book_examples\\stock.data",
                              GENERIC_READ,
                              0,
                              nullptr,
                              OPEN_EXISTING,
                              0, nullptr);

    HANDLE hMem = CreateFileMapping(hFile, nullptr, PAGE_READONLY, 0, 0, nullptr);
    GOODS *ptr = (GOODS*)MapViewOfFile(hMem, FILE_MAP_READ, 0, 0, 0);
    sprintf(Text, "%d", ptr[0].Number);
    MessageBox(nullptr, Text, "info", MB_OK);
    UnmapViewOfFile(ptr);
    CloseHandle(hMem);
    CloseHandle(hFile);

    return 0;
}