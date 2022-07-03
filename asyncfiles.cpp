#include <windows.h>
#include <iostream>

const int N = 0x1000;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    char FileName[] = "C:\\Users\\whoam\\CLionProjects\\win32_book_examples\\test.data";
    char Text[100];
    DWORD Count;
    OVERLAPPED ovlp;
    ZeroMemory(&ovlp, sizeof ovlp);
    PINT pBuffer = (PINT)VirtualAlloc(nullptr, N * 4, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);

    for (int i = 0; i < N; i++) {
        pBuffer[i] = i;
    }

    HANDLE hFile = CreateFile(FileName, GENERIC_READ|GENERIC_WRITE,
                              0, nullptr, CREATE_ALWAYS, 0, nullptr);
    WriteFile(hFile, pBuffer, N*4, &Count, nullptr);
    ZeroMemory(pBuffer, sizeof pBuffer);
    CloseHandle(hFile);

    hFile = CreateFile(FileName, GENERIC_READ, 0, nullptr,
                       OPEN_EXISTING, FILE_FLAG_OVERLAPPED|FILE_FLAG_NO_BUFFERING, nullptr);
    pBuffer[N - 1] = 0x12345678;
    ReadFile(hFile, pBuffer, N*4, &Count, &ovlp);
    sprintf(Text, "pBuffer[...]=%d", pBuffer[N-1]);
    MessageBox(nullptr, Text, "Async reading", MB_OK);
    sprintf(Text, "pBuffer[...]=0x%X", pBuffer[N-1]);
    MessageBox(NULL, Text, "Reading with delay", MB_OK);
    VirtualFree(pBuffer, 0, MEM_RELEASE);
    CloseHandle(hFile);

    return 0;
}