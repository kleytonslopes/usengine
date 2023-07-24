/*********************************************************************
 *   File: main.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
 //#include "Runtime/Application.hpp"
#include "Environment.hpp"

int main()
{
	try
	{
		us::env::Environment::Applicaiton = new UApplication();
		us::env::Environment::Applicaiton->Run();
		delete us::env::Environment::Applicaiton;
	}
	catch (const std::exception&)
	{
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}