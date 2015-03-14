#include "Camera.h"
#include "glm/glm.hpp"
#define GLM_FORCE_RADIANS
#define PI 3.14159265359
#include "glm/gtx/transform.hpp"

Camera::Camera(const float fov,const float aspectRatio,const float nearPlane,const float farPlane) : 
	m_projectionMatrix(glm::perspective((float)(fov * PI)/ 180,aspectRatio,nearPlane,farPlane))
{
}

//TODO:Implement a free-look camera. We can use glm::lookAt and from that
//we can derive the rest of the locations, by taking crossproduct and all
//that fancy shit. Basically, the problem with last camera was that we
//could not get the lookAt(forward) vector working properly.
