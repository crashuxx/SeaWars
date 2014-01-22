#ifndef WINDOWCONSOLE_H
#define WINDOWCONSOLE_H

#include "iConsole.h"
#include <windows.h>

class WindowsConsole : public iConsole
{
public:
	WindowsConsole();
	~WindowsConsole();
        
        int getWidth();
        int getHeight();

	void setTitle(const char*);
	void swapBuffers();
	void writeString(int x, int y, std::string text);
	void writeString(int x, int y, std::string text, int color);
	void write(int x, int y, char c, int color);

private:
	COORD dwSize;

	HANDLE hStdout;
	HANDLE hBuffer;
};

#endif // WINDOWCONSOLE_H
