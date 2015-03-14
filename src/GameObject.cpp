#include "GameObject.h"
#include <vector>
#include "glm/glm.hpp"
#include "GL/glew.h"
GameObject::GameObject() : m_eulerRotation(glm::vec3(0,0,0)), m_worldPosition(glm::vec3(0,0,0)), m_scale(glm::vec3(1,1,1))
{
	m_objectName = "";
	m_textureName = "";
}

GameObject::~GameObject() 
{
	glDeleteBuffers(1,&m_facesBufferId);
}

void GameObject::AddFace(int face)		
{
	m_faces.push_back(face);
}

void GameObject::SetObjectName(const std::string objectName)
{
	m_objectName = objectName;
}

void GameObject::SetTextureName(const std::string textureName)
{
	m_textureName = textureName;
}

void GameObject::SetWorldPosition(float x, float y, float z)
{
	m_worldPosition = glm::vec3(x,y,z);
}

void GameObject::SetEulerRotation(float x, float y, float z)
{
	m_eulerRotation = glm::vec3(x,y,z);
}

void GameObject::SetScale(float x, float y, float z)
{
	m_scale= glm::vec3(x,y,z);
}

void GameObject::InitalizeGLBuffers()
{
	glGenBuffers(1,&m_facesBufferId);
	BindBuffer();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(int) * m_faces.size(),&m_faces,GL_STATIC_DRAW);
	UnbindBuffer();
}

void GameObject::BindBuffer() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_facesBufferId);
}

void GameObject::UnbindBuffer() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
