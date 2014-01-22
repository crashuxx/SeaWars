/* 
 * File:   IndirectConsole.h
 * Author: c
 *
 * Created on 22 styczeń 2014, 20:53
 */

#ifndef INDIRECTCONSOLE_H
#define	INDIRECTCONSOLE_H

#include "iConsole.h"

class IndirectConsole : public iConsole {
public:
    IndirectConsole(iConsole*, int, int, int, int);
    ~IndirectConsole();
    
    int getWidth();
    int getHeight();
    
    void setTitle(const char*);
    void swapBuffers();
    void writeString(int x, int y, std::string text);
    void writeString(int x, int y, std::string text, int color);
    void write(int x, int y, char c, int color);
private:
    int X;
    int Y;
    int Width;
    int Height;
    iConsole* console;

};

#endif	/* INDIRECTCONSOLE_H */

