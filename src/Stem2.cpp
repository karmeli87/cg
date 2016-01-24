#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Cylinder.h"
#include "Stem2.h"

#include "Stem3.h"
#include "Grape.h"


Stem2::Stem2(Vector3 pos, GLfloat r, GLfloat size, Vector3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
	std::cout << "numof ver branch " << origin << std::endl;
	for (int i = 0; i < stem3num; i++){
		Vector3 tmp2 = Vector3(std::cosf(angle.x), std::cosf(angle.y), std::cosf(angle.z)).normalize();
		stem3Array[i] = new Stem3(
			tmp2 * i *(size / stem3num ),		// move position along main axis: dependent of the number of stem2's
			r / 2,	// half the radius of stem1
			size / 3 * 2,	// two thirds the length of stem1
			Vector3(angle.x, angle.y, angle.z),// angle
			res
			);

	}
}

void Stem2::render(){

	Cylinder::render();
	/*for (int i = 0; i < stem3num; i++){
		stem3Array[i]->render();
	}*/
}