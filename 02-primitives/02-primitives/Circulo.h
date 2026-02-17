#ifndef _CIRCULO_INCLUDE
#define _CIRCULO_INCLUDE


#include "ShaderProgram.h"


// Given a point (x, y) and a size (width, height) in pixels Circulo creates 
// a VBO with 20 triangles. Vertices in the VBO have only a position
// attribute (no colors or texture coordinates)


class Circulo
{

private:
	Circulo(float x, float y, float radius, ShaderProgram& program);

public:
	// Circulos can only be created inside an OpenGL context
	static Circulo *createCirculo(float x, float y, float radius, ShaderProgram& program);

	void render() const;
	void free();

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation;
	int sides;

};


#endif // _CIRCULO_INCLUDE

