#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include <vector>
#include <string>
#include "glm/glm.hpp"
#include "GL/glew.h"
class GameObject
{
	public:
		GameObject();
		~GameObject();
		void AddFace(int face);
		void SetObjectName(const std::string objectName);
		void SetWorldPosition(float x, float y, float z);
		void SetEulerRotation(float x, float y, float z);
		void SetScale(float x, float y, float z);
		void SetTextureName(const std::string textureName);
		void UnbindBuffer() const;
		void BindBuffer() const;
		//Getters
		std::string GetObjectName() const { return m_objectName; } 
		std::string GetTextureName() const { return m_textureName; }
		glm::vec3 GetWorldPosition() const { return m_worldPosition; }
		glm::vec3 GetEulerRotation() const { return m_eulerRotation; }
		glm::vec3 GetScale() const { return m_scale; } 
		const std::vector<int>& GetFaceVector() const { return m_faces; }
		void InitalizeGLBuffers();

	private:
		glm::vec3 m_eulerRotation;
		glm::vec3 m_worldPosition;
		glm::vec3 m_scale;
		std::string m_objectName;
		std::string m_textureName;
		std::vector<int> m_faces;
			
		GLuint m_facesBufferId;
};
#endif //GAME_OBJECT_H
