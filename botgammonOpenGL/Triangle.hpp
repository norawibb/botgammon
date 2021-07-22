#pragma once

#include <SDL.h>
#include "Functions.hpp"

struct IsoTriangle
{
	int x;
	int y;
	int w;
	int h;
	int r;
	//SDL_Color color;
};

void SDL_RenderFillIsoTriangle(SDL_Renderer* renderer, IsoTriangle* triangle);

void DrawTriangle(GLuint gProgramID, GLint gVertexPos2DLocation, IsoTriangle* triangle);