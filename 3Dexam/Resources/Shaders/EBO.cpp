#include"EBO.h"


// Constructor that generates a Elements Buffer Object and links it to indices
EBO::EBO() // Pass by const reference
{
    glGenBuffers(1, &ID);

}

void EBO::EBOSetUp(const std::vector<unsigned int>& indices)
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        indices.size() * sizeof(unsigned int), // Size in bytes
        indices.data(), // Pointer to the raw data
        GL_STATIC_DRAW);
}


// Binds the EBO
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbinds the EBO
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}