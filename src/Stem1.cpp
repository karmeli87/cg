#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include "Helpers.h"
#include "Cylinder.h"
#include "Stem1.h"
#include "Stem2.h"
#include "Grape.h"


Stem1::Stem1(Vector3 pos, GLfloat r, GLfloat size, Vector3 angle, GLint res) :Cylinder(pos, r, size, angle, res){
	for (int i = 0; i < stem2num; i++){	
		stem2Array[i] = new Stem2(
			origin+(i + 1)*size*dir.normalize() / stem2num,
			r / 2,	// half the radius of stem1
			size / 3 * 2,	// two thirds the length of stem1
			Vector3(45*i,90,45),// angle
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

