#include "Light.h"
#include "Cylinder.h"

Light::Light(glm::vec3 pos)
{
	origin = pos;

	lightPosLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.position");
	matAmbientLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.ambient");
	matDiffuseLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.diffuse");
	matSpecularLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.specular");

	glUniform3f(lightPosLoc, origin.x, origin.y, origin.z);
	glUniform3f(matAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(matDiffuseLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(matSpecularLoc, 0.1f, 0.1f, 0.1f);

	GLfloat vertices[] = {
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,

		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vertexBuffer);

	shaderOrigin = glGetUniformLocation(GameObject::m_cProg->getPrgID(), "origin");
	shaderVertex = glGetAttribLocation(GameObject::m_cProg->getPrgID(), "in_Position");

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vao);
	// Position attribute
	glVertexAttribPointer(shaderVertex, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	objectsNum = sizeof(vertices)/2;
	
}

void Light::render(){
	glBindVertexArray(vao);
	
	glUniform3f(shaderOrigin, origin.x, origin.y, origin.z);	// set origin position
	glUniform1i(glGetUniformLocation(GameObject::m_cProg->getPrgID(), "renderLight"), 1);
	glEnableVertexAttribArray(shaderVertex);
	//std::cout << "num of obj : " << objectsNum << std::endl;
	//glDrawElements(GL_TRIANGLES, objectsNum, GL_UNSIGNED_INT, 0);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, objectsNum);
	glDisableVertexAttribArray(shaderVertex);
	glUniform1i(glGetUniformLocation(GameObject::m_cProg->getPrgID(), "renderLight"), 0);
	glBindVertexArray(0);
	
}

Light::~Light()
{
}
