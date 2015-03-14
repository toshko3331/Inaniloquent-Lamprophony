#ifndef SHADER_H
#define SHADER_H
#include <string>
#include "GL/glew.h"
#include "glm/glm.hpp"

class Shader
{


	public:
		Shader(std::string vertShaderName,std::string fragShaderName);
		~Shader();
		void UpdateWorld(const glm::mat4& cameraiewMatrix) const;
		const std::string GetVertexSource() const {return m_vertShaderSource;} 
	private:
		std::string ReadShaderFile(const std::string fileName);
		GLuint m_shaderProgram;

		const std::string m_vertShaderSource;
		const std::string m_fragShaderSource;
		GLchar* m_vertShaderSourceC;
		GLchar* m_fragShaderSourceC;

		GLuint m_vertShaderId;
		GLuint m_fragShaderId;		
	
		GLint m_unionCameraMatrixId;

};
#endif // SHADER_H
