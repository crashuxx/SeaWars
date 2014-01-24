#include <stdio.h>
#include <conio.h>
#include <winsock2.h>

#include "world.h"

#include "WindowsConsole.h"
#include "Net.h"

WSADATA wsaData;

int main(int argc, char **argv) {
    
    WSAStartup(MAKEWORD(2,0), &wsaData);
    
    WindowsConsole* console = new WindowsConsole();
    console->setTitle("SeaWars dev");

    World world(console);
    world.gameLoop();
    
    WSACleanup();
    return 0;
}
