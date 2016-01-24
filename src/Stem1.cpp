#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Helpers.h"
#include "Cylinder.h"
#include "Stem1.h"
#include "Stem2.h"
#include "Stem3.h"
#include "Grape.h"


Stem1::Stem1(Vector3 pos, GLfloat r, GLfloat size, Vector3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
		angle = angle*M_PI / 180;
	Vector3 tmp2 = Vector3(std::cosf(angle.x), std::cosf(angle.y), std::cosf(angle.z)).normalize();
	std::cout << "angle " << tmp2 << std::endl;
	for (int i = 0; i < stem2num; i++){
		
		stem2Array[i] = new Stem2(
			//angle* i *(size / stem2num + 1),
			pos+tmp2*(i + 1)*size / stem2num,
			//tmp2 * (i+1) *(size /((float) stem2num) ),	// move position along main axis: dependent of the number of stem2's
			r / 2,	// half the radius of stem1
			size / 3 * 2,	// two thirds the length of stem1
			Vector3(90,90,0),// angle
			res
		);

	}
}

void Stem1::render(){

	Cylinder::render();
	for (int i = 0; i < stem2num; i++){
		stem2Array[i]->render();
	}
}

