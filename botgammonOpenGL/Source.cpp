// Open source code
//	Author: JINORACANTSLEEP

#include "Game.hpp"
#include "Functions.hpp"

/* TODO:
* FIGURE OUT HOW TO STORE GVBO WITH MULTIPLE TRIANGLES
* 
* Make GameObject class and have triangle inherit the class
*	has xpos ypos width height rotation *color
* 
* Continue cleaning up and implementing OpenGL w/ LazyFoo
* Move preferences into cpp hpp files of their own
* Clean up triangles / rendering, vvv
*	Make triangle struct into class with triangle->move() triangle->draw()
*	we have to figure out how to store the arrays of vertices
*	Triangle is also inverted
* View matrix? Right now everything is relative and being adjusted in DrawTriangle() (possible cause for inversion)
* Colors
*	
* 
* Also, a ton of compiler warnings, need to fix those
* 
* Future:
*	Class for entire backgammon instance? so can spawn a ton for natural selection concurrency
*	Somehow allow a setting to throw in human players in either seat
*	Option to visualize 1 or more games
* 
*	Eventually machine learning (duh) but how to implement
*/






Game* game = nullptr;

int main(int argc, const char* argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int frameTime;
	game = new Game();
	Preferences preferences = ReadPreferences();
	game->resolution_x = preferences.resolution_x;
	game->resolution_y = preferences.resolution_y;
	game->init("Botgammon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, preferences.resolution_x, preferences.resolution_y, preferences.fullscreen);

	game->BoardSet();
	while (game->running())
	{
		frameStart = SDL_GetTicks();
		//Handle events on queue
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}