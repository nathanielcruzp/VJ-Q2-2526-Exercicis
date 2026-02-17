#include <GL/glew.h>
#include <GL/gl.h>
#include "Circulo.h"

float PI = 3.14159265;

Circulo *Circulo::createCirculo(float x, float y, float radius, ShaderProgram &program)
{
	Circulo *circulo = new Circulo(x, y, radius, program);

	return circulo;
}

Circulo::Circulo(float x, float y, float radius, ShaderProgram &program)
{
    float sides = 20;
    float vertices[20 * 6]; //por defecto serán de 20 lados
    float angle = 2.0f * PI / sides;
	vertices[0] = x;
	vertices[1] = y;
	vertices[2] = x + radius;
	vertices[3] = y;
	vertices[4] = x + radius * cos(angle);
	vertices[5] = y + radius * sin(angle);

    for (int i = 1; i < sides; ++i) {
        angle = (i + 1) * 2.0f * PI / sides;
        vertices[6 * i] = x;
        vertices[6 * i + 1] = y;
        vertices[6 * i + 2] = vertices[6 * i - 2];
        vertices[6 * i + 3] = vertices[6 * i - 1];
        vertices[6 * i + 4] = x + radius * cos(angle);
        vertices[6 * i + 5] = y + radius * sin(angle);
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sides * 6 * sizeof(float), vertices, GL_STATIC_DRAW);
    posLocation = program.bindVertexAttribute("position", 2);
}

void Circulo::render() const
{
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glDrawArrays(GL_TRIANGLES, 0, sides * 3);
}

void Circulo::free()
{
	glDeleteBuffers(1, &vbo);
}

