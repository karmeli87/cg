#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"
#include "Stem2.h"
#include "Stem3.h"
#include "Grape.h"


Stem2::Stem2(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res) :Cylinder(pos, r, size, angle, res){

}

void Stem2::render(){
	Cylinder::render();
}