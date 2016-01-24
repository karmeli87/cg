#ifndef STEM2_CLASS
#define STEM2_CLASS

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
#include "Stem3.h"

class Stem2 : public Cylinder{
public:
	Stem2(Vector3 origin, GLfloat radius, GLfloat length, Vector3 dir, GLint slices);
	virtual void render();

protected:
	static const int stem3num = 3;
	Stem3* stem3Array[stem3num];
};

#endif