#include <windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    BYTE Data[26];
    DWORD dwCnt;

    for(int i = 0; i < 26; i++) {
        Data[i] = (BYTE)(i + 'A');
    }

    ZeroMemory(&si, sizeof si);
    si.cb = sizeof si;
    CreateProcess(nullptr, "notepad.exe C:\\Users\\whoam\\angl.txt",
                  nullptr, nullptr, FALSE, 0,
                  nullptr, nullptr, &si, &pi);

    // for (int i = 0; i < 324234234234; i++) {
    //    printf("%d", i);
    // }

    WaitForSingleObject(pi.hProcess, INFINITE);
    HANDLE hFile = CreateFile("C:\\Users\\whoam\\angl.txt", GENERIC_READ|GENERIC_WRITE, 0,
                              nullptr, OPEN_EXISTING, 0, nullptr);
    SetFilePointer(hFile, 0, 0, FILE_END);
    WriteFile(hFile, Data, 26, &dwCnt, nullptr);
    CloseHandle(hFile);

    return 0;
}
