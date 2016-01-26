#ifndef STEM3_CLASS
#define STEM3_CLASS

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>

#include "Common.h"
#include "GameObject.h"
#include "ShaderProgram.h"
#include "Cylinder.h"

class Stem3 : public Cylinder{
public:
	Stem3(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res);
	virtual void render();

protected:
	//Grape* fruitEdgeArray[1];
	Grape* fruitEdge;
};

#endif