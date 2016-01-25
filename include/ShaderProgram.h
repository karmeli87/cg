#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <GL/glew.h>
#ifdef _WIN32
#include "GL/wglew.h"
#endif
#include <GL/gl.h>


#include <vector>


class ShaderProgram
{
public:
  // constructor
  ShaderProgram();

  // destructor
  virtual ~ShaderProgram();

  // get the id of the program
  GLuint getPrgID() const { return m_uiShaderPrg; }

  // add a shader and compile it
  int addShader(const GLchar * const * ppcSrc, GLenum eShaderType);

  // link all shaders
  int linkShaders();

  // use this program
  void useProgram();

  static const GLchar* LoadShaderFromFile(const GLchar* shaderPath);

protected:

  // id for programs
  GLuint  m_uiShaderPrg;

  // vector storing all shader id's
  std::vector<GLuint> m_auiShaderIDs;

};



#endif