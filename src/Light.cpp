#include "Light.h"

ShaderProgram* Light::m_cProg = NULL;

Light::Light(glm::vec3 pos)
{
	point = pos;

	lightPosLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.position");
	matAmbientLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.ambient");
	matDiffuseLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.diffuse");
	matSpecularLoc = glGetUniformLocation(Light::m_cProg->getPrgID(), "light.specular");

	glUniform3f(lightPosLoc, point.x, point.y, point.z);
	glUniform3f(matAmbientLoc, 0.2f, 0.2f, 0.2f);
	glUniform3f(matDiffuseLoc, 0.7f, 0.7f, 0.7f);
	glUniform3f(matSpecularLoc, 0.1f, 0.1f, 0.1f);
}


Light::~Light()
{
}
