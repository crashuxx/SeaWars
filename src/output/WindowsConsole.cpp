#include "WindowsConsole.h"

#include <stdio.h>

WindowsConsole::WindowsConsole() {
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    hBuffer = CreateConsoleScreenBuffer(GENERIC_WRITE | GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

    if (hStdout == INVALID_HANDLE_VALUE || hBuffer == INVALID_HANDLE_VALUE) {
        printf("CreateConsoleScreenBuffer failed - (%d)\n", (int) GetLastError());
        exit(1);
    }

    dwSize.X = 80;
    dwSize.Y = 28;

    SMALL_RECT readRect = {0, 0, (short) (dwSize.X - 1), (short) (dwSize.Y - 1)};

    SetConsoleScreenBufferSize(hStdout, dwSize);
    SetConsoleWindowInfo(hStdout, true, &readRect);

    CONSOLE_CURSOR_INFO lpConsoleCursorInfo = {100, false};
    SetConsoleCursorInfo(hStdout, &lpConsoleCursorInfo);
    SetConsoleCursorInfo(hBuffer, &lpConsoleCursorInfo);
}

WindowsConsole::~WindowsConsole() {
    CloseHandle(hBuffer);
}

int WindowsConsole::getWidth() {
    return dwSize.X;
}

int WindowsConsole::getHeight() {
    return dwSize.Y;
}

void WindowsConsole::swapBuffers() {
    COORD dwBufferCoord = {0, 0};
    SMALL_RECT readRect = {0, 0, (short) (dwSize.X - 1), (short) (dwSize.Y - 1)};

    PCHAR_INFO data = new CHAR_INFO[dwSize.X * dwSize.Y];
    memset(data, 0, sizeof (CHAR_INFO) * dwSize.X * dwSize.Y);

    if (!ReadConsoleOutput(hBuffer, data, dwSize, dwBufferCoord, &readRect)) {
        printf("ReadConsoleOutput failed - (%d)\n", (int) GetLastError());
        exit(1);
    }

    SMALL_RECT writeRect = {0, 0, (short) (dwSize.X - 1), (short) (dwSize.Y - 1)};

    if (!WriteConsoleOutput(hStdout, data, dwSize, dwBufferCoord, &writeRect)) {
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", (int) GetLastError());
        exit(1);
    }

    delete [] data;

    COORD tl = {0, 0};
    CONSOLE_SCREEN_BUFFER_INFO s;
    GetConsoleScreenBufferInfo(hBuffer, &s);
    DWORD written, cells = s.dwSize.X * s.dwSize.Y;
    FillConsoleOutputCharacter(hBuffer, ' ', cells, tl, &written);
    FillConsoleOutputAttribute(hBuffer, s.wAttributes, cells, tl, &written);
    SetConsoleCursorPosition(hBuffer, tl);
}

void WindowsConsole::writeString(int x, int y, std::string text) {
    COORD coord = {(short) x, (short) y};

    DWORD lpNumberOfCharsWritten = 0;

    SetConsoleCursorPosition(hBuffer, coord);
    SetConsoleTextAttribute(hBuffer, FOREGROUND_GREEN);
    WriteConsole(hBuffer, text.c_str(), text.length(), &lpNumberOfCharsWritten, NULL);

    SetConsoleTextAttribute(hBuffer, 0);
}

void WindowsConsole::writeString(int x, int y, std::string text, int color) {
    COORD coord = {(short) x, (short) y};

    DWORD lpNumberOfCharsWritten = 0;

    SetConsoleCursorPosition(hBuffer, coord);
    SetConsoleTextAttribute(hBuffer, color);
    WriteConsole(hBuffer, text.c_str(), text.length(), &lpNumberOfCharsWritten, NULL);

    SetConsoleTextAttribute(hBuffer, 0);
}

void WindowsConsole::write(int x, int y, char c, int color) {
    COORD coord = {(short) x, (short) y};

    DWORD lpNumberOfCharsWritten = 0;

    SetConsoleCursorPosition(hBuffer, coord);
    SetConsoleTextAttribute(hBuffer, color);
    WriteConsole(hBuffer, &c, 1, &lpNumberOfCharsWritten, NULL);

    SetConsoleTextAttribute(hBuffer, 0);
}

void WindowsConsole::setTitle(const char* title) {
    SetConsoleTitle(title);
}
