/*********************************************************************
 *   File: Class-generated.hpp
 *  Brief: This class is automatically generated by UsEngine ClassCreator
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#include "Core/Macros.hpp"
#include "Core/ClassOf.hpp"

#undef CURRENT_CLASS_IDENTITY_FILE
#define CURRENT_CLASS_IDENTITY_FILE hpp_BClass_IWeakClass

#define hpp_BClass_IWeakClass_def \
private: \
	using Super = IWeakClass; using This = BClass; \
	DEFINE_CAST_FUNCTION() \
public: \
	DEFINE_OPERATOR_CPY(BClass) \
	DEFINE_OPERATOR_MOV(BClass) \
	DEFINE_IDENTITY_BODY() \
	DEFINE_GET_CLASS(BClass) \
private:
