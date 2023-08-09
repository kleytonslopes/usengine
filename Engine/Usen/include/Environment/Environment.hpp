#pragma once
#ifndef US_ENVIRONMENT_HPP
#define	US_ENVIRONMENT_HPP

#include "Core/UniquePtr.hpp"
#include <Runtime/Application.hpp>
#include "Core/TickClass.hpp"

namespace us::env::Environment
{
	inline UUniquePtr<UApplication> Applicaiton;
	inline UUniquePtr<UTickClass> TickComponent = UUniquePtr<UTickClass>::Make();
}

#endif // !US_ENVIRONMENT_HPP
