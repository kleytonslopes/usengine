/*********************************************************************
 *   File: SceneSerializer.cpp
 *  Brief:
 *
 * Author: Kleyton
 *   Date: July 2023
 *
 * Copyright (c) 2023 Sunydark. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "Serializer/SceneSerializer.hpp"
#include "Serializer/EntitySerializer.hpp"
#include "Framework/Scene.hpp"
#include "Framework/Entity.hpp"
#include "Renderer/ShaderParameters.hpp"
#include "Components/Interface/IComponent.hpp"

YAML::Emitter& operator<<(YAML::Emitter& out, const TVector<FShaderParameters>& vector)
{
	out << YAML::Flow;
	out << YAML::BeginSeq;

	for (const FShaderParameters& val : vector)
	{
		out << val.Name;
	}

	out << YAML::EndSeq;

	return out;
}

USceneSerializer::USceneSerializer(UScene* scene)
	: Scene{ scene }
{

}

USceneSerializer::~USceneSerializer()
{

}

void USceneSerializer::Serialize()
{
	SetFilePath(FText::Format(Content::SceneFilePath, Scene->sceneSettings.Name.c_str()));

	BeginMap("Scene", Scene->sceneSettings.Name);

	SerializeShaders();
	SetializeEntities();

	EndMap();

	Save();
}

bool USceneSerializer::Deserialize(const FString& scenePath)
{
	filePath = FText::Format(Content::SceneFilePath, scenePath.c_str());
	YAML::Node data = Load(filePath);

	if (!data["Scene"])
		return false;

	Scene->sceneSettings.Name = Read<FString>(data, "Scene");
	DeserializeShaders(data);

	return true;
}

void USceneSerializer::SerializeShaders()
{
	Key("Shaders");
	BeginMap();

	Key<TVector<FShaderParameters>>("name", Scene->sceneSettings.ShadersParameters);

	EndMap();
}
void USceneSerializer::SetializeEntities()
{
	BeginSequence("Entities");

	TMap<FString, UEntity*>::iterator it;
	

	for (it = Scene->entities.begin(); it != Scene->entities.end(); it++)
	{
		it->second->EntitySerializer->Serialize(out);

		ULOG(ELogLevel::ELL_TRACE, FText::Format("Iterating with %s", it->first.c_str()));
	}
	EndSequence();
}

void USceneSerializer::DeserializeShaders(YAML::Node& data)
{
	auto shaders = data["Shaders"];
	if (shaders)
	{
		Scene->sceneSettings.ShadersParameters = Read<TVector<FShaderParameters>>(shaders, "name");
	}
}

void USceneSerializer::DeserializeEntities(YAML::Node& data)
{
	auto entities = data["Entities"];
}
