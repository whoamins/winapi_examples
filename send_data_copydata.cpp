#include <windows.h>


HWND hwndRcv;
int nData[0x10000];


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof si);
    si.cb = sizeof(si);
    hwndRcv = FindWindow("WinRcv", nullptr);

    if (!hwndRcv) {
        CreateProcess(nullptr, "C:\\Users\\000\\CLionProjects\\winapi_examples\\cmake-build-debug\\lol.exe",
                      nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi);

        while(!hwndRcv)
            hwndRcv = FindWindow("WinRcv", nullptr);
    } else
        MessageBox(nullptr, "Process already created", "Info", MB_OK);

    for (int i = 0; i < 0x10000; i++) {
        nData[i] = i * 10;
    }

    // Copy data to another process
    COPYDATASTRUCT cds;
    cds.dwData = 0;
    cds.cbData = sizeof(nData);
    cds.lpData = (PVOID)nData;
    SendMessage(hwndRcv, WM_COPYDATA, NULL, (LPARAM)&cds);
    return 0;
}
