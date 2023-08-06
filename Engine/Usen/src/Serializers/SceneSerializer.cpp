/*********************************************************************
 *   File: SceneSerializer.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Serializers/SceneSerializer.hpp"
#include "Serializers/EntitySerializer.hpp"

#include "Framework/Scene.hpp"
#include "Actors/Actor.hpp"
#include "Renderer/ShaderParameters.hpp"
#include "Components/Component.hpp"

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

FSceneSerializer::FSceneSerializer()
{
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

FSceneSerializer::~FSceneSerializer()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void FSceneSerializer::Serialize()
{
	SetFilePath(FText::Format(Content::SceneFilePath, Scene->Settings.Name.c_str()));

	BeginSection("Scene", Scene->Settings.Name);

	SerializeShaders();
	SetializeEntities();

	EndSection();

	Save();
}

bool FSceneSerializer::Deserialize(const FString& scenePath)
{
	seriFilePath = FText::Format(Content::SceneFilePath, scenePath.c_str());
	SeriNode data = Load(seriFilePath);

	if (!data["Scene"])
		return false;

	Scene->Settings.Name = Read<FString>(data, "Scene");
	DeserializeShaders(data);
	DeserializeEntities(data);

	return true;
}

void FSceneSerializer::SetScene(UScene* scene)
{
	this->Scene = scene;
}

void FSceneSerializer::SerializeShaders()
{
	Key("Shaders");
	BeginSection();

	Key<TVector<FShaderParameters>>("name", Scene->Settings.ShadersParameters);

	EndSection();
}

void FSceneSerializer::SetializeEntities()
{
	BeginArray("Entities");

	TMap<FString, AEntity*>::iterator it;


	for (it = Scene->entities.begin(); it != Scene->entities.end(); it++)
	{
		BeginSection("Entity", it->second->GetId());
		Key("Identity", it->second->GetIdentity());
		it->second->Serialize(out);

		ULOG(ELogLevel::ELL_TRACE, FText::Format("Iterating with %s", it->first.c_str()));
		EndSection();
	}

	EndArray();
}

void FSceneSerializer::DeserializeShaders(SeriNode& data)
{
	auto shaders = data["Shaders"];
	if (shaders)
	{
		Scene->Settings.ShadersParameters = Read<TVector<FShaderParameters>>(shaders, "name");
	}
}

void FSceneSerializer::DeserializeEntities(SeriNode& data)
{
	auto entities = data["Entities"];
}