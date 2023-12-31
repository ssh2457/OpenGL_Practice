#include "Mesh.h"

Mesh::Mesh()
	: VAO(0)
	, VBO(0)
	, IBO(0)
	, indexCount(0)
{

}

Mesh::~Mesh() {
	ClearMesh();
}

void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numOfIndices) {
	indexCount = numOfIndices;


	// Generate VAO
	glGenVertexArrays(1, &VAO);
	// Bind VAO
	glBindVertexArray(VAO);

	// Generate IBO
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indexCount, indices, GL_STATIC_DRAW);

	// Generate VBO
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

	// Register attribute pointer
	/*
		glVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)

		index: ID
		size: Number of data to input for each vertex
		type: data type
		normalized: bool value
		stride: The Number of data for each vertex


		glEnableVertexAttribArray(GLuint index)
		index: ID
	*/ 

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * 8, (void*)(sizeof(vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	// Unbind VBO
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Unbind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::RenderMesh() {
	// Bind VAO
	glBindVertexArray(VAO);

	// Bind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Draw
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);

	// Unbind VAO
	glBindVertexArray(0);

	// Unbind IBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}


void Mesh::ClearMesh() {
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	indexCount = 0;
}