#ifndef STEM1_CLASS
#define STEM1_CLASS

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>

#include "Cylinder.h"
#include "Grape.h"
#include "Stem2.h"

class Stem1 : public Cylinder{
public:
	Stem1(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res);
	virtual void render();

protected:
	static const int stem2num = 10;
	Stem2* stem2Array[stem2num];

};

#endif