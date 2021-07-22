#pragma once

#include <SDL.h>
#include "Functions.hpp"

/*struct IsoTriangle
{
	int x;
	int y;
	int w;
	int h;
	int r;
	//SDL_Color color;
};*/

//void SDL_RenderFillIsoTriangle(SDL_Renderer* renderer, IsoTriangle* triangle);

//void DrawTriangle(GLuint gProgramID, GLint gVertexPos2DLocation, IsoTriangle* triangle);

class IsoTriangle {
public:
	IsoTriangle();
	IsoTriangle(int x, int y, int w, int h, int r);
	~IsoTriangle();
	void Draw(GLuint gProgramID, GLint gVertexPos2DLocation); // FIGURE OUT IF WE NEED TO PASS THESE THINGS OR NOT
	int xpos=0; // public or private?? idk
	int ypos=0;
	int width=0;
	int height=0;
	int rotation=0;
	//SDL_Color color;
private:
	GLuint gVBO = 0;
	GLuint gIBO = 0;
	GLfloat triVertexData[6] =
	{
		-0.5f, -0.5f, //v1x, v1y
		 0.5f, -0.5f, //v2x, 
		 0.5f,  0.5f
	};
	//IBO data
	GLuint triIndexData[3] = { 0, 1, 2 };
};