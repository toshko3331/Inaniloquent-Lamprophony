#include <iostream>
#include "SDL.h"
#include "GL/glew.h"
#include "Window.h"
#define WIDTH 1200
#define HEIGHT 800

//Consider making inline
void HandleInput(bool* isRunning,SDL_Event* event)
{
	while(SDL_PollEvent(event))
	{
		if(event->type == SDL_QUIT )
		{ 
			*isRunning = false;
		}
	}	
}

void MainLoop(const Window& window)
{
	glClearColor(0.25f,0.45f,1.0f,1.0f);

	bool isRunning = true;
	SDL_Event event;

	while(isRunning)
	{
		//Logic
		//Events
		HandleInput(&isRunning,
			&event);
		//Rendering
		glClear(GL_COLOR_BUFFER_BIT);
		SDL_GL_SwapWindow(window.GetWindow());
	}
}

int main(int argc,char ** argv)
{
	Window window = Window("Inaniloquent Lamprophony",
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			WIDTH,
			HEIGHT,
			SDL_WINDOW_OPENGL);	
	
	GLenum GLEWErrorCode = glewInit();
	if(GLEWErrorCode != GLEW_OK)
	{
		std::cerr << "Failed to initialize GLEW: " << glewGetErrorString(GLEWErrorCode) << std::endl;
		return 1;
	}
	
	MainLoop(window);
	window.Destroy();
	SDL_Quit();

	return 0;
}
