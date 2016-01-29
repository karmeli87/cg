#include <math.h>
#include "Grape.h"
#include "Common.h"
#include "TextureLoader.h"
const double Pi = 3.1415926535897;
unsigned int stacks = 20;
unsigned int slices = 20;
unsigned int textureHeight = 512;
unsigned int textureWidth = 512;
const char *texturePath = "./textures/greenSM.png";

GLuint textureId;


ShaderProgram* Grape::m_cProg = NULL;

void Grape::DrawEllipsoid()
{
	std::vector<unsigned int> indices;
	std::vector<float> uv_coord;
	std::vector<float> vertices;
	std::vector<float> normals;

	float tStep = (Pi) / (float)stacks;
	float sStep = (Pi) / (float)slices;
	glm::vec3 inv_rVector = glm::vec3(1 / rVector.x, 1 / rVector.y, 1 / rVector.z);
	unsigned int i = -1;
	
	for (float t = -Pi / 2; t <= (Pi / 2) + .0001; t += tStep)
	{
		for (float s = -Pi; s <= Pi + .0001; s += sStep)
		{	
			glm::vec3 coord = glm::vec3(cos(t) * cos(s), cos(t) * sin(s), sin(t));
			addVertices(vertices,coord*rVector);
			uv_coord.push_back((2 * t + Pi) / (2 * Pi)); // x-coord
			uv_coord.push_back((s + Pi) / (2 * Pi)); // y-coord
			addVertices(normals, glm::normalize(2.0f*coord*inv_rVector*inv_rVector));

			coord = glm::vec3(cos(t + tStep) * cos(s), cos(t + tStep) * sin(s), sin(t + tStep));
			addVertices(vertices,coord*rVector);
			uv_coord.push_back((2 * t + 2 *tStep + Pi) / (2 * Pi)); // x-coord
			uv_coord.push_back((s + Pi) / (2 * Pi)); // y-coord
			addVertices(normals, glm::normalize(2.0f*coord*inv_rVector*inv_rVector));

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
	TextureLoadr::load(textureId, texturePath, textureHeight, textureWidth);
	printf("loaded with id: %d", textureId);
}

Grape::Grape(glm::vec3 pos, glm::vec3 dir,glm::vec3 radiusVector){
	
	origin = pos;
	rVector = radiusVector;
	axis = glm::vec3(0, 0, 1);
	setDir(dir);

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
}
Grape::Grape(glm::vec3 pos) : Grape(pos, glm::vec3() ,glm::vec3(1.0, 1.0, 1.0)){}
void Grape::setMaterial(){
	GLint matShineLoc = glGetUniformLocation(Grape::m_cProg->getPrgID(), "material.shininess");
	glUniform1f(matShineLoc, 1.0f);
}
void Grape::render(){
	// bind texture

	setMaterial();

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
void Grape::move(glm::vec3 new_pos){
	origin += new_pos;
}