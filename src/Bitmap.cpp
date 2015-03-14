#include "Bitmap.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include "png.h"
#include "GL/glew.h"


Bitmap::Bitmap()
{
	//TODO: Assing a defualt(possibly error) texture or generate a random one.
	//What I mean by error, is this texture will signify that an error happend.
}

Bitmap::Bitmap(std::string filePath)
{	
	this->LoadImage(filePath);
	this->InitializeGLTextureBuffer();
}

void Bitmap::InitializeGLTextureBuffer()
{
	glGenTextures(1,&m_textureBufferId);
	BindTexture();	

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,m_width,m_height,0,GL_RGBA,GL_UNSIGNED_BYTE,m_pixels);
	UnbindTexture();
}

void Bitmap::BindTexture() const
{
	glBindTexture(GL_TEXTURE_2D,m_textureBufferId);
}

void Bitmap::UnbindTexture() const
{
	glBindTexture(GL_TEXTURE_2D,0);
}

void Bitmap::LoadImage(std::string filePath)
{
	unsigned char pngSigniture[8];

	FILE* texture = fopen(filePath.c_str(), "rb");
	if(!texture)
	{
		std::cerr << filePath << " failed to be loaded." << std::endl;
		return;
	}
	fread(pngSigniture,1,8,texture);

	if(png_sig_cmp(pngSigniture,0,8))
	{
		std::cerr << filePath << " is not a PNG type file." << std::endl;
		fclose(texture);
		return;
	}

	png_structp pngReadStruct = png_create_read_struct(PNG_LIBPNG_VER_STRING,NULL,NULL,NULL);
	if(pngReadStruct == NULL)
	{
		std::cerr << "Read structure for " << filePath << " was not initalized correctly." << std::endl;
		fclose(texture);
		return;
	}

	png_infop pngInfoStruct = png_create_info_struct(pngReadStruct);
	if(pngInfoStruct == NULL)
	{
		std::cerr << "Info structure for "  << filePath << " was not initalized correctly." << std::endl;
		png_destroy_read_struct(&pngReadStruct,nullptr,nullptr);
		fclose(texture);
		return;
	}

	if(setjmp(png_jmpbuf(pngReadStruct)))
	{
		std::cerr << "Error during I/O of file " << filePath << std::endl;
		png_destroy_read_struct(&pngReadStruct,&pngInfoStruct,nullptr);
		fclose(texture);
		return;
	}

	png_init_io(pngReadStruct,texture);
	png_set_sig_bytes(pngReadStruct,8);
	png_read_info(pngReadStruct,pngInfoStruct);
	
	m_width = png_get_image_width(pngReadStruct,pngInfoStruct);
	m_height = png_get_image_height(pngReadStruct,pngInfoStruct);

	m_pixels = new unsigned char[m_width * m_height * 4];

	png_read_update_info(pngReadStruct,pngInfoStruct);
	
	png_bytep* row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * m_height);
	for(int y = 0; y < m_height; y++)
	{
		row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(pngReadStruct,pngInfoStruct));
	}
	
	png_read_image(pngReadStruct, row_pointers);

        for (int y = 0;y < m_height; y++) 
	{
                for (int x = 0;x < m_width * 4;x+=4)
		{	
			//Bit shifting according to our RGBA format. 
			m_pixels[y * m_width + x + 0] = row_pointers[y][x + 0];
			m_pixels[y * m_width + x + 1] = row_pointers[y][x + 1];
			m_pixels[y * m_width + x + 2] = row_pointers[y][x + 2];
			m_pixels[y * m_width + x + 3] = row_pointers[y][x + 3];
                }
        }

        for (int i = 0;i < m_height; i++)
	{
                free(row_pointers[i]);
	}

	png_destroy_read_struct(&pngReadStruct,&pngInfoStruct,nullptr);
	free(row_pointers);
	fclose(texture);
}

Bitmap::~Bitmap()
{
	glDeleteTextures(1,&m_textureBufferId);
	delete[] m_pixels;
}
