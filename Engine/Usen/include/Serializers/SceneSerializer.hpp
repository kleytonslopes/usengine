/*********************************************************************
 *   File: SceneSerializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SCENE_SERIALIZER_HPP
#define	US_SCENE_SERIALIZER_HPP


#include "Serializers/Serializer.hpp"
#include "SceneSerializer-generated.hpp"

class UScene;

class FSceneSerializer : public BSerializer
{
	DEFAULT_BODY_GENERATED()
public:
	void Serialize() override;
	void Serialize(SeriFile& otherOut) override { /* DoNothing */ }
	bool Deserialize(const FString& scenePath) override;

	void SetScene(UScene* scene);

private:
	UScene* Scene = nullptr;

	void SerializeShaders();
	void SetializeEntities();

	void DeserializeShaders(SeriNode& data);
	void DeserializeEntities(SeriNode& data);
};

#endif // !US_SCENE_SERIALIZER_HPP