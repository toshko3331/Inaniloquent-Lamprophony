#version 120

varying vec2 _texelCoordinate;
varying vec3 _normal;

uniform sampler2D sampler;
//uniform vec3 lightDirection;

void main()
{
	gl_FragColor = texture2D(sampler, _texelCoordinate) * 
		clamp(dot(-vec3(0,0,1), _normal), 0.0, 1.0);
}

