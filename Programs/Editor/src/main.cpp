/*********************************************************************
 *   File: main.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/

#include "Environment.hpp"

int main()
{
	try
	{
		us::env::Environment::Applicaiton.Get()->Run();
		us::env::Environment::Applicaiton.Destroy();
	}
	catch (const std::exception&)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}