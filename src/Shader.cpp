#include "Shader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
Shader::Shader(std::string vertShaderName,std::string fragShaderName) : 
	m_vertShaderSource(ReadShaderFile(vertShaderName)),
	m_fragShaderSource(ReadShaderFile(fragShaderName))
{
	GLint compileStatus = 0;
	GLint linkStatus = 0;
	GLint validationStatus = 0;
	
	m_shaderProgram = glCreateProgram();	
	m_vertShaderId = glCreateShader(GL_VERTEX_SHADER);
	m_vertShaderSourceC = (GLchar*)m_vertShaderSource.c_str();
	glShaderSource(m_vertShaderId,1,&m_vertShaderSourceC,NULL);
	glCompileShader(m_vertShaderId);
	
	glGetShaderiv(m_vertShaderId,GL_COMPILE_STATUS,&compileStatus);
	
	if(compileStatus == GL_FALSE)
	{
		
		GLint logLength = 0;
		glGetShaderiv(m_vertShaderId,GL_INFO_LOG_LENGTH,&logLength);
		
		std::vector<GLchar> errorLog(logLength);
		
		glGetShaderInfoLog(m_vertShaderId,logLength,NULL,&errorLog[0]);
		
		std::cerr << "Error in vertex shader: " << &errorLog.at(0) << std::endl;
		
		glDeleteShader(m_vertShaderId);
		//TODO:Return here.
	}

	m_fragShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	m_fragShaderSourceC = (GLchar*)m_fragShaderSource.c_str();
	glShaderSource(m_fragShaderId,1,&m_fragShaderSourceC,NULL);
	glCompileShader(m_fragShaderId);
	
	glGetShaderiv(m_fragShaderId,GL_COMPILE_STATUS,&compileStatus);
	
	if(compileStatus == GL_FALSE)
	{
		
		GLint logLength = 0;
		glGetShaderiv(m_fragShaderId,GL_INFO_LOG_LENGTH,&logLength);
		
		std::vector<GLchar> errorLog(logLength);
		
		glGetShaderInfoLog(m_fragShaderId,logLength,NULL,&errorLog[0]);
		std::cerr << "Error in fragment shader: " << &errorLog.at(0) << std::endl;
	
		glDeleteProgram(m_shaderProgram);
		glDeleteShader(m_vertShaderId);
		glDeleteShader(m_fragShaderId);
		//TODO:Return here.
	}

	glAttachShader(m_shaderProgram,m_vertShaderId);
	glAttachShader(m_shaderProgram,m_fragShaderId);
	
	
	glBindAttribLocation(m_shaderProgram,0,"positionCoordinate");
	glBindAttribLocation(m_shaderProgram,1,"texelCoordinate");
	glBindAttribLocation(m_shaderProgram,2,"normal");

	glLinkProgram(m_shaderProgram);
	
	glGetProgramiv(m_shaderProgram,GL_LINK_STATUS,&linkStatus);
	if(linkStatus == GL_FALSE)
	{	
		std::vector<GLchar> errorLog(2048);
		
		glGetProgramInfoLog(m_shaderProgram,2048,NULL,&errorLog[0]);
		std::cerr << "Error in linking program: " << &errorLog.at(0) << std::endl;
		glDetachShader(m_shaderProgram,m_vertShaderId);
		glDetachShader(m_shaderProgram,m_fragShaderId);
		
		glDeleteShader(m_vertShaderId);
		glDeleteShader(m_fragShaderId);
		glDeleteProgram(m_shaderProgram);
		//TODO:Return here.
	}
	
	glDetachShader(m_shaderProgram,m_vertShaderId);
	glDetachShader(m_shaderProgram,m_fragShaderId);
	
	glDeleteShader(m_vertShaderId);
	glDeleteShader(m_fragShaderId);
	
	glValidateProgram(m_shaderProgram);
	
	glGetProgramiv(m_shaderProgram,GL_VALIDATE_STATUS,(int*)&validationStatus);
	if(validationStatus == GL_FALSE)
	{
		std::vector<GLchar> errorLog(2048);
		
		glGetProgramInfoLog(m_shaderProgram,2048,NULL,&errorLog[0]);
		std::cerr << "Error in validating program: " << &errorLog.at(0) << std::endl;
		//TODO:Return here.
	}
	
	glGetUniformLocation(m_shaderProgram,"cameraViewMatrix");
	//glGetUniformLocation(m_shaderProgram,"normal");
	//glGetUniformLocation(m_shaderProgram,"lightDirection");

	glUseProgram(m_shaderProgram);
}

Shader::~Shader()
{
	glDeleteProgram(m_shaderProgram);
}

void Shader::UpdateWorld(const glm::mat4& cameraViewMatrix) const
{
	glUniformMatrix4fv(m_unionCameraMatrixId,1,GL_FALSE,&cameraViewMatrix[0][0]);
}
std::string Shader::ReadShaderFile(std::string fileName)
{
	std::string readingString;
	std::string finalString = "";
	
	std::ifstream shaderFile;
	shaderFile.open(std::string("shaders/") + fileName);
	if(shaderFile.is_open())
	{
		while(getline(shaderFile,readingString))
		{
			finalString.append(readingString + '\n');		
		}
		
	}else
	{
		std::cerr << "Could not open shaders/" << fileName << std::endl;
		return finalString.c_str();
	}
	shaderFile.close();
	return finalString;
}

