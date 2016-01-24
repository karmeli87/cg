#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Helpers.h"

class GameObject
{
	/****** Vars *******/
protected:
	bool isSelected = false;
	Vector3 origin;
	Vector3 dir;

	GLuint shaderOrigin;
	GLuint shaderVertex;
	GLuint shaderTexture;
	GLuint shaderVertexUV;

	GLuint vao;
	GLuint indexBuffer;
	GLuint vertexBuffer;
	GLuint uvBuffer;

	unsigned int objectsNum = 0;

	/****** Functions ******/
public:
	GameObject(){}
	GameObject(Vector3 origin, Vector3 dir){
		this->origin = origin;
		this->dir = dir;
	}
	virtual ~GameObject(){}
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
	virtual void addVertices(std::vector<float>&vertices, Vector3 v){
		Vector4 vec = Vector4(v.x, v.y, v.z, 1);
		vec = rotationMatrix(dir.x, dir.y, dir.z)*vec;

		vertices.push_back(vec.x);
		vertices.push_back(vec.y);
		vertices.push_back(vec.z);
	}
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

	virtual void setMaterial() = 0;
	

};
#endif
