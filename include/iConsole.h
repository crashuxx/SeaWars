#ifndef ISCREEN_H
#define ISCREEN_H

#include <string>

class iConsole
{
public:
	virtual ~iConsole() {}
        
        virtual int getWidth() = 0;
        virtual int getHeight() = 0;

	virtual void swapBuffers() = 0;
	virtual void writeString(int x, int y, std::string text) = 0;
	virtual void writeString(int x, int y, std::string text, int color) = 0;
	virtual void write(int x, int y, char c, int color) = 0;
};

#endif // ISCREEN_H
