#ifndef WINDOW_H
#define WINDOW_H
#include <string>
#include "SDL.h"


class Window
{

	public:
		/*-------------------------*/
		// 
		// Description: Initializes the window, renderer, texture and OpenGL context.
		//
		// @title: The title that will be assigned to the window.
		// @x: The horizontal position of the window when it is created.
		// @y: The vertical position of the window when it is created.
		// @width: The width of the window.
		// @height: The height of the window.
		// @flags: All of the desired SDL_WindowFlags OR'd together.
		//
		// Return: Void
		/*-------------------------*/
		Window(const char* title,int x,int y,int width, int height,Uint32 flags);
		
		/*-------------------------*/
		// 
		// Description: Frees up all of the memory held by all of the different
		//		window handles and sets their pointers to NULL.
		//
		// Return: Void
		/*-------------------------*/
		void Destroy();

		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The handle to the window.
		/*-------------------------*/
		SDL_Window* GetWindow() const {return m_window; }
		
		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The handle to the renderer.
		/*-------------------------*/
		SDL_Renderer* GetRenderer() const {return m_renderer;}
		
		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The handle to the texture.
		/*-------------------------*/
		SDL_Texture* GetTexture() const {return m_texture;}
		
		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The handle to the GL context created by SDL.
		/*-------------------------*/
		SDL_GLContext GetGLContext() const {return m_GLContext;}

		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The width of the window.
		/*-------------------------*/
		int GetWindowWidth() const { return m_windowWidth; }
		
		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The height to the window.
		/*-------------------------*/
		int GetWindowHeight() const { return m_windowHeight; } 

	private:
		SDL_Window* m_window;
		SDL_Renderer* m_renderer;
		SDL_Texture* m_texture;
		SDL_GLContext m_GLContext;

		int m_windowWidth;
		int m_windowHeight;
};

#endif //WINDOW_H
