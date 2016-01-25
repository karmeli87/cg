#ifndef GRAPE_CLASS
#define GRAPE_CLASS

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>

#include "Matrices.h"
#include "ShaderProgram.h"
#include "GameObject.h"

class Grape: public GameObject{
	
public:
	Grape(){}
	Grape(Vector3 radiusVector);
	Grape(Vector3 pos,Vector3 dir, Vector3 radiusVector);
	~Grape(){}
	static void setShader(ShaderProgram &prog){m_cProg = &prog;}
	static void setInitialTexture();
	virtual void render();
	virtual void move(Vector3 new_pos);
protected:
	virtual void setMaterial();

private:
	Vector3 rVector;
	void DrawEllipsoid();
	static ShaderProgram *m_cProg;
};

#endif