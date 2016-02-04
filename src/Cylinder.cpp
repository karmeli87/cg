#define _USE_MATH_DEFINES
#include <iostream>
#include <algorithm>
#include <math.h>
#include "Cylinder.h"
#include "TextureLoader.h"

unsigned int textureHeight1 = 512;
unsigned int textureWidth1 = 512;
const char *texturePath1 = "./textures/tree.png"; 
const char *texturePath2 = "./textures/treeNormal.png";
GLuint textureId1;
GLuint textureId2;

std::vector<unsigned char> mapNormals;

void Cylinder::DrawCylinder()
{
	std::vector<float> uv_coord;
	std::vector<unsigned int> indices;
	std::vector<float> cylVertices;
	std::vector<float> normals;

	unsigned char* normalMap = mapNormals.data();
	unsigned int totalSize = mapNormals.size();
	//std::cout << mapNormals.size() << std::endl;
	float thetaStep = ((float)2.0*M_PI) / slices;
	float dz = ((float)(length)) / slices;
	glm::vec3 rotationAxis = glm::vec3(0, -1, 0);
	unsigned int i = -1;
	// close the opening at begin
	for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
		this->addVertices(cylVertices,glm::vec3(radius*cos(theta), 0, radius*sin(theta)));
		this->addVertices(cylVertices,glm::vec3(0, 0, 0));
		this->addVertices(normals, glm::vec3(0, -1, 0));
		this->addVertices(normals, glm::vec3(0, -1, 0));

		uv_coord.push_back(0); // y-coord
		uv_coord.push_back(0); // x-coord
		uv_coord.push_back(0); // y-coord
		uv_coord.push_back(0); // x-coord
		
		
		i = i + 2;
		indices.push_back(i);
		indices.push_back(i - 1);
		indices.push_back(i - 2);

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i - 1);
	}


	// create the cylinder
	for (float z = 0; z < length-dz + 0.001; z += dz) {
		for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
			this->addVertices(cylVertices, glm::vec3(radius*cos(theta), z, radius*sin(theta)));
			//this->addVertices(normals, glm::vec3(radius*cos(theta), 0, radius*sin(theta)));

			float uvx = z / length;
			float uvy = theta / ((float)2.0*M_PI);

			uv_coord.push_back(3*uvx); // x-coord
			uv_coord.push_back(uvy); // y-coord

			unsigned int normalIndex =4*(unsigned int)(uvy*(float)(textureWidth1-1) + uvx*(float)(textureHeight1)*(float)(textureWidth1-1));
			//std::cout << normalIndex << std::endl;
			normalIndex = std::min(normalIndex, totalSize);
			glm::vec3 norm = glm::vec3(normalMap[normalIndex], normalMap[normalIndex + 1],- normalMap[normalIndex + 2] );
			norm = glm::rotate(norm, theta, rotationAxis);
			this->addVertices(normals, 2.0f*glm::normalize(norm) - 1.0f);
			
			this->addVertices(cylVertices, glm::vec3(radius*cos(theta), z + dz, radius*sin(theta)));
			//this->addVertices(normals, glm::vec3(radius*cos(theta), 0, radius*sin(theta)));

			uvx = (z + dz) / length;
			
			uv_coord.push_back(3*uvx); // x-coord
			uv_coord.push_back(uvy); // y-coord

			normalIndex = 4*(unsigned int)(uvy*(float)(textureWidth1-1) + uvx*(float)(textureHeight1)*(float)(textureWidth1-1));
			//std::cout << normalIndex << std::endl;
			if (normalIndex > totalSize){
				std::cout << normalIndex << std::endl;
				std::cout << uvx <<":" << uvy<< std::endl;
			}
			normalIndex = std::min(normalIndex, totalSize);
			
			norm = glm::vec3(normalMap[normalIndex], normalMap[normalIndex + 1],- normalMap[normalIndex + 2]);
			norm = glm::rotate(norm, theta, rotationAxis);
			this->addVertices(normals, 2.0f*glm::normalize(norm) - 1.0f);

			i = i + 2;
			indices.push_back(i);
			indices.push_back(i - 1);
			indices.push_back(i - 2);

			indices.push_back(i);
			indices.push_back(i + 1);
			indices.push_back(i - 1);
			
		}
	}
	// close the opening at end
	for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
		this->addVertices(cylVertices, glm::vec3(radius*cos(theta), length, radius*sin(theta)));
		this->addVertices(cylVertices, glm::vec3(0, length, 0));
		this->addVertices(normals, glm::vec3(0, 1, 0));
		this->addVertices(normals, glm::vec3(0, 1, 0));
		uv_coord.push_back(0); // y-coord
		uv_coord.push_back(0); // x-coord
		uv_coord.push_back(0); // y-coord
		uv_coord.push_back(0); // x-coord
		
		i = i + 2;
		indices.push_back(i);
		indices.push_back(i - 1);
		indices.push_back(i - 2);

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i - 1);
	}
	
	this->bindVertices(cylVertices);
	this->bindIndices(indices);
	this->bindUV(uv_coord);
	this->bindNormals(normals);
}

void Cylinder::setInitialTexture(){
	TextureLoadr::load(textureId1, texturePath1, textureHeight1, textureWidth1);
	mapNormals = TextureLoadr::getData(texturePath2, textureHeight1, textureWidth1);
}

Cylinder::Cylinder(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res) {
	origin = pos;
	radius = r;
	length = size;
	this->setDir(angle);
	slices = res;
	
	this->shaderOrigin = glGetUniformLocation(GameObject::m_cProg->getPrgID(), "origin");
	this->shaderVertex = glGetAttribLocation(GameObject::m_cProg->getPrgID(), "in_Position");
	this->shaderVertexUV = glGetAttribLocation(GameObject::m_cProg->getPrgID(), "vertTexCoord");
	this->shaderVertexNormal = glGetAttribLocation(GameObject::m_cProg->getPrgID(), "vertexNormal");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &indexBuffer);	
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &uvBuffer);
	glGenBuffers(1, &normalBuffer);

	this->DrawCylinder();
}

void Cylinder::setMaterial(){
	GLint matShineLoc = glGetUniformLocation(GameObject::m_cProg->getPrgID(), "material.shininess");
	glUniform1f(matShineLoc, 1.0f);
}

void Cylinder::render() {

	this->setMaterial();
	// bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId1);

	glBindVertexArray(vao);
	glUniform3f(shaderOrigin, origin.x, origin.y, origin.z);
	glEnableVertexAttribArray(shaderVertex);
	glEnableVertexAttribArray(shaderVertexUV);				// set texture coord
	glEnableVertexAttribArray(shaderVertexNormal);			// set vertex normal
	//std::cout << "num of obj : " << objectsNum << std::endl;
	glDrawElements(GL_TRIANGLES, objectsNum, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, objectsNum);
	glDisableVertexAttribArray(shaderVertexNormal);		
	glDisableVertexAttribArray(shaderVertex);
	glDisableVertexAttribArray(shaderVertexUV);
	glBindVertexArray(0);
	//glActiveTexture(GL_TEXTURE_2D);


}