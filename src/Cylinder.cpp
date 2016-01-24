#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"

ShaderProgram* Cylinder::m_cProg = NULL;

void Cylinder::DrawCylinder()
{
	
	std::vector<float> cylVertices;

	float thetaStep = ((float)2.0*M_PI) / slices;
	float dz = ((float)(length)) / slices;
	// create the cylinder
	for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
		addVertices(cylVertices,Vector3(radius*cos(theta), 0, radius*sin(theta)));
		addVertices(cylVertices,Vector3(0, 0, 0));

	}
	// close the opening at begin
	for (float z = 0; z < length; z += dz) {
		for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
			addVertices(cylVertices,Vector3(radius*cos(theta), z, radius*sin(theta)));
			addVertices(cylVertices,Vector3(radius*cos(theta), z + dz, radius*sin(theta)));
		}
	}
	// close the opening at end
	for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
		addVertices(cylVertices,Vector3(radius*cos(theta), length, radius*sin(theta)));
		addVertices(cylVertices,Vector3(0, length, 0));
	}
	bindVertices(cylVertices);
}


Cylinder::Cylinder(Vector3 pos, GLfloat r, GLfloat size, Vector3 angle, GLint res) {
	origin = pos;
	radius = r;
	length = size;
	dir = angle;
	slices = res;
	fruitEdge = new Grape(origin, dir, Vector3(1, 1, 2));

	shaderOrigin = glGetUniformLocation(Cylinder::m_cProg->getPrgID(), "origin");
	shaderVertex = glGetAttribLocation(Cylinder::m_cProg->getPrgID(), "in_Position");
	shaderVertexUV = glGetAttribLocation(Cylinder::m_cProg->getPrgID(), "vertTexCoord");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	/*glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	*/
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	
	DrawCylinder();
}

void Cylinder::setMaterial(){

	GLint matAmbientLoc = glGetUniformLocation(Cylinder::m_cProg->getPrgID(), "material.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(Cylinder::m_cProg->getPrgID(), "material.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(Cylinder::m_cProg->getPrgID(), "material.specular");
	GLint matShineLoc = glGetUniformLocation(Cylinder::m_cProg->getPrgID(), "material.shininess");

	glUniform3f(matAmbientLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matDiffuseLoc, 1.0f, 0.5f, 0.31f);
	glUniform3f(matSpecularLoc, 0.5f, 0.5f, 0.5f);
	glUniform1f(matShineLoc, 32.0f);
}

void Cylinder::render() {
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glEnableVertexAttribArray(shaderVertex);
	glUniform3f(shaderOrigin, origin.x, origin.y, origin.z);
	//glDrawElements(GL_TRIANGLE_STRIP, cylVertices.size(), GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, objectsNum);
	glDisableVertexAttribArray(shaderVertex);
	glBindVertexArray(0);

	fruitEdge->render();
}