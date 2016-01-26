#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"
#include "Stem3.h"
#include "Grape.h"


Stem3::Stem3(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
	//fruitEdgeArray[0] = new Grape(pos, angle, glm::vec3(1, 1, 2));
	fruitEdge = new Grape(pos+glm::normalize(angle)*size, angle, glm::vec3(1, 1, 2));
}

void Stem3::render(){
	//fruitEdgeArray[0]->render();
	fruitEdge->render();
	Cylinder::render();

}