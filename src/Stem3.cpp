#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"
#include "Stem3.h"
#include "Grape.h"


Stem3::Stem3(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
	fruitEdge = new Grape(pos + glm::normalize(angle)*size, glm::normalize(angle), glm::vec3(0.5, 0.5, 0.7));
}

void Stem3::render(){
	fruitEdge->render();
	Cylinder::render();

}