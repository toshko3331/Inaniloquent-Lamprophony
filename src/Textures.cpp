#include "Textures.h"
#include <vector>
#include <string>
#include "Bitmap.h"
Textures::Textures(const std::vector<std::string>& files,std::string filePath)
{
	for(unsigned int i = 0;i < files.size();i++)
	{
		std::string name = filePath + files.at(i);
		m_textureBitmaps.push_back(new Bitmap(name));
		m_textureNames.push_back(name);
	}
}

Textures::~Textures()
{
	for(unsigned int i = 0; i < m_textureBitmaps.size();i++)
	{
		delete m_textureBitmaps.at(i);
	}
}

Bitmap* Textures::GetTextureByName(std::string name)
{
	for(unsigned int i = 0;i < m_textureBitmaps.size();i++)
	{
		if(name == m_textureNames.at(i))
		{
			return m_textureBitmaps.at(i);
		}
	}
	//TODO:Return an error texture, this way we don't have to crash the program (i.e. the source engine's red "ERROR" texture).
	std::cout << "No texture found in texture array." << std::endl;
	exit(EXIT_FAILURE);
}	
