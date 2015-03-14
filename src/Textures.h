#ifndef TEXTURES_H
#define TEXTURES_H
#include <string>
#include <vector>
#include <iostream>
#include "Bitmap.h"

class Textures{

	public:
		Textures(const std::vector<std::string>& files,std::string filePath = std::string(""));
		~Textures();		
		Bitmap* GetTextureByName(std::string name);
		std::vector<Bitmap*>& GetTextures(){ return m_textureBitmaps; }
	private:
		std::vector<Bitmap*> m_textureBitmaps;
		std::vector<std::string> m_textureNames;
};

#endif //TEXTURES_H
