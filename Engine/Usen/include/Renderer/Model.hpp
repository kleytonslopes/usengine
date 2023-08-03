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
class URenderComponent;

class UModel : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UModel();
	virtual ~UModel();

	void Initialize() override;
	virtual void LoadModel() = 0;
	virtual void Draw(float deltaTime) = 0;
	void SetMeshActor(AMesh* actor);

protected:
	AMesh* MeshActor = nullptr;
	URenderComponent* RenderComponent = nullptr;
	FString DirectoryPath;

};

#endif // !US_MODEL_HPP