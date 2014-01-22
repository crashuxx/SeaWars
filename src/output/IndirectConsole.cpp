/* 
 * File:   IndirectConsole.cpp
 * Author: c
 * 
 * Created on 22 styczeń 2014, 20:53
 */

#include "IndirectConsole.h"

IndirectConsole::IndirectConsole(iConsole* con, int x, int y, int w, int h) {
    X = x;
    Y = y;
    Width = w;
    Height = h;
    
    console = con;
}

IndirectConsole::~IndirectConsole() {
}

void IndirectConsole::setTitle(const char*) {
}
void IndirectConsole::swapBuffers() {
}

void IndirectConsole::writeString(int x, int y, std::string text) {
    
    if(x >= Width || y >= Height ) {
        return;
    }
    
    console->writeString(X+x, Y+y, text);
}

void IndirectConsole::writeString(int x, int y, std::string text, int color) {
    
    if(x >= Width || y >= Height ) {
        return;
    }
    
    console->writeString(X+x, Y+y, text, color);
}

void IndirectConsole::write(int x, int y, char c, int color) {
    
    if(x >= Width || y >= Height ) {
        return;
    }
    
    console->write(X+x, Y+y, c, color);
}
