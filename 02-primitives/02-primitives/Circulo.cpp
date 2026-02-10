#include <GL/glew.h>
#include <GL/gl.h>
#include <cmath>
#include "Circulo.h"


Circulo *Circulo::createCirculo(float x, float y, float radius, float sides, ShaderProgram &program)
{
	Circulo *circulo = new Circulo(x, y, radius, sides, program);

	return circulo;
}


Circulo::Circulo(float x, float y, float radius, float sides, ShaderProgram &program)
{
	float vertices[sides*3*2];
	for (int i = 0; i < sides; ++i) { //arreglar esto lolazo
		float angle = i * 2.0f * M_PI / sides;
		vertices[2 * i] = x + radius * cos(angle);
		vertices[2 * i + 1] = y + radius * sin(angle);
	}
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), vertices, GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2);
}

void Circulo::render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Circulo::free()
{
	glDeleteBuffers(1, &vbo);
}

