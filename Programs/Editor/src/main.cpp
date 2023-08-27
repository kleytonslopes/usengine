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

#undef DEBUG 
#undef _DEBUG

int main()
{
	try
	{
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