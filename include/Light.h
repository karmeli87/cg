#include <glm/glm.hpp>
#include "ShaderProgram.h"

class Light
{
public:
	Light(glm::vec3 pos);
	~Light();
	static void setShader(ShaderProgram &shader){
		m_cProg = &shader;
	}
private:
	static ShaderProgram* m_cProg;
	glm::vec3 point;
	GLint matAmbientLoc;
	GLint matDiffuseLoc;
	GLint matSpecularLoc;
	GLint lightPosLoc;
};

