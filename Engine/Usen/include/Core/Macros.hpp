/*********************************************************************
 *   File: Macros.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#define DEFAULT_BODY_GENERATED_FILTER_IN(A,B,C) A##B##C
#define DEFAULT_BODY_GENERATED_FILTER(A,B,C) DEFAULT_BODY_GENERATED_FILTER_IN(A,B,C)
#define DEFAULT_BODY_GENERATED(...) DEFAULT_BODY_GENERATED_FILTER(CURRENT_CLASS_IDENTITY_FILE,_,def);
