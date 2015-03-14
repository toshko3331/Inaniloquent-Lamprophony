#ifndef BITMAP_H
#define BITMAP_H
#include <string>
#include "GL/glew.h"
class Bitmap
{
	public:
		
		Bitmap();
		Bitmap(std::string filePath);
		void BindTexture() const;
		void UnbindTexture() const;
		~Bitmap();
		int GetWidth() const { return m_width;}
		int GetHeight() const { return m_height;}
	private:
		void LoadImage(std::string filePath);
		void InitializeGLTextureBuffer();
		int m_width;
		int m_height;
		unsigned char* m_pixels;

		GLuint m_textureBufferId;
};
#endif //BITMAP_H
