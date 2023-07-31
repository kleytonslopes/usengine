/*********************************************************************
 *   File: Model.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_MODEL_HPP
#define	US_MODEL_HPP


#include "Base/Class.hpp"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Renderer/MeshRenderer.hpp"
#include "Model-generated.hpp"

class AMesh;

class UModel : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UModel();
	virtual ~UModel();

	virtual void LoadModel() = 0;
	void SetMeshActor(AMesh* actor);

protected:
	AMesh* MeshActor = nullptr;
	FString DirectoryPath;

};

#endif // !US_MODEL_HPP