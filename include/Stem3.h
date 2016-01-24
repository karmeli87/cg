#ifndef STEM3_CLASS
#define STEM3_CLASS

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

class Stem3 : public Cylinder{
public:
	Stem3(Vector3 origin, GLfloat radius, GLfloat length, Vector3 dir, GLint slices);
	virtual void render();

protected:
	Grape* fruitEdge;
};

#endif