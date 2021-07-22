#include "Game.hpp"

SDL_Rect leftR, rightR, midR, ballR;
IsoTriangle* testTriangle1;
IsoTriangle* testTriangle2;



Game::Game()
{
	// Default resolution
	resolution_x = 800;
	resolution_y = 600;

	rndtime = 0;
	ballrxv = 2;
	ballryv = 2;
	isRunning = false;
}
Game::~Game()
{}

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	//Initialization flag
	success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		std::cout << "SDL Subsystems Initialized" << std::endl;
		//Use OpenGL 3.1 core
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		//Create window
		window = SDL_CreateWindow(title, xpos, ypos, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			std::cout << "Window created" << std::endl;
			//Create context
			context = SDL_GL_CreateContext(window);
			if (context == NULL)
			{
				printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize GLEW
				glewExperimental = GL_TRUE;
				GLenum glewError = glewInit();
				if (glewError != GLEW_OK)
				{
					printf("Error initializing GLEW! %s\n", glewGetErrorString(glewError));
				}

				//Use Vsync
				if (SDL_GL_SetSwapInterval(1) < 0)
				{
					printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
				}

				//Initialize OpenGL
				if (!initGL())
				{
					printf("Unable to initialize OpenGL!\n");
					success = false;
				}
			}
		}
	}

	return success;
	/*int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems Initialised" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			std::cout << "Window created" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			std::cout << "Renderer created" << std::endl;
		}

		// Get the keystates
		keystates = SDL_GetKeyboardState(NULL);

		isRunning = true;
	}
	else {
		isRunning = false;
	}*/
}
bool Game::initGL()
{
	std::cout << "Initializing GLEW" << std::endl;
	//Success flag
	success = true;

	//Generate program
	gProgramID = glCreateProgram();

	//Create vertex shader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	//Get vertex source
	const GLchar* vertexShaderSource[] =
	{
		"#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
	};

	//Set vertex source
	glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

	//Compile vertex source
	glCompileShader(vertexShader);

	//Check vertex shader for errors
	GLint vShaderCompiled = GL_FALSE;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
	if (vShaderCompiled != GL_TRUE)
	{
		printf("Unable to compile vertex shader %d!\n", vertexShader);
		printShaderLog(vertexShader);
		success = false;
	}
	else
	{
		std::cout << "Vertex shader compiled" << std::endl;
		//Attach vertex shader to program
		glAttachShader(gProgramID, vertexShader);


		//Create fragment shader
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		//Get fragment source
		const GLchar* fragmentShaderSource[] =
		{
			"#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 1.0, 1.0, 1.0 ); }"
		};

		//Set fragment source
		glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

		//Compile fragment source
		glCompileShader(fragmentShader);

		//Check fragment shader for errors
		GLint fShaderCompiled = GL_FALSE;
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
		if (fShaderCompiled != GL_TRUE)
		{
			printf("Unable to compile fragment shader %d!\n", fragmentShader);
			printShaderLog(fragmentShader);
			success = false;
		}
		else
		{

			std::cout << "Fragment shader compiled" << std::endl;
			//Attach fragment shader to program
			glAttachShader(gProgramID, fragmentShader);


			//Link program
			glLinkProgram(gProgramID);

			//Check for errors
			GLint programSuccess = GL_TRUE;
			glGetProgramiv(gProgramID, GL_LINK_STATUS, &programSuccess);
			if (programSuccess != GL_TRUE)
			{
				printf("Error linking program %d!\n", gProgramID);
				printProgramLog(gProgramID);
				success = false;
			}
			else
			{

				//Initialize Projection Matrix
				glMatrixMode(GL_PROJECTION);
				glLoadIdentity();
				glOrtho(0.0, resolution_x, resolution_y, 0.0, 1.0, -1.0);
				
				//Initialize Modelview Matrix
				glMatrixMode(GL_MODELVIEW);
				glLoadIdentity();
				//Initialize clear color
				glClearColor(0.f, 0.f, 0.f, 1.f);

				std::cout << "Program success" << std::endl;
				//Get vertex attribute location
				gVertexPos2DLocation = glGetAttribLocation(gProgramID, "LVertexPos2D");
				if (gVertexPos2DLocation == -1)
				{
					printf("LVertexPos2D is not a valid glsl program variable!\n");
					success = false;
				}
				else
				{

					
				}
			}
		}
	}

	return success;
}


void Game::handleKeys(unsigned char key, int x, int y)
{	// CUSTOM CODE HERE
	std::cout << "Key: " << key << " | X: " << x << " | Y: " << y << std::endl;
	//Toggle quad
	if (key == 'q')
	{
		//Cycle through projection scales
		if (gProjectionScale == 1.f)
		{
			//Zoom out
			gProjectionScale = 2.f;
		}
		else if (gProjectionScale == 2.f)
		{
			//Zoom in
			gProjectionScale = 0.5f;
		}
		else if (gProjectionScale == 0.5f)
		{
			//Regular zoom
			gProjectionScale = 1.f;
		}

		//Update projection matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0, resolution_x * gProjectionScale, resolution_y * gProjectionScale, 0.0, 1.0, -1.0);
	}
}


