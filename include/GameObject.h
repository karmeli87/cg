#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/vector_angle.hpp>
#include "ShaderProgram.h"

class GameObject
{
	/****** Vars *******/
protected:
	bool isSelected = false;
	glm::vec3 origin;
	glm::vec3 dir;

	GLuint shaderOrigin;
	GLuint shaderTexture;
	GLuint shaderVertex;
	GLuint shaderVertexUV;
	GLuint shaderVertexNormal;

	GLuint vao;
	GLuint indexBuffer;
	GLuint vertexBuffer;
	GLuint uvBuffer;
	GLuint normalBuffer;

	unsigned int objectsNum = 0;

	/****** Functions ******/
public:
	GameObject(){}
	GameObject(glm::vec3 origin, glm::vec3 dir){
		this->origin = origin;
		this->dir = dir;
	}
	virtual ~GameObject(){}
	static ShaderProgram *m_cProg;
	virtual void render() = 0;
	virtual void select(){ 
		isSelected = true;
		glPolygonMode(GL_FRONT_AND_BACK,  GL_LINE);
	}
	virtual void deselect(){ 
		isSelected = false; 
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
protected:
	
	glm::mat4 trans;
	glm::vec3 axis = glm::vec3(0,1,0);

	template <class T> static void pushVector(std::vector<T>&list, glm::vec3 vec){
		list.push_back(vec.x);
		list.push_back(vec.y);
		list.push_back(vec.z);
	}
	template <class T> static void updateVector(std::vector<T>&list,unsigned int index, glm::vec3 vec){
		list[3 * index] = vec.x;
		list[3 * index + 1] = vec.y;
		list[3 * index + 2] = vec.z;
	}
	

	virtual void setDir(glm::vec3 newDir){
		glm::vec3 rotationAxis = glm::cross(axis, newDir);
		float angle = std::acos(glm::dot(glm::normalize(axis), glm::normalize(newDir)));// *180 / 3.14159265;
		trans = glm::rotate(trans, angle, rotationAxis);
		//std::cout << glm::to_string(axis) << glm::to_string(newDir) << angle << std::endl;
		//std::cout << "trans " << glm::to_string(trans) << std::endl;
		axis = newDir;
	}

	virtual void addVertices(std::vector<float>&vertices, glm::vec3 v){	
		glm::vec4 vec = glm::vec4(v, 1);
		glm::vec4 res = trans*vec;
		glm::vec3 newVec = glm::vec3(res.x, res.y, res.z);
		pushVector<float>(vertices, newVec);
	}

	virtual void bindShaderAttrs(){
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(shaderVertex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glVertexAttribPointer(shaderVertexUV, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glVertexAttribPointer(shaderVertexNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	};

	virtual void bindVertices(std::vector<float>&vertices){
		objectsNum = vertices.size();
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);
		glVertexAttribPointer(shaderVertex, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	};
	virtual void bindIndices(std::vector<unsigned int>&indices){
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
	}
	virtual void bindUV(std::vector<float>&uv_coord){
		glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
		glBufferData(GL_ARRAY_BUFFER, uv_coord.size() * sizeof(float), &uv_coord[0], GL_STATIC_DRAW);
		glVertexAttribPointer(shaderVertexUV, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	};
	virtual void bindNormals(std::vector<float>&normals){
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(shaderVertexNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	};

	virtual void setMaterial() = 0;
	

};
#endif
