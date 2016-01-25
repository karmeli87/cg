
#include <iostream>
#include <math.h>
#include "Grape.h"
#include "Common.h"
#include "Matrices.h"

const double Pi = 3.1415926535897;
unsigned int stacks = 20;
unsigned int slices = 20;
unsigned int textureHeight = 512;
unsigned int textureWidht = 512;
const char *texturePath = "./textures/greenSM.png";
bool isTextureLoaded = false;
GLuint textureId;

std::vector<unsigned char> textureData;

ShaderProgram* Grape::m_cProg = NULL;
Vector3 index2vector(std::vector<float> &vertices,unsigned int index){
	return Vector3(vertices[3 * index], vertices[3 * index + 1], vertices[3 * index + 2]);
}

Vector3 calcNormal(std::vector<float> &vertices, unsigned int vertex1, unsigned int vertex2, unsigned int vertex3){
	Vector3 v1 = index2vector(vertices, vertex1);
	Vector3 v2 = index2vector(vertices, vertex2);
	Vector3 v3 = index2vector(vertices, vertex3);

	Vector3 edge1 = v2 - v1;
	Vector3 edge2 = v3 - v1;
	return edge2.cross(edge1);
}

void Grape::DrawEllipsoid()
{
	std::vector<unsigned int> indices;
	std::vector<float> uv_coord;
	std::vector<float> vertices;
	std::vector<float> normals;

	float tStep = (Pi) / (float)stacks;
	float sStep = (Pi) / (float)slices;
	Vector3 inv_rVector = Vector3(1 / rVector.x, 1 / rVector.y, 1 / rVector.z);
	unsigned int i = -1;
	
	for (float t = -Pi / 2; t <= (Pi / 2) + .0001; t += tStep)
	{
		for (float s = -Pi; s <= Pi + .0001; s += sStep)
		{	
			Vector3 coord = Vector3(cos(t) * cos(s), cos(t) * sin(s), sin(t));
			addVertices(vertices,coord*rVector);
			uv_coord.push_back((2 * t + Pi) / (2 * Pi)); // x-coord
			uv_coord.push_back((s + Pi) / (2 * Pi)); // y-coord
			Grape::pushVector<float>(normals, coord*inv_rVector*inv_rVector*2);

			coord = Vector3(cos(t + tStep) * cos(s), cos(t + tStep) * sin(s), sin(t + tStep));
			addVertices(vertices,coord*rVector);
			uv_coord.push_back((2 * t + 2 *tStep + Pi) / (2 * Pi)); // x-coord
			uv_coord.push_back((s + Pi) / (2 * Pi)); // y-coord
			Grape::pushVector<float>(normals, coord*inv_rVector*inv_rVector*2);

			i = i + 2;

			if (s > -Pi){
				if (t < (-Pi / 2) + 0.001){
					indices.push_back(i - 3);
					indices.push_back(i);
					indices.push_back(i - 2);
				}
				else if (t > (Pi / 2)){
					indices.push_back(i);
					indices.push_back(i- 3);
					indices.push_back(i - 1);
				}
				else {
					// left-up tri
					indices.push_back(i - 3);
					indices.push_back(i - 1);
					indices.push_back(i - 2);
					//right-bottom tri
					indices.push_back(i - 2);
					indices.push_back(i - 1);
					indices.push_back(i);
				}
			}
		}
	}
	bindVertices(vertices);
	bindIndices(indices);
	bindUV(uv_coord);
	bindNormals(normals);
}

void Grape::setInitialTexture(){
	if (!isTextureLoaded){
		loadPNG(texturePath, textureData, textureWidht, textureHeight);
		glGenTextures(1, &textureId);
		glBindTexture(GL_TEXTURE_2D, textureId);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, textureHeight, textureWidht, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData.data());
		textureData.clear();
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glBindTexture(GL_TEXTURE_2D, 0);
		isTextureLoaded = true;
	}
}

Grape::Grape(Vector3 pos, Vector3 dir,Vector3 radiusVector){
	origin = pos;
	rVector = radiusVector;
	this->dir = dir+Vector3(90,0,0);

	shaderOrigin = glGetUniformLocation(Grape::m_cProg->getPrgID(), "origin");
	shaderVertex = glGetAttribLocation(Grape::m_cProg->getPrgID(), "in_Position");
	shaderVertexUV = glGetAttribLocation(Grape::m_cProg->getPrgID(), "vertTexCoord");
	shaderVertexNormal = glGetAttribLocation(Grape::m_cProg->getPrgID(), "vertexNormal");
	
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &indexBuffer);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &uvBuffer);
	glGenBuffers(1, &normalBuffer);
	
	DrawEllipsoid();
	setMaterial();

}
Grape::Grape(Vector3 pos) : Grape(pos, Vector3() ,Vector3(1.0, 1.0, 1.0)){}
void Grape::setMaterial(){

	GLint matAmbientLoc = glGetUniformLocation(Grape::m_cProg->getPrgID(), "light.ambient");
	GLint matDiffuseLoc = glGetUniformLocation(Grape::m_cProg->getPrgID(), "light.diffuse");
	GLint matSpecularLoc = glGetUniformLocation(Grape::m_cProg->getPrgID(), "light.specular");
	GLint matShineLoc = glGetUniformLocation(Grape::m_cProg->getPrgID(), "material.shininess");

	glUniform3f(matAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(matDiffuseLoc, 0.5f, 0.5f, 0.5f);
	glUniform3f(matSpecularLoc, 1.0f, 1.0f, 1.0f);
	glUniform1f(matShineLoc, 32.0f);
}
void Grape::render(){
	// bind texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId);
	
	glBindVertexArray(vao);									// load vao
	glUniform3f(shaderOrigin, origin.x,origin.y,origin.z);	// set origin position

	glEnableVertexAttribArray(shaderVertex);				// set vertex coord
	glEnableVertexAttribArray(shaderVertexUV);				// set texture coord
	glEnableVertexAttribArray(shaderVertexNormal);			// set vertex normal
	glDrawElements(GL_TRIANGLES, objectsNum, GL_UNSIGNED_INT, 0);
	glDisableVertexAttribArray(shaderVertexNormal);
	glDisableVertexAttribArray(shaderVertexUV);
	glDisableVertexAttribArray(shaderVertex);
	
	glBindVertexArray(0);
	glActiveTexture(GL_TEXTURE_2D);
}
void Grape::move(Vector3 new_pos){
	origin += new_pos;
}