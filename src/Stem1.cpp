#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

#include "Cylinder.h"
#include "Stem1.h"
#include "Stem2.h"
#include "Grape.h"


Stem1::Stem1(glm::vec3 pos, GLfloat r, GLfloat size, glm::vec3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
	for (int i = 0; i < stem2num; i++){	
		float randFl = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // random between 0 and 1
		float randFl1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // random between 0 and 1
		float randFl2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX); // random between 0 and 1

		float high = size / 3 * 2;
		float low = size / 3 * 1;
		float randLength = ((low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)))));
		high = r / 3 * 2;
		low = r / 3 * 1;
		float randRadius = ((low + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (high - low)))));

		stem2Array[i] = new Stem2(
			origin + (i + 1)*size / (1+ stem2num) *glm::normalize(axis),
			randRadius,	// half the radius of stem1
			randLength,	// two thirds the length of stem1
			glm::vec3(45*randFl, 90 * randFl1, 45 * randFl2),// angle
			res
		);

	}
}

void Stem1::render(){

	this->Cylinder::render();
	for (int i = 0; i < stem2num; i++){
		stem2Array[i]->render();
	}
}

