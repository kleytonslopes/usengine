/*********************************************************************
 *   File: SceneSerializer.hpp
 *  Brief: 
 * 
 * Author: Kleyton
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Sunydark. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_SCENE_SERIALIZER_HPP
#define	US_SCENE_SERIALIZER_HPP

#include "Serializer/Serializer.hpp"


class UScene;

class USceneSerializer : public USerializer
{
	DEFAULT_BODY(USerializer);
public:
	explicit USceneSerializer(UScene* scene);
	~USceneSerializer() final;

	void Serialize() override;
	void Serialize(YAML::Emitter& otherOut) override { /* DoNothing */ }
	bool Deserialize(const FString& scenePath) override;

private:
	UScene* Scene = nullptr;

	void SerializeShaders();
	void SetializeEntities();

	void DeserializeShaders(YAML::Node& data);
	void DeserializeEntities(YAML::Node& data);
};

#endif // !US_SCENE_SERIALIZER_HPP
