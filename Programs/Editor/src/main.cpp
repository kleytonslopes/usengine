/*********************************************************************
 *   File: main.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/

//#define _ITERATOR_DEBUG_LEVEL 2


#include "Environment/Environment.hpp"
#include "Runtime/ApplicationEditor.hpp"
#include "Pawns/Pawn.hpp"
#include "Core/Transform.hpp"
#include "Core/Math.hpp"
#include "glm/glm.hpp"

#undef DEBUG 
#undef _DEBUG

//void rotateVector(double& x, double& y, double& z, char axis, double angle) {
//	double cosA = cos(angle);
//	double sinA = sin(angle);
//
//	double tempX = x;
//	double tempY = y;
//	double tempZ = z;
//
//	if (axis == 'X' || axis == 'x') {
//		y = cosA * tempY - sinA * tempZ;
//		z = sinA * tempY + cosA * tempZ;
//	}
//	else if (axis == 'Y' || axis == 'y') {
//		x = cosA * tempX + sinA * tempZ;
//		z = -sinA * tempX + cosA * tempZ;
//	}
//	else if (axis == 'Z' || axis == 'z') {
//		x = cosA * tempX - sinA * tempY;
//		y = sinA * tempX + cosA * tempY;
//	}
//	else {
//		//std::cerr << "Invalid axis specified." << std::endl;
//	}
//}

// Quaternion structure
struct Quaternion {
	double w, x, y, z;

	Quaternion(double w, double x, double y, double z) : w(w), x(x), y(y), z(z) {}
};

// Function to normalize a quaternion
Quaternion normalize(const Quaternion& q) {
	double magnitude = std::sqrt(q.w * q.w + q.x * q.x + q.y * q.y + q.z * q.z);
	return Quaternion(q.w / magnitude, q.x / magnitude, q.y / magnitude, q.z / magnitude);
}

// Function to multiply two quaternions
Quaternion multiply(const Quaternion& q1, const Quaternion& q2) {
	return Quaternion(
		q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
		q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
		q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
		q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
	);
}

// Function to rotate a vector using a quaternion
void rotateVectorWithQuaternion(double& x, double& y, double& z, const Quaternion& rotationQuaternion) {
	Quaternion vectorQuaternion(0.0, x, y, z);
	Quaternion conjugate = Quaternion(rotationQuaternion.w, -rotationQuaternion.x, -rotationQuaternion.y, -rotationQuaternion.z);

	Quaternion rotatedVectorQuaternion = multiply(multiply(rotationQuaternion, vectorQuaternion), conjugate);

	x = rotatedVectorQuaternion.x;
	y = rotatedVectorQuaternion.y;
	z = rotatedVectorQuaternion.z;
}


int main()
{
	try
	{
		//

		////
		//double x = 1.0; // Initial X component
		//double y = 0.0; // Initial Y component
		//double z = 0.0; // Initial Z component

		//double angleX = 45.0 * M_PI / 180.0; // Angle in radians for rotation around X-axis
		//double angleY = 30.0 * M_PI / 180.0; // Angle in radians for rotation around Y-axis
		//double angleZ = 60.0 * M_PI / 180.0; // Angle in radians for rotation around Z-axis

		//// Create the rotation quaternions for each axis
		//Quaternion rotationQuaternionX(std::cos(angleX / 2.0), std::sin(angleX / 2.0), 0.0, 0.0);
		//Quaternion rotationQuaternionY(std::cos(angleY / 2.0), 0.0, std::sin(angleY / 2.0), 0.0);
		//Quaternion rotationQuaternionZ(std::cos(angleZ / 2.0), 0.0, 0.0, std::sin(angleZ / 2.0));

		//rotationQuaternionX = normalize(rotationQuaternionX);
		//rotationQuaternionY = normalize(rotationQuaternionY);
		//rotationQuaternionZ = normalize(rotationQuaternionZ);

		//ULOG(ELogLevel::ELL_DEBUG, FText::Format("Original Vector: (X: %f, Y: %f, Z: %f)", x, y, z));

		//// Rotate around X-axis
		//rotateVectorWithQuaternion(x, y, z, rotationQuaternionX);

		//ULOG(ELogLevel::ELL_DEBUG, FText::Format("Rotated Vector X: (X: %f, Y: %f, Z: %f)", x, y, z));

		//// Reset vector
		//x = 1.0;
		//y = 0.0;
		//z = 0.0;

		//// Rotate around Y-axis
		//rotateVectorWithQuaternion(x, y, z, rotationQuaternionY);

		//ULOG(ELogLevel::ELL_DEBUG, FText::Format("Rotated Vector y: (X: %f, Y: %f, Z: %f)", x, y, z));

		//// Reset vector
		//x = 1.0;
		//y = 0.0;
		//z = 0.0;

		//// Rotate around Z-axis
		//rotateVectorWithQuaternion(x, y, z, rotationQuaternionZ);

		//ULOG(ELogLevel::ELL_DEBUG, FText::Format("Rotated Vector z: (X: %f, Y: %f, Z: %f)", x, y, z));

		us::env::Environment::Applicaiton = new UApplicationEditor();
		us::env::Environment::Applicaiton->Run();
		us::env::Environment::Applicaiton->Destroy();

		delete us::env::Environment::TickComponent;
		delete us::env::Environment::RenderComponent;
		delete us::env::Environment::Applicaiton;

	}
	catch (const std::exception& ex)
	{
		us::env::Environment::Applicaiton->Destroy();

		delete us::env::Environment::TickComponent;
		delete us::env::Environment::RenderComponent;
		delete us::env::Environment::Applicaiton;

		ULOG(ELogLevel::ELL_FATAL, ex.what());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}