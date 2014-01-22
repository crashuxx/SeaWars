#include <stdio.h>
#include <conio.h>

#include "world.h"

#include "WindowsConsole.h"

int main(int argc, char **argv) {
    WindowsConsole* console = new WindowsConsole();
    console->setTitle("SeaWars dev");

    World world(console);
    world.gameLoop();

    return 0;
}