void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_QUIT:
		isRunning = false;
		break;
	case SDL_TEXTINPUT:
		mouseX = 0, mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);
		handleKeys(event.text.text[0], mouseX, mouseY);

	default:
		break;
	}
	//continuous-response keys
	/*if (keystates[SDL_SCANCODE_UP])
	{
		std::cout << "ass" << std::endl;
	}
	if (keystates[SDL_SCANCODE_DOWN])
	{
		std::cout << "balls" << std::endl;
	}*/
}

void Game::BoardSet() // size objects and place them
{ // all sizes scale with resolution
	leftR.h = resolution_y / 5;
	leftR.w = resolution_x / 50;
	leftR.x = 0;
	leftR.y = (resolution_y / 2) - (leftR.h / 2);

	rightR.h = resolution_y / 5;
	rightR.w = resolution_x / 50;
	rightR.x = resolution_x - rightR.w;
	rightR.y = (resolution_y / 2) - (leftR.h / 2);

	midR.h = resolution_y;
	midR.w = resolution_x / 175;
	midR.x = (resolution_x / 2) - (midR.w / 2);
	midR.y = 0;

	ballR.h = resolution_y / 30;
	ballR.w = resolution_y / 30;
	ballR.x = (resolution_x / 2) - (ballR.w / 2);
	ballR.y = (resolution_y / 2) - (ballR.h / 2);

	testTriangle1 = new IsoTriangle(resolution_x / 4, resolution_y / 2, resolution_y / 8, resolution_y / 3, 0);
	testTriangle2 = new IsoTriangle(resolution_x * 3 / 4, resolution_y / 2, resolution_y / 8, resolution_y / 3, 0);

	//testTriangle.color = SDL_Color{ 255, 0, 0 };
}


void Game::update()
{
	
	rndtime++;
	testTriangle1->rotation = (testTriangle1->rotation + 1) % 360;
	testTriangle2->rotation = (testTriangle2->rotation - 1) % 360;
	//std::cout << testTriangle.r << std::endl;
	/*if (rndtime >= 250)
	{
		if ((ballR.y >= (resolution_y - ballR.h)) || (ballR.y <= 0)) // Ball reflects off of top and bottom, reverse y velocity
			ballryv = -ballryv;
		if (((ballR.x + ballR.w) >= rightR.x) && (!((ballR.y > (rightR.y + rightR.h)) || ((ballR.y + ballR.h) < rightR.y))))
			ballrxv = -std::abs(ballrxv);
		if ((ballR.x <= (leftR.x + leftR.w)) && (!((ballR.y > (leftR.y + leftR.h)) || ((ballR.y + ballR.h) < leftR.y))))
			ballrxv = std::abs(ballrxv);

		ballR.x += ballrxv;
		ballR.y += ballryv;
	}*/
	



}

void Game::render()
{

	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	//Reset modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Move to center of the screen
	glTranslatef(resolution_x / 2.f, resolution_y / 2.f, 0.f);
	testTriangle1->Draw(gProgramID, gVertexPos2DLocation);
	testTriangle2->Draw(gProgramID, gVertexPos2DLocation);

	SDL_GL_SwapWindow(window);
	/*
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	// add things to render here
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &leftR);
	SDL_RenderFillRect(renderer, &rightR);
	SDL_RenderFillRect(renderer, &midR);
	SDL_RenderFillRect(renderer, &ballR);

	SDL_RenderFillIsoTriangle(renderer, &testTriangle);

	SDL_RenderPresent(renderer);
	*/

}

void Game::clean()
{
	//Deallocate program
	glDeleteProgram(gProgramID);

	//Destroy window	
	SDL_DestroyWindow(window);
	window = NULL;

	//Quit SDL subsystems
	SDL_Quit();
	std::cout << "Game Cleaned" << std::endl;
}


void Game::printProgramLog(GLuint program)
{
	//Make sure name is shader
	if (glIsProgram(program))
	{
		//Program log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetProgramInfoLog(program, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a program\n", program);
	}
}

void Game::printShaderLog(GLuint shader)
{
	//Make sure name is shader
	if (glIsShader(shader))
	{
		//Shader log length
		int infoLogLength = 0;
		int maxLength = infoLogLength;

		//Get info string length
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

		//Allocate string
		char* infoLog = new char[maxLength];

		//Get info log
		glGetShaderInfoLog(shader, maxLength, &infoLogLength, infoLog);
		if (infoLogLength > 0)
		{
			//Print Log
			printf("%s\n", infoLog);
		}

		//Deallocate string
		delete[] infoLog;
	}
	else
	{
		printf("Name %d is not a shader\n", shader);
	}
}