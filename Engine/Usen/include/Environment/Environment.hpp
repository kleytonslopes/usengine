#pragma once
#ifndef US_ENVIRONMENT_HPP
#define	US_ENVIRONMENT_HPP

#include "Core/UniquePtr.hpp"
#include <Runtime/Application.hpp>
#include "Core/TickClass.hpp"

namespace us::env::Environment
{
	inline UApplication* Applicaiton;
	inline UTickClass* TickComponent = new UTickClass();
}

#endif // !US_ENVIRONMENT_HPP
