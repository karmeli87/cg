#include "RenderTriangle.h"

#include <iostream>
#include <cmath>
#include "ShaderProgram.h"
#include "Grape.h"
#include "Cylinder.h"
#include "Matrices.h"
#include "Helpers.h"


// vertex shader program
const GLchar* vertexShaderRTSrc = ShaderProgram::LoadShaderFromFile("./shaders/vertex.fs");

// fragment shader program
const GLchar* fragShaderRTSrc = ShaderProgram::LoadShaderFromFile("./shaders/fragment.fs");


Cylinder** cylArr;
void initCylArr() {
	cylArr = new Cylinder*[3];
	GLint slices = 20;
	GLfloat x = 0;
	GLfloat y = 0;
	GLfloat z = 0;
	GLfloat radius = 0.3;
	GLfloat length = 8;
	Vector3 angle = Vector3(15, 30, 67);
	cylArr[0] = new Cylinder(Vector3(x, y, z), radius, length, angle, slices);
	cylArr[1] = new Cylinder(Vector3(x +5, y, z), radius, length, Vector3(0,90,0), slices);
	cylArr[2] = new Cylinder(Vector3(x, y, z), radius, length, angle, slices);
}
// constructor
RenderTriangle::RenderTriangle()
  : m_iWidth( 800 )
  , m_iHeight( 600 )
  , m_fHeightAngle( 0.4f )
  , m_fNearDistance( 1.0f )
  , m_fFarDistance( 150.0f )
  , m_fRotX( 0.0f )
  , m_fRotY( 0.0f )
  , m_fTransZ(-10.0f)
{}



void
RenderTriangle::setWindowSize( int iWidth, int iHeight )
{
  m_iWidth = iWidth;
  m_iHeight = iHeight;
  glViewport( 0, 0, m_iWidth, m_iHeight );      // tells OpenGL the new size of the render area
}


void
RenderTriangle::initGL()
{
  //----------------------------------------------------------------------
  // create program and link
  //----------------------------------------------------------------------
  if( m_cProg.addShader( &vertexShaderRTSrc, GL_VERTEX_SHADER ) ) return;
  if(m_cProg.addShader(&fragShaderRTSrc, GL_FRAGMENT_SHADER)) return;
  if( m_cProg.linkShaders() ) return;
  
  // determine bindings with shader
  m_iProjectionMatrixID = glGetUniformLocation(m_cProg.getPrgID(), "cProjectionMatrix");
  m_iModelviewMatrixID = glGetUniformLocation(m_cProg.getPrgID(), "cModelviewMatrix");

  //----------------------------------------------------------------------
  // create object
  //----------------------------------------------------------------------
  Grape::setInitialTexture();
  Cylinder::setInitialTexture();
  Grape::setShader(m_cProg);
  Cylinder::setShader(m_cProg);
  
  initCylArr();
  //-----------------------------------------------------------------
  // init GL
  //-----------------------------------------------------------------

  // set background color to black
  glClearColor(0.0f,0.0f,0.0f,0.0f);
  // set depth buffer to far plane
  glClearDepth(1.0f);
  // enable depth test with the z-buffer
  glEnable(GL_DEPTH_TEST);

  // fill the polygon
  glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);

  // do not use culling
  glDisable(GL_CULL_FACE);

  // enable anti-aliasing
  glEnable( GL_MULTISAMPLE_ARB );


}


void
RenderTriangle::uninitGL()
{
  //-----------------------------------------------------------------
  // uninit GL
  //-----------------------------------------------------------------

  // delete buffer objects
  
  // destroy vertex array object

}



void
RenderTriangle::renderCamera()
{
  // setup projection matrix
  float fLeft, fRight, fBottom, fTop;
  fTop = m_fNearDistance * tanf(m_fHeightAngle / 2.0f);
  fRight = fTop * (float)m_iWidth / (float)m_iHeight;
  fBottom = -fTop;
  fLeft = -fRight;

  // builds projection matrix like glFrustum
  for(unsigned int i = 0; i < 16; i++) m_afProjectionMatrix[i] = 0.0f;
  m_afProjectionMatrix[0] = (2.0f * (float)m_fNearDistance) / (fRight - fLeft);
  m_afProjectionMatrix[5] = (2.0f * m_fNearDistance) / (fTop - fBottom);
  m_afProjectionMatrix[8] = (fRight + fLeft) / (fRight - fLeft);
  m_afProjectionMatrix[9] = (fTop + fBottom) / (fTop - fBottom);
  m_afProjectionMatrix[10] = -(m_fFarDistance + m_fNearDistance) / (m_fFarDistance - m_fNearDistance);
  m_afProjectionMatrix[11] = -1.0f;
  m_afProjectionMatrix[14] = -2.0f * m_fFarDistance * m_fNearDistance / (m_fFarDistance - m_fNearDistance);
  glUniformMatrix4fv(m_iProjectionMatrixID, 1, false, m_afProjectionMatrix);
  
  // setup modelview matrix
  
  
  Matrix4 m_afModelViewMatrix = rotationMatrix(m_fRotX, m_fRotY, 0);
  m_afModelViewMatrix[14] = m_fTransZ;

  Matrix4 sceneOffset = Matrix4();
 // sceneOffset = 0.5*sceneOffset;
  sceneOffset[12] = 0;
  sceneOffset[13] = 0;
  sceneOffset[14] = 0;
  Matrix4 sendToShader = sceneOffset*Matrix4(m_afModelViewMatrix);
  glUniformMatrix4fv(m_iModelviewMatrixID, 1, false, &sendToShader[0]);

}

unsigned int lastSelection = 0;

void RenderTriangle::selectObject(unsigned int index){
/*	grapeArr[lastSelection]->deselect();
	if (index == 0){
		return;
	}
	grapeArr[index-1]->select();
	lastSelection = index-1;*/
}
void
RenderTriangle::moveObject2D(unsigned int index, int x, int y){
	//grapeArr[index - 1]->move(Vector3(-(float)(x) / (2*m_iWidth)*m_fTransZ,(float)(y) / (2*m_iHeight)*m_fTransZ, 0));
}
void
RenderTriangle::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

  for (int i = 0; i < 5; i++){
	 // glStencilFunc(GL_ALWAYS, i + 1, -1);
	//  grapeArr[i]->render();
  }
  //cylArr[0]->render();
  for (int i = 0; i < 3; i++) {
	  cylArr[i]->render();
  }
}