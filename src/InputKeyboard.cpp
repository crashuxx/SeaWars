#include "InputKeyboard.h"
#include <conio.h>
#include <stdexcept>

InputKeyboard::InputKeyboard() {
    position = 0;
}

InputKeyboard::~InputKeyboard() {
}

void InputKeyboard::handle() {
    chars.clear();
    position = 0;

    while (kbhit()) {
        chars.push_back(getch());
    }
}

char InputKeyboard::read() {
    try {
        position++;
        return chars.at(position - 1);
    } catch (std::out_of_range &e) {
        return 0x00;
    }
}

bool InputKeyboard::fetch(char find) {
    std::vector<char>::iterator charsIterator = chars.begin();

    while (charsIterator != chars.end()) {
        if (*charsIterator == find) {
            chars.erase(charsIterator);
            return true;
        }

        ++charsIterator;
    }

    return false;
}

bool InputKeyboard::has() {
    return (chars.size() - position) > 0;
}

void InputKeyboard::clear() {
    chars.clear();
}
