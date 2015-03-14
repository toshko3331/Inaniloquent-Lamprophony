#include "OBJLevelLoader.h"
#include <iostream>
#include "GameObject.h"
#include "Textures.h"

void OBJLevelLoader::AppendVertex(std::string source)
{
	for(int i = 0; i < 3;i++)
	{
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);

		m_vertecies.push_back(((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str())));
		source = source.erase(0,secondDelimiterLocation);
	}
}

void OBJLevelLoader::AppendTexel(std::string source)
{
	for(int i = 0; i < 2;i++)
	{
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);
  
		m_texelCoords.push_back((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str()));
		source = source.erase(0,secondDelimiterLocation);
	}
}

void OBJLevelLoader::AppendNormal(std::string source)
{
	for(int i = 0; i < 3;i++)
	{
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);
    
		m_normals.push_back(((float)atof((source.substr(firstDelimiterLocation + 1,secondDelimiterLocation - firstDelimiterLocation - 1)).c_str())));
		source = source.erase(0,secondDelimiterLocation);
	}	
}


void OBJLevelLoader::AssignTexture(GameObject* object,std::string materialName)
{
	if(m_MTLFile.is_open())
	{
		materialName = materialName.substr(7,std::string::npos);
		std::string line("");
		bool quitWhile = false;
		while(getline(m_MTLFile,line))
		{
			if(line.compare(std::string("newmtl ") + materialName) == 0)
			{
				quitWhile = true;	
				break;
			}	
		}
		if(quitWhile == true)
		{
			while(getline(m_MTLFile,line))
			{
				if(line.compare(0,6,"map_Kd") == 0)
				{
					object->SetTextureName(line.substr(7,std::string::npos));
					break;
				}
			}
		}
		else
		{
			std::cerr << materialName << " was not found in material file." << std::endl;
		}
	}else
	{
		//TODO:Return default texture.
		std::cerr << "MTL file is not open for extractio of texture name." << std::endl;
		return;
	}
}


void OBJLevelLoader::AppendFace(GameObject* object,std::string source)
{
	for(int i = 0; i < 3;i++)
	{
		int firstDelimiterLocation = source.find_first_of(' ');
		int secondDelimiterLocation = source.find_first_of(' ',firstDelimiterLocation+1);
		int firstSlashDelimiterLocation = source.find_first_of('/');
		int secondSlashDelimiterLocation = source.find_first_of('/',firstSlashDelimiterLocation+1);
		object->AddFace((atoi((source.substr(firstDelimiterLocation + 1,firstSlashDelimiterLocation - firstDelimiterLocation - 1)).c_str())) - 1);
		object->AddFace((atoi((source.substr(firstSlashDelimiterLocation + 1,secondDelimiterLocation - firstSlashDelimiterLocation - 1)).c_str())) - 1);
		if(i != 2)
		{
			object->AddFace((atoi((source.substr(secondSlashDelimiterLocation + 1,secondDelimiterLocation - secondSlashDelimiterLocation)).c_str())) - 1);
		}
		else
		{
			object->AddFace(atoi(source.substr(secondSlashDelimiterLocation + 1,source.find('\n') - 1).c_str()) - 1);
		}
		source = source.erase(0,secondDelimiterLocation);
	
	}
}

std::string OBJLevelLoader::GetNextLine(std::ifstream& mapFile,std::string line)
{
	do{
		getline(mapFile,line);
	}while(line.compare(0,1,"s",0,1) == 0 || line.compare(0,1,"#",0,1) == 0);
	
	return line;
}

