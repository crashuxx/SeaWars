#include <stdio.h>
#include <conio.h>

#include "world.h"

int main(int argc, char **argv)
{
    World world;
	world.getConsole()->setTitle("SeaWars dev");

	world.gameLoop();

	return 0;
}
