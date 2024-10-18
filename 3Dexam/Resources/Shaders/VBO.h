#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include<glad/glad.h>

class VBO
{
public:
	// Reference ID of the Vertex Buffer Object
	GLuint ID;

	VBO() : ID(0) {
		glGenBuffers(1, &ID);
	}
	VBO(const GLfloat* data, GLsizeiptr size) : ID(0) {
		glGenBuffers(1, &ID);
		UpdateData(data, size);
	}

	// Constructor that generates a Vertex Buffer Object and links it to vertices
	VBO(GLfloat* vertices, GLsizeiptr size);
	void UpdateData(const void* data, size_t size);
	// Binds the VBO
	void Bind();
	// Unbinds the VBO
	void Unbind();
	// Deletes the VBO
	void Delete();
};

#endif
