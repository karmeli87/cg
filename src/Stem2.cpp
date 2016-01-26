#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"
#include "Stem2.h"
#include "Stem3.h"
#include "Grape.h"


Stem2::Stem2(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res) :Cylinder(pos, r, size, angle, res){

	for (int i = 0; i < stem3num; i++){
		stem3Array[i] = new Stem3(
			origin + (i + 1)*size / stem3num*glm::normalize(axis),
			r / 2,	// half the radius of stem1
			size / 3 * 2,	// two thirds the length of stem1
			glm::vec3(45 * i, 90, 45),// angle
			res
			);

	}
}

void Stem2::render(){
	//printf("render stem2");
	this->Cylinder::render();
	for (int i = 0; i < stem3num; i++){
		stem3Array[i]->render();
	}
}