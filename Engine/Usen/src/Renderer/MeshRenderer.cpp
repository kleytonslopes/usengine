/*********************************************************************
 *   File: MeshRenderer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Renderer/MeshRenderer.hpp"
#include "Renderer/Texture.hpp"
#include "Core/Vertex.hpp"

UMeshRenderer::UMeshRenderer()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UMeshRenderer::~UMeshRenderer()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}