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
#include "Renderer/Model.hpp"

DEFAULT_BODY(UMeshRenderer)

void UMeshRenderer::SetModel(UModel* model)
{
	this->Model = model;
}
