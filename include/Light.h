#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "GameObject.h"

class Light : public GameObject
{
public:
	Light(glm::vec3 pos);
	~Light();
	void ShowLightSource();

	glm::vec3 getPos(){ return origin; }
	void setPos(glm::vec3 pos){ 
		origin += pos; 
		glUniform3f(lightPosLoc, origin.x, origin.y, origin.z);

	}
	void virtual render();

private:
	virtual void setMaterial(){};
	GLint matAmbientLoc;
	GLint matDiffuseLoc;
	GLint matSpecularLoc;
	GLint lightPosLoc;

};

