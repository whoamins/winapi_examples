#include <windows.h>
#include <windowsx.h>

DWORD WINAPI Thread1(LPVOID);
DWORD WINAPI Thread2(LPVOID);

HANDLE mutex;
int nBalance;
const int nAccount = 500000;
const int nDelta = 1;
BOOL bGo, bTerminate;
int nDeals1, nDeals2;


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    HANDLE hThreads[2];
    DWORD dwIDThread1, dwIDThread2;
    int nExpences;
    char Text[100];
    nBalance = nAccount;
    CreateMutex(nullptr, FALSE, nullptr);
    hThreads[0] = CreateThread(nullptr, 0, Thread1, nullptr, 0, &dwIDThread1);
    hThreads[1] = CreateThread(nullptr, 0, Thread2, nullptr, 0, &dwIDThread2);
    MessageBox(nullptr, "Start", "Command", MB_OK);
    bGo = TRUE;
    while(nBalance >= nDelta);
    bTerminate = TRUE;
    WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);
    CloseHandle(hThreads[0]);
    CloseHandle(hThreads[1]);
    CloseHandle(mutex);
    nExpences = nDelta * (nDeals1 + nDeals2); // Expences >= Account. wtf?
    wsprintf(Text, "Start balance=%d\nNumber of deals #1=%d\nNumber of deals #2=%d\n"
                   "Withdrawn From The Account=%d", nAccount, nDeals1, nDeals2, nExpences);
    MessageBox(nullptr, Text, "Results", MB_OK);
}


DWORD WINAPI Thread1(LPVOID) {
        while(!bTerminate) {
            if(bGo) {
                WaitForSingleObject(mutex, INFINITE);
                int nLocalBalance = nBalance;

                if (nLocalBalance >= nDelta) {
                    nLocalBalance -= nDelta;
                    nDeals1++;
                    nBalance = nLocalBalance;
                }
                ReleaseMutex(mutex);
            }
        }

        return 0;
}

DWORD WINAPI Thread2(LPVOID) {
        while(!bTerminate) {
            if(bGo) {
                WaitForSingleObject(mutex, INFINITE);
                int nLocalBalance = nBalance;

                if (nLocalBalance >= nDelta) {
                    nLocalBalance -= nDelta;
                    nDeals2++;
                    nBalance = nLocalBalance;
                }
                ReleaseMutex(mutex);
            }
        }

        return 0;
}
