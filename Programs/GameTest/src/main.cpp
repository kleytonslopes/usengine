/*********************************************************************
 *   File: main.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/

#include "Environment/Environment.hpp"
#include "Runtime/ApplicationGame.hpp"
#include "Pawns/Pawn.hpp"

#include "Core/Vectors/Vector3.hpp"

 //operator glm::vec3& (const Vector3& vc) { return glm::vec3{}; }

int main()
{
	try
	{
		Vector3 nv3_1{1.0, 2.2, 3.1};
		Vector3 nv3_2{1.0, 3.2, 2.1};

		glm::vec3 gv3_1{1.0, 2.2, 3.1};
		glm::vec3 gv3_2{1.0, 3.2, 2.1};

		double ndot = Vector3::Dot(nv3_1, nv3_1);
		float gdot = glm::dot(gv3_1, gv3_1);

		Vector3 cvnv3_1 = Vector3::Cross(nv3_1, nv3_2);
		glm::vec3 cvgv3_1 = glm::cross(gv3_1, gv3_2);

		Vector3 nnv3 = Vector3::Normalize(cvnv3_1);
		glm::vec3 ngv_1 = glm::normalize(cvgv3_1);

		

		us::env::Environment::Applicaiton = new UApplicationGame();
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