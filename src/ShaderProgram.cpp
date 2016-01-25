#include "ShaderProgram.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm>


// constructor
ShaderProgram::ShaderProgram()
  : m_uiShaderPrg(0)
{
	m_uiShaderPrg = glCreateProgram();
	m_auiShaderIDs.resize(0);
}

// constructor
ShaderProgram::~ShaderProgram()
{
  // free all shader objects
  for( auto i=m_auiShaderIDs.begin(); i != m_auiShaderIDs.end(); ++i)
  {
    glDeleteShader( *i );
  }

  // free program
  if( m_uiShaderPrg ) glDeleteProgram( m_uiShaderPrg );
}

const GLchar* ShaderProgram::LoadShaderFromFile(const GLchar* shaderPath)
{
	GLchar* code;
	
	std::ifstream shaderFile;
	std::stringstream shaderStream;
	shaderFile.exceptions(std::ifstream::badbit);
	try
	{
		shaderFile.open(shaderPath);
		shaderStream << shaderFile.rdbuf();
		shaderFile.close();
		
		code = new char[shaderStream.str().size() + 1];
		strcpy(code, shaderStream.str().c_str());
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ\n at :" << shaderPath << " : " << e.what() <<std::endl;
	}
	
	return code;
}

int 
ShaderProgram::addShader( const GLchar * const * ppcSrc, GLenum eShaderType )
{
  GLuint  uiID;
  GLint   iCompiled;

  // create vertex shader
  uiID = glCreateShader( eShaderType );
  if(0 == uiID) return -1;

  m_auiShaderIDs.push_back( uiID );

  // compile shader
  glShaderSource( uiID, 1, ppcSrc, NULL);
  glCompileShader( uiID );

  // check for errors and output them
  glGetShaderiv( uiID, GL_COMPILE_STATUS, &iCompiled);
  if(!iCompiled)
  {
    GLint iLength;
    GLchar* pcMessage;

    glGetShaderiv( uiID, GL_INFO_LOG_LENGTH, &iLength);
    pcMessage = new GLchar[iLength];
    if(NULL == pcMessage) return -1;
    glGetShaderInfoLog( uiID, iLength, &iLength, pcMessage);
    std::cout << "compile error for shader " << eShaderType << ": " << pcMessage << std::endl;
    delete[] pcMessage;
    return -1;
  }

  // attach shader
  glAttachShader( m_uiShaderPrg, uiID);

  return 0;
}



int
ShaderProgram::linkShaders()
{
  GLint   iLinked;

  // link shaders to program
  glLinkProgram(m_uiShaderPrg);

  // check for errors and output them
  glGetProgramiv(m_uiShaderPrg, GL_LINK_STATUS, &iLinked);
  if(!iLinked)
  {
    GLint iLength;
    GLchar* pcMessage;

    glGetProgramiv(m_uiShaderPrg, GL_INFO_LOG_LENGTH, &iLength);
    pcMessage = new GLchar[iLength];
    if(NULL == pcMessage) return -1;
    glGetProgramInfoLog(m_uiShaderPrg, iLength, &iLength, pcMessage);
    std::cout << "linker error: " << pcMessage << std::endl;
    delete[] pcMessage;
    return -1;
  }

  useProgram();

  return 0;
}


void
ShaderProgram::useProgram()
{
  // set as active program
  glUseProgram(m_uiShaderPrg);
}

