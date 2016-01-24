#ifndef RENDERTRIANGLE_H
#define RENDERTRIANGLE_H

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>


#include "RenderIf.h"
#include "ShaderProgram.h"
#include "Cylinder.h"
#include "Stem1.h"
#include "Stem2.h"
#include "Stem3.h"


class RenderTriangle : public RenderIf
{
public:
  // constructor
  RenderTriangle();
  // destructor
  virtual ~RenderTriangle() {};

  // set the size of the window
  virtual void setWindowSize( const int iWidth, const int iHeight );

  // initialize the GL state/scene
  virtual void initGL();
  // free all GL resources
  virtual void uninitGL();

  // update camera parameters and object orientation
  virtual void renderCamera();
  // render the scene
  virtual void render();

  // pass a key to the renderer
  virtual void keyPressed(unsigned char ucKey) {};

  // rotate scene
  virtual void rotX( const float fAngle ) { m_fRotX += fAngle; }
  virtual void rotY( const float fAngle ) { m_fRotY += fAngle; }
  virtual void transZ(const float fZ) { m_fTransZ *= fZ; }
  virtual void move(const float x, const float y){}
  virtual void selectObject(unsigned int);
  virtual void moveObject2D(unsigned int, int, int);

protected:
  int     m_iWidth;
  int     m_iHeight;

  // vertical viewing angle
  float   m_fHeightAngle;

  // near and far distance of scene
  float   m_fNearDistance;
  float   m_fFarDistance;

  // rotation angle around x-axis
  float   m_fRotX;
  // rotation angle around y-axis
  float   m_fRotY;
  // translation in z-direction
  float   m_fTransZ;

  // modelview matrix
  float   m_afModelViewMatrix[16];

  // projection matrix
  float   m_afProjectionMatrix[16];

  // shader programs
  ShaderProgram m_cProg;

  // ids for shader bindings
  GLint   m_iOrigin;
  GLint   m_iVertexAttribPosition;
  GLint   m_iProjectionMatrixID;
  GLint   m_iModelviewMatrixID;

  // ids for object
  GLuint  m_uiVAO;
  GLuint  m_uiVBOindices;
  GLuint  m_uiVBOcoords;

  // initial vertex list
  static float afVertexList[3 * 3];
  // initial index list
  static unsigned int auiIndexList[1 * 3];

  Stem1* mainStem;
};



#endif