OBJLevelLoader::OBJLevelLoader(std::string objFile)
{
	std::string line;
	std::ifstream mapFile;
	std::string name;
	bool firstPass = true;
	mapFile.open(objFile.c_str(),std::fstream::in);
	
	if(mapFile.is_open())
	{
		while (getline(mapFile,line))
		{
			if(line.compare(0,1,"s",0,1) == 0 || line.compare(0,1,"#",0,1) == 0)
			{
				line = GetNextLine(mapFile,line);
			}
			
			GameObject* object = new GameObject();
			
			if(line.compare(0,6,"mtllib",0,6) == 0)
			{
				m_MTLFile.open(line.substr(7,std::string::npos).c_str(),std::fstream::in);
				line = GetNextLine(mapFile,line);
			}
			if(firstPass)
			{
				if(line.compare(0,1,"o",0,1) == 0)
				{
					object->SetObjectName(line.substr(2));
					line = GetNextLine(mapFile,line);
					firstPass = false;
				}
			}
			else
			{
				object->SetObjectName(name);
			}
			if(line.compare(0,2,"v ",0,2) == 0)
			{
				
				while(line.compare(0,2,"v ",0,2) == 0)
				{
					AppendVertex(line);	
					line = GetNextLine(mapFile,line);
				}
			}
			if(line.compare(0,2,"vt",0,2) == 0)
			{
				while(line.compare(0,2,"vt",0,2) == 0)
				{
					AppendTexel(line);
					line = GetNextLine(mapFile,line);
				}	
			}
			if(line.compare(0,2,"vn",0,2) == 0)
			{
				while(line.compare(0,2,"vn",0,2) == 0)
				{
					AppendNormal(line);
					line = GetNextLine(mapFile,line);
				}
			}
			if(line.compare(0,6,"usemtl",0,6) == 0)
			{
				AssignTexture(object,line);
				line = GetNextLine(mapFile,line);
			}
			if(line.compare(0,1,"f",0,1) == 0)
			{
				while(line.compare(0,1,"f",0,1) == 0)
				{
					AppendFace(object,line);
					line = GetNextLine(mapFile,line);
				}
			}
			
			if(object->GetObjectName() != "" && m_vertecies.size() != 0 && object->GetFaceVector().size() != 0 && m_texelCoords.size() != 0)
			{
				m_objectVector.push_back(object);
				if(line != "") 
				{
					name = line.substr(2);
				}
				continue;
			}
			delete object;
		}
		InitializeGlobalGLBuffers();
		for(unsigned int i = 0;i < m_objectVector.size();i++)
		{
			m_objectVector.at(i)->InitalizeGLBuffers();	
		}
	}else
	{
	
		std::cerr << "Could not open " << objFile << std::endl;
		return;	
	}
	m_MTLFile.close();
	mapFile.close();	
}

void OBJLevelLoader::InitializeGlobalGLBuffers()
{
	glGenVertexArrays(1,&m_vertexBufferObjectId);
	glBindVertexArray(m_vertexBufferObjectId);
	
	//Vertex Positions
	{
		glGenBuffers(1,&m_positionBufferId);
		glBindBuffer(GL_ARRAY_BUFFER,m_positionBufferId);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float) * m_vertecies.size(),&m_vertecies,GL_STATIC_DRAW);
		glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);	
		glEnableVertexAttribArray(0);
	}
	//Texture Coordinates
	{
		glGenBuffers(1,&m_textureCoordinateBufferId);
		glBindBuffer(GL_ARRAY_BUFFER,m_textureCoordinateBufferId);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float) * m_texelCoords.size(),&m_texelCoords,GL_STATIC_DRAW);
		glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);
		glEnableVertexAttribArray(1);
	}
	//Normals	
	{
		glGenBuffers(1,&m_normalBufferId);
		glBindBuffer(GL_ARRAY_BUFFER,m_normalBufferId);
		glBufferData(GL_ARRAY_BUFFER,sizeof(float) * m_normals.size(),&m_normals,GL_STATIC_DRAW);
		glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);
		glEnableVertexAttribArray(2);
	}
	
	glBindVertexArray(0);	
}

void OBJLevelLoader::DrawLevel(Textures& textures)
{
	glBindVertexArray(m_vertexBufferObjectId);
	
	for(unsigned int i = 0;i < m_objectVector.size();i++)
	{
		std::string textureName  = m_objectVector.at(i)->GetTextureName();
		m_objectVector.at(i)->BindBuffer();
		(textures.GetTextureByName(textureName))->BindTexture();
		glDrawElementsBaseVertex(GL_TRIANGLES,m_objectVector.at(i)->GetFaceVector().size(),GL_UNSIGNED_INT,0,0);
		(textures.GetTextureByName(textureName))->UnbindTexture();
		m_objectVector.at(i)->UnbindBuffer();
	}

	glBindVertexArray(0);
}

OBJLevelLoader::~OBJLevelLoader()
{
	if(m_MTLFile.is_open())
	{
		m_MTLFile.close();
	}

	for(unsigned int i = 0; i < m_objectVector.size();i++)
	{
		delete m_objectVector.at(i);
	}

	glDeleteBuffers(1,&m_positionBufferId);
	glDeleteBuffers(1,&m_textureCoordinateBufferId);
	glDeleteBuffers(1,&m_normalBufferId);
	
	glDeleteVertexArrays(1,&m_vertexBufferObjectId);	
}
