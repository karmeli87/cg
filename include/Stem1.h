#ifndef STEM1_CLASS
#define STEM1_CLASS

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>

#include "Common.h"
#include "Matrices.h"
#include "GameObject.h"
#include "ShaderProgram.h"
#include "Cylinder.h"
#include "Grape.h"
#include "Stem2.h"

class Stem1 : public Cylinder{
public:
	Stem1(Vector3 pos, GLfloat r, GLfloat size, Vector3 angle, GLint res);
	virtual void render();

protected:
	static const int stem2num = 3;
	Stem2* stem2Array[stem2num];

};

#endif