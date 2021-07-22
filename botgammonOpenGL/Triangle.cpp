#include "Triangle.hpp"


void SDL_RenderFillIsoTriangle(SDL_Renderer* renderer, IsoTriangle* triangle) {
	//SDL_SetRenderDrawColor(renderer, triangle->color.r, triangle->color.g, triangle->color.b, triangle->color.a);
	floatVector2D v1, v2, v3;
	v1.x = triangle->x - (cos(triangle->r * M_PI / 180.0f)*triangle->w);
	v1.y = triangle->y - (sin(triangle->r * M_PI / 180.0f)*triangle->w);
	v2.x = triangle->x + (sin(triangle->r * M_PI / 180.0f)*triangle->h);
	v2.y = triangle->y - (cos(triangle->r * M_PI / 180.0f)*triangle->h);
	v3.x = triangle->x + (cos(triangle->r * M_PI / 180.0f) * triangle->w);
	v3.y = triangle->y + (sin(triangle->r * M_PI / 180.0f) * triangle->w);
	SDL_RenderDrawLine(renderer, v1.x, v1.y, v2.x, v2.y);
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderDrawLine(renderer, v2.x, v2.y, v3.x, v3.y);
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderDrawLine(renderer, v3.x, v3.y, v1.x, v1.y);
}


GLuint gVBO = 0;
GLuint gIBO = 0;
GLfloat triVertexData[] =
{
	-0.5f, -0.5f, //v1x, v1y
	 0.5f, -0.5f, //v2x, 
	 0.5f,  0.5f
};
//IBO data
GLuint triIndexData[] = { 0, 1, 2 };

void DrawTriangle(GLuint gProgramID, GLint gVertexPos2DLocation, IsoTriangle* triangle) {
	floatVector2D v1, v2, v3;
	triVertexData[0] = ((triangle->x - (cos(triangle->r * M_PI / 180.0f) * triangle->w))/800-1);
	triVertexData[1] = -((triangle->y - (sin(triangle->r * M_PI / 180.0f) * triangle->w))/450-1);
	triVertexData[2] = ((triangle->x + (sin(triangle->r * M_PI / 180.0f) * triangle->h)) / 800-1);
	triVertexData[3] = -((triangle->y - (cos(triangle->r * M_PI / 180.0f) * triangle->h)) / 450-1);
	triVertexData[4] = ((triangle->x + (cos(triangle->r * M_PI / 180.0f) * triangle->w)) / 800-1);
	triVertexData[5] = -((triangle->y + (sin(triangle->r * M_PI / 180.0f) * triangle->w)) / 450-1);
	//std::cout << gVBO << std::endl;
	//Create VBO
	glGenBuffers(1, &gVBO);
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glBufferData(GL_ARRAY_BUFFER, 2 * 3 * sizeof(GLfloat), triVertexData, GL_STATIC_DRAW); // 2 * 3 is sizeof(triVertexData[])

	//Create IBO
	glGenBuffers(1, &gIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3 * sizeof(GLuint), triIndexData, GL_STATIC_DRAW);

	
	//Bind program
	glUseProgram(gProgramID);

	//Enable vertex position
	glEnableVertexAttribArray(gVertexPos2DLocation);

	//Set vertex data
	glBindBuffer(GL_ARRAY_BUFFER, gVBO);
	glVertexAttribPointer(gVertexPos2DLocation, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

	//Set index data and render
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIBO);
	glDrawElements(GL_TRIANGLE_FAN, 3, GL_UNSIGNED_INT, NULL);

	//Disable vertex position
	glDisableVertexAttribArray(gVertexPos2DLocation);

	//Unbind program
	glUseProgram(NULL);
}