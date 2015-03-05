#include "Window.h"
#include <string>
#include <iostream>
#include "SDL.h"

Window::Window(const char* title,int x,int y,int width, int height,Uint32 flags) : m_windowWidth(width), m_windowHeight(height)
{

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 
			3); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 
			2); 
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, 
			SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,
			8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,
			8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,
			8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,
			8);

	m_window =  SDL_CreateWindow(title, 
				x, 
				y, 
				width, 
				height,
				flags);

	if(m_window == NULL)
	{
		std::cerr << "Window failed to be created with title '" << title  << "'" << std::endl;
		SDL_Quit();	
	}

	m_GLContext = SDL_GL_CreateContext(m_window);

	if(m_GLContext == NULL)
	{
		std::cerr << "OpenGL context failed to be created in window '" << title  << "'" << std::endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	m_isDestroyed = false;
}

Window::~Window()
{
	if(m_isDestroyed)
	{
		return;
	}
	else{
		this->Destroy();
	}
}

void Window::Destroy()
{
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyWindow(m_window);

	m_window = NULL;
	m_GLContext = NULL;
	
	m_isDestroyed = true;
}


