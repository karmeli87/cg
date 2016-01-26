#ifndef GRAPE_CLASS
#define GRAPE_CLASS

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>

#include "ShaderProgram.h"
#include "GameObject.h"

class Grape: public GameObject{
	
public:
	Grape(){}
	Grape(glm::vec3 radiusVector);
	Grape(glm::vec3 pos,glm::vec3 dir, glm::vec3 radiusVector);
	~Grape(){}
	static void setShader(ShaderProgram &prog){m_cProg = &prog;}
	static void setInitialTexture();
	virtual void render();
	virtual void move(glm::vec3 new_pos);
protected:
	virtual void setMaterial();

private:
	glm::vec3 rVector;
	void DrawEllipsoid();
	static ShaderProgram *m_cProg;
};

#endif