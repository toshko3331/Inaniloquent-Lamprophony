#ifndef VERTEX_H
#define VERTEX_H
#include "glm/glm.hpp"
class Vertex
{

	public:
		/*-------------------------*/
		// 
		// Description: Initializes the position, texture coordinate, and normal vectors.
		//
		// @position: The poistion of this vertex.
		// @textureCoordinate: The corresponding texture coordinate
		// @normal: The corresponding normal.
		//
		// Return: None
		/*-------------------------*/
		Vertex(glm::vec3 position,glm::vec3 textureCoordinate,glm::vec3 normal);
		
		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The posiiton vector of this vertex.
		/*-------------------------*/
		glm::vec3 GetPositon() const { return m_position; }
		
		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The texture coordinate vector of this vertex.
		/*-------------------------*/
		glm::vec3 GetTextureCoordinate() const  { return m_textureCoordinate; }
		
		/*-------------------------*/
		// 
		// Description: Getter.
		//
		// Return: The normal vector of this vertex.
		/*-------------------------*/
		glm::vec3 GetNormal() const  { return m_normal; }  
	private:
		glm::vec3 m_position; 
		glm::vec3 m_textureCoordinate;
		glm::vec3 m_normal;
};

#endif // VERTEX_H

