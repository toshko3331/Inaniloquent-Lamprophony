#ifndef OBJ_LEVEL_LOADER_H
#define OBJ_LEVEL_LOADER_H
#include <fstream>
#include <string>
#include <vector>
#include "GameObject.h"
#include "Textures.h"

class OBJLevelLoader
{
	public:
		OBJLevelLoader(std::string filename);
		~OBJLevelLoader();

	 	std::vector<GameObject*>& GetObjects() { return m_objectVector; }

		const std::vector<float>& GetVertecies() const { return m_vertecies; }
		const std::vector<float>& GetTexelVector() const { return m_texelCoords; }
		const std::vector<float>& GetNormals() const { return m_normals; }
		void DrawLevel(Textures& textures);
	private:
		std::string GetNextLine(std::ifstream& mapFile,std::string line);
		void AppendVertex(std::string source);
		void AppendFace(GameObject* object, std::string source);
		void AppendTexel(std::string source);
		void AppendNormal(std::string source);
		void AssignTexture(GameObject* object,const std::string materialName);	
		void InitializeGlobalGLBuffers();	

		std::vector<float> m_vertecies;
		std::vector<float> m_texelCoords;
		std::vector<float> m_normals;
		std::vector<GameObject*> m_objectVector;

		GLuint m_vertexBufferObjectId;
		GLuint m_positionBufferId;
		GLuint m_textureCoordinateBufferId;
		GLuint m_normalBufferId;

		std::ifstream m_MTLFile;
};
#endif //OBJ_LEVEL_LOADER_H
