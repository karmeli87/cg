#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Helpers.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

class GameObject
{
	/****** Vars *******/
protected:
	bool isSelected = false;
	Vector3 origin;
	Vector3 dir;

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
	template <class T> static void pushVector(std::vector<T>&list, Vector3 vec){
		list.push_back(vec.x);
		list.push_back(vec.y);
		list.push_back(vec.z);
	}
	template <class T> static void updateVector(std::vector<T>&list,unsigned int index, Vector3 vec){
		list[3 * index] = vec.x;
		list[3 * index + 1] = vec.y;
		list[3 * index + 2] = vec.z;
	}
	
	bool is = true;
	virtual void addVertices(std::vector<float>&vertices, Vector3 v){
		glm::mat4 trans;
	//	if (is){
			Vector3 cross = Vector3(0.0, 1.0, 0.0).cross(this->dir);
			glm::vec3 axis = glm::vec3(cross.x, cross.y, cross.z);
			float angle = std::acos(dir.normalize().dot(Vector3(0.0, 1.0, 0.0)));// *180 / 3.14159265;
			trans = glm::rotate(trans, angle, axis);
	//		std::cout << " asdasd " << glm::to_string(trans) << std::endl;
	//		is = false;
	//	}
		
		glm::vec4 vec = glm::vec4(v.x, v.y, v.z, 1);
		glm::vec4 res = trans*vec;
		Vector3 newVec = Vector3(res.x, res.y, res.z);
		
	//	std::cout << "in :" << v << " , " << "out : " << newVec << std::endl;
		
		pushVector<float>(vertices, newVec);
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
	virtual void bindNormals(std::vector<float>&normals){
		glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
		glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(float), &normals[0], GL_STATIC_DRAW);
		glVertexAttribPointer(shaderVertexNormal, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	};

	virtual void setMaterial() = 0;
	

};
#endif
