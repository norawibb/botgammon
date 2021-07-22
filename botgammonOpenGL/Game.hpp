#pragma once
//pragma balls

#include "Functions.hpp"
#pragma comment(lib, "glew32.lib")

class Game {

public:
	Game();
	~Game();

	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	bool initGL();
	void BoardSet();
	void handleKeys(unsigned char key, int x, int y);
	void handleEvents();
	void update();
	void render();
	void clean();
	//Shader loading utility programs
	void printProgramLog(GLuint program);
	void printShaderLog(GLuint shader);

	bool running() { return success; }
	int resolution_x, resolution_y;

private:
	Uint32 rndtime;
	int ballrxv, ballryv;
	bool isRunning, success;
	int mouseX, mouseY;
	SDL_Window* window=NULL;
	SDL_GLContext context;
	SDL_Renderer* renderer;
	GLint gVertexPos2DLocation = -1;
	GLuint gProgramID=0;
	float gProjectionScale = 1.f;
	//GLuint gVBO = 0;
	//GLuint gIBO = 0;
	//bool gRenderQuad = true;
	const Uint8* keystates;
};
