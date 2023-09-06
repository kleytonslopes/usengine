/*********************************************************************
 *   File: Color.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: September 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Core/Color.hpp"


FColor FColor::White{1.f, 1.f, 1.f, 1.f};
FColor FColor::Black{0.f, 0.f, 0.f, 1.f};
FColor FColor::Red{1.f, 0.f, 0.f, 1.f};
FColor FColor::Green{0.f, 1.f, 0.f, 1.f};
FColor FColor::Blue{0.f, 0.f, 1.f, 1.f};
FColor FColor::Cyan{0.f, 1.f, 1.f, 1.f};
FColor FColor::Pink{1.f, 0.f, 1.f, 1.f};
FColor FColor::Yellow{1.f, 1.f, 0.f, 1.f};
FColor FColor::Orange{1.f, 0.5f, 0.f, 1.f};
FColor FColor::Purple{0.5f, 0.0f, 0.5f, 1.f};

FColor::FColor(float r, float g, float b, float a) 
	: R{r}
	, G{g}
	, B{b}
	, A{a}
{
}
