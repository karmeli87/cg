#include "RenderTriangle.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <iostream>
#include <cmath>
#include "ShaderProgram.h"
#include "Cylinder.h"
#include "Stem1.h"


// vertex shader program
const GLchar* vertexShaderRTSrc = ShaderProgram::LoadShaderFromFile("./shaders/vertex.fs");

// fragment shader program
const GLchar* fragShaderRTSrc = ShaderProgram::LoadShaderFromFile("./shaders/fragment.fs");

Stem1* mainStem;

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

  glUniform1i(glGetUniformLocation(m_cProg.getPrgID(), "material.diffuse"), 0);
  glUniform1i(glGetUniformLocation(m_cProg.getPrgID(), "material.specular"), 1);
  GLint lightPosLoc = glGetUniformLocation(m_cProg.getPrgID(), "light.position");
  GLint viewPosLoc = glGetUniformLocation(m_cProg.getPrgID(), "viewPos");
  glUniform3f(lightPosLoc, 0, 0, -10);
  glUniform3f(viewPosLoc, 0, 0, -10);
  //----------------------------------------------------------------------
  // create object
  //----------------------------------------------------------------------
  Grape::setInitialTexture();
  Cylinder::setInitialTexture();
  
  Grape::setShader(m_cProg);
  Cylinder::setShader(m_cProg);

  
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



  mainStem = new Stem1(glm::vec3(0, 0, 0), 0.5f, 20, glm::vec3(45, 45, 45), 20);
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

  glm::mat4 m_afModelViewMatrix = glm::eulerAngleXYZ<float>(glm::radians(m_fRotX), 0, glm::radians(m_fRotY));
  m_afModelViewMatrix[3].z = m_fTransZ;
  glUniformMatrix4fv(m_iModelviewMatrixID, 1, false, glm::value_ptr(m_afModelViewMatrix));

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
	//grapeArr[index - 1]->move(glm::vec3(-(float)(x) / (2*m_iWidth)*m_fTransZ,(float)(y) / (2*m_iHeight)*m_fTransZ, 0));
}
void
RenderTriangle::render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

	mainStem->render();
}