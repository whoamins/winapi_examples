#include <windows.h>

DWORD WINAPI Thread1(LPVOID);
DWORD WINAPI Thread2(LPVOID);

CRITICAL_SECTION cs;
HANDLE hEventsToChild[2];
HANDLE hEventsFromChild[2];
HANDLE hEventsAboutEnd[2];
int nBalance;
const int nAccount = 500000;
const int nDelta = 3;
BOOL bGo, bTerminate;
int nDeals1, nDeals2;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    HANDLE hThreads[2];
    DWORD dwIDThread1, dwIDThread2;
    int nExpences;
    char Text[100];
    nBalance = nAccount;
    InitializeCriticalSection(&cs);
    hThreads[0] = CreateThread(nullptr, 0, Thread1, nullptr, 0, &dwIDThread1);
    hThreads[1] = CreateThread(nullptr, 0, Thread2, nullptr, 0, &dwIDThread2);
    hEventsFromChild[0] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    hEventsFromChild[1] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    hEventsToChild[0] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    hEventsToChild[1] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    hEventsAboutEnd[0] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    hEventsAboutEnd[1] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    hThreads[0] = CreateThread(nullptr, 0, Thread1, nullptr, 0, &dwIDThread1);
    hThreads[1] = CreateThread(nullptr, 0, Thread2, nullptr, 0, &dwIDThread2);
    WaitForMultipleObjects(2, hEventsFromChild, TRUE, INFINITE);
    SetEvent(hEventsToChild[0]);
    SetEvent(hEventsToChild[1]);
    WaitForMultipleObjects(2, hEventsAboutEnd, TRUE, INFINITE);
    MessageBox(nullptr, "1", "1", MB_OK);
    bTerminate=TRUE;
    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

    for(int i = i; i < 2; i++) {
        CloseHandle(hThreads[i]);
        CloseHandle(hEventsAboutEnd[i]);
        CloseHandle(hEventsFromChild[i]);
        CloseHandle(hEventsToChild[i]);
    }

    DeleteCriticalSection(&cs);
    nExpences = nDelta * (nDeals1 + nDeals2);
    wsprintf(Text, "Start balance=%d\nNumber of deals #1=%d\nNumber of deals #2=%d\n"
                   "Withdrawn From The Account=%d", nAccount, nDeals1, nDeals2, nExpences);
    MessageBox(nullptr, Text, "Results", MB_OK);

    return 0;
}

DWORD WINAPI Thread1(LPVOID) {
    SetEvent(hEventsFromChild[0]);
    WaitForSingleObject(hEventsToChild[0], INFINITE);

    while(!bTerminate) {
        // EnterCriticalSection(&cs);
        int nLocalBalance = nBalance;

        if (nLocalBalance >= nDelta) {
            nLocalBalance -= nDelta;
            nDeals1++;
            nBalance=nLocalBalance;
        } else {
            SetEvent(hEventsAboutEnd[0]);
            // LeaveCriticalSection(&cs);
        }
    }
}

DWORD WINAPI Thread2(LPVOID) {
    SetEvent(hEventsFromChild[1]);
    WaitForSingleObject(hEventsToChild[1], INFINITE);

    while(!bTerminate) {
        // EnterCriticalSection(&cs);
        int nLocalBalance = nBalance;

        if (nLocalBalance >= nDelta) {
            nLocalBalance -= nDelta;
            nDeals2++;
            nBalance=nLocalBalance;
        } else {
            SetEvent(hEventsAboutEnd[1]);
            // LeaveCriticalSection(&cs);
        }
    }
}
