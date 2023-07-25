#pragma once
#ifndef US_ENVIRONMENT_HPP
#define	US_ENVIRONMENT_HPP

#include "Core/UniquePtr.hpp"
#include <Runtime/Application.hpp>

namespace us::env::Environment
{
	inline UUniquePtr<UApplication> Applicaiton = UUniquePtr<UApplication>::Make();
}

#endif // !US_ENVIRONMENT_HPP
