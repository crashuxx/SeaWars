#ifndef INPUTKEYBOARD_H
#define INPUTKEYBOARD_H

#include <vector>

class InputKeyboard
{
public:
	InputKeyboard();
	~InputKeyboard();

	void handle();

	char read();
	bool fetch(char);

	bool has();
        
        void clear();

private:
	int position;
	std::vector<char> chars;
};

#endif // INPUTKEYBOARD_H
