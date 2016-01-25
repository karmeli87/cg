#ifndef CYLINDER_CLASS
#define CYLINDER_CLASS

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>

#include "Common.h"
#include "Matrices.h"
#include "GameObject.h"
#include "ShaderProgram.h"
#include "Grape.h"

class Cylinder : public GameObject{
public:
	Cylinder() {}
	Cylinder(Vector3 origin, GLfloat radius, GLfloat length, Vector3 dir, GLint slices);
	~Cylinder() {}
	static void setInitialTexture();
	static void setShader(ShaderProgram &prog){ m_cProg = &prog; }
	virtual void render();

protected:
	virtual void setMaterial();

private:
	GLfloat length;
	GLfloat radius;
	GLint slices;
	Grape* fruitEdge;

	static ShaderProgram *m_cProg;
	void DrawCylinder();
};

#endif