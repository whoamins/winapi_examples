#include <iostream>
#include <Windows.h>

int Add(int x, int y) {
    return x + y;
}

int main()
{
    char buf[100];
    int res = Add(34, 54);
    wsprintf(buf, "res=%#x", res);
    MessageBox(nullptr, buf, "Result", MB_OK);

    return 0;
}
