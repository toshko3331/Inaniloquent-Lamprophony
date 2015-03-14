#version 120

attribute vec3 position;
attribute vec2 texCoord;
attribute vec3 normal;

varying vec2 _texelCoordinate;
varying vec3 _normal;

uniform mat4 cameraViewMatrix;
//uniform mat4 Normal;

void main()
{
	gl_Position = cameraViewMatrix * vec4(position, 1.0);
	_texelCoordinate = texCoord;
	_normal = vec4(normal, 0.0).xyz;
}

