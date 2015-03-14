#include <iostream>
#include "SDL.h"
#include "GL/glew.h"
#include "Window.h"
#include "Shader.h"
#include "Textures.h"
#include "OBJLevelLoader.h"
#include "Camera.h"
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

	std::vector<std::string> textureNames;
	textureNames.push_back("test.png");
	textureNames.push_back("64x64.png");

	Textures textures = Textures(textureNames,"textures/");
	OBJLevelLoader level("level.obj");
	Shader shader = Shader("BasicShader.vert","BasicShader.frag");
	Camera camera = Camera(70.0f,(float)(WIDTH/HEIGHT),0.1f,1000);


	while(isRunning)
	{
		//Logic
		//Events
		HandleInput(&isRunning,&event);
		//Rendering
		level.DrawLevel(textures);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		shader.UpdateWorld(camera.GetProjectionMatrix());
		SDL_GL_SwapWindow(window.GetWindow());
	}
}

int main(int argc,char ** argv)
{
	Window window = Window("Inaniloquent Lamprophony", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
			WIDTH,HEIGHT,SDL_WINDOW_OPENGL);	
	
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
