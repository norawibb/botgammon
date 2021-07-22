#pragma once

#include <SDL.h>
#undef main
#include <gl\glew.h>
#include <SDL_opengl.h>
#include <gl\glu.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include "Triangle.hpp"

struct floatVector2D
{
	float x;
	float y;
};

struct Preferences
{
	bool fullscreen;
	int resolution_x;
	int resolution_y;
};

Preferences ReadPreferences();

