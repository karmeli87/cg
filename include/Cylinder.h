#ifndef CYLINDER_CLASS
#define CYLINDER_CLASS

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>

#include "Common.h"
#include "GameObject.h"
#include "ShaderProgram.h"
#include "Grape.h"

class Cylinder : public GameObject{
public:
	Cylinder() {}
	Cylinder(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res);
	~Cylinder() {}
	static void setInitialTexture();
	virtual void render();

protected:
	virtual void setMaterial();
	GLfloat length;
	GLfloat radius;
	GLint slices;
	void DrawCylinder();
};

#endif
