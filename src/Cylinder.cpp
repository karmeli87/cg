#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"


unsigned int textureHeight1 = 512;
unsigned int textureWidht1 = 512;
const char *texturePath1 = "./textures/stemTexture4.png"; 
bool isTextureLoaded1 = false;
GLuint textureId1;
std::vector<unsigned char> textureData1;

ShaderProgram* Cylinder::m_cProg = NULL;

void Cylinder::DrawCylinder()
{
	std::vector<float> uv_coord;
	std::vector<unsigned int> indices;
	std::vector<float> cylVertices;

	float thetaStep = ((float)2.0*M_PI) / slices;
	float dz = ((float)(length)) / slices;

	
	unsigned int i = -1;
	// close the opening at begin
	for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
		addVertices(cylVertices,Vector3(radius*cos(theta), 0, radius*sin(theta)));
		addVertices(cylVertices,Vector3(0, 0, 0));
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
	for (float z = 0; z < length; z += dz) {
		for (float theta = 0; theta <= 2 * M_PI + 0.0001; theta += thetaStep) {
			addVertices(cylVertices,Vector3(radius*cos(theta), z, radius*sin(theta)));
			uv_coord.push_back(z / length); // x-coord
			uv_coord.push_back(theta / ((float)2.0*M_PI)); // y-coord
			
			addVertices(cylVertices,Vector3(radius*cos(theta), z + dz, radius*sin(theta)));
			uv_coord.push_back((z + dz) / length); // x-coord
			uv_coord.push_back((theta) / ((float)2.0*M_PI)); // y-coord

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
		addVertices(cylVertices,Vector3(radius*cos(theta), length, radius*sin(theta)));
		addVertices(cylVertices,Vector3(0, length, 0));
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
	
	bindVertices(cylVertices);
	bindIndices(indices);
	bindUV(uv_coord);
}

void Cylinder::setInitialTexture(){
	if (!isTextureLoaded1){
		loadPNG(texturePath1, textureData1, textureWidht1, textureHeight1);
		glGenTextures(1, &textureId1);
		glBindTexture(GL_TEXTURE_2D, textureId1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureHeight1, textureWidht1, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData1.data());
		textureData1.clear();
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		isTextureLoaded1 = true;
	}
}

Cylinder::Cylinder(Vector3 pos, GLfloat r, GLfloat size, Vector3 angle, GLint res) {
	origin = pos;
	radius = r;
	length = size;
	dir = angle;
	slices = res;
	
	shaderOrigin = glGetUniformLocation(Cylinder::m_cProg->getPrgID(), "origin");
	shaderVertex = glGetAttribLocation(Cylinder::m_cProg->getPrgID(), "in_Position");
	shaderVertexUV = glGetAttribLocation(Cylinder::m_cProg->getPrgID(), "vertTexCoord");

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &indexBuffer);	
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &uvBuffer);
	
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

	// bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId1);

	glBindVertexArray(vao);
	glUniform3f(shaderOrigin, origin.x, origin.y, origin.z);
	glEnableVertexAttribArray(shaderVertex);
	glEnableVertexAttribArray(shaderVertexUV);				// set texture coord
	std::cout << "num of obj : " << objectsNum << std::endl;
	glDrawElements(GL_TRIANGLES, objectsNum, GL_UNSIGNED_INT, 0);
	//glDrawArrays(GL_TRIANGLE_STRIP, 0, objectsNum);
	glDisableVertexAttribArray(shaderVertex);
	glDisableVertexAttribArray(shaderVertexUV);
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE_2D);


}