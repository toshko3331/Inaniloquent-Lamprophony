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

	m_renderer = SDL_CreateRenderer(m_window, 
				-1,
				SDL_RENDERER_ACCELERATED);

        if(m_renderer == NULL)
	{
		std::cerr << "Rederer failed to be created in window '" << title  << "'" << std::endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	m_texture = SDL_CreateTexture(m_renderer, 
				SDL_PIXELFORMAT_ARGB8888, 
				SDL_TEXTUREACCESS_STATIC, 
				m_windowWidth, 
				m_windowHeight);

	if(m_texture == NULL)
	{
		std::cerr << "Texture failed to be created in window '" << title  << "'" << std::endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

	m_GLContext = SDL_GL_CreateContext(m_window);

	if(m_GLContext == NULL)
	{
		std::cerr << "OpenGL context failed to be created in window '" << title  << "'" << std::endl;
		SDL_DestroyTexture(m_texture);
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}

}

void Window::Destroy()
{
	SDL_GL_DeleteContext(m_GLContext);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	m_window = NULL;
	m_renderer = NULL;
	m_texture = NULL;
	m_GLContext = NULL;
}


