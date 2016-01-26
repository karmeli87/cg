#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"
#include "Stem3.h"
#include "Grape.h"


Stem3::Stem3(Vector3 pos, GLfloat r, GLfloat size, Vector3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
	fruitEdge = new Grape(origin, dir, Vector3(1, 1, 2));
}

void Stem3::render(){

	Cylinder::render();
	fruitEdge->render();
}