#include <windows.h>
#include <iostream>

struct GOODS {
    int Num;
    int Price;
};

const int N = 1000;

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    GOODS Stock[N];
    GOODS Unit1, Unit2;
    DWORD Count;

    for(int i = 0; i < N; i++) {
        Stock[i].Num = i + 1;
        Stock[i].Price = (i + 1) * 10;
    }

    HANDLE hFile = CreateFile("C:\\Users\\whoam\\CLionProjects\\win32_book_examples\\stock.data",
                              GENERIC_READ|GENERIC_WRITE, 0, nullptr,
                              CREATE_ALWAYS, 0, nullptr);
    WriteFile(hFile, Stock, sizeof(Stock), &Count, nullptr);
    SetFilePointer(hFile, sizeof(GOODS) * (N-1), nullptr, FILE_BEGIN);
    ReadFile(hFile, &Unit1, sizeof(GOODS), &Count, nullptr);
    CloseHandle(hFile);
    hFile = CreateFile("C:\\Users\\whoam\\CLionProjects\\win32_book_examples\\stock.data",
                       GENERIC_READ, 0, nullptr, OPEN_EXISTING, 0, nullptr);
    ReadFile(hFile, &Unit2, sizeof(GOODS), &Count, nullptr);
    char text[200];
    sprintf(text, "№:%d - Price:%d\n№:%d - Price:%d\n", Unit1.Num, Unit1.Price, Unit2.Num, Unit2.Price);
    MessageBox(nullptr, text, "Info", MB_OK);
    CloseHandle(hFile);

    return 0;
}
