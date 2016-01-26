#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"
#include "Stem3.h"
#include "Grape.h"


Stem3::Stem3(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
	fruitEdge = new Grape(origin, dir, glm::vec3(1, 1, 2));
}

void Stem3::render(){

	Cylinder::render();
	fruitEdge->render();
}