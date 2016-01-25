#ifndef HELPERS
#define HELPERS
#include "Matrices.h"

enum AngleMode{ Degree, Radian };
inline Matrix4 rotationMatrix(float m_fRotX, float m_fRotY, float m_fRotZ, AngleMode mode = Degree){

	Vector3 angles = Vector3(m_fRotX, m_fRotY, m_fRotZ);

	if (mode == Degree){
		angles = angles * 3.14159265f / 180.0f; // convert to radian
	}

	float cosa = std::cosf(angles.x);
	float sina = std::sinf(angles.x);
	float cosb = std::cosf(angles.y);
	float sinb = std::sinf(angles.y);
	float cosc = std::cosf(angles.z);
	float sinc = std::sinf(angles.z);

	return Matrix4(
		cosb*cosc, -cosb*sinc, sinb, 0,
		cosa*sinc + sina*sinb*cosc, cosa*cosc - sina*sinb*sinc, -sina*cosb, 0,
		sina*sinc - cosa*sinb*cosc, sina*cosc + cosa*sinb*sinc, cosa*cosb, 0,
		0, 0, 0, 1
		);
}

#endif