#include "../inc/game.h"

int main(int argc, char *argv[])
{
	init();

	while(is_running)
	{
		handle_inputs();
		update();
		render();
	}

	quit();

	return 0;
}

