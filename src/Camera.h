#ifndef CAMERA_H
#define CAMERA_H
#include "glm/glm.hpp"
	
class Camera
{
	public:
		Camera(const float fov,const float aspectRatio,const float nearPlane,const float farPlane);
		const glm::mat4 GetProjectionMatrix() const { return m_projectionMatrix; }
	private:
		const glm::mat4 m_projectionMatrix;
};

#endif //CAMERA_H
