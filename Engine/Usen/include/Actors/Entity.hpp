/*********************************************************************
 *   File: Entity.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ENTITY_HPP
#define	US_ENTITY_HPP


#include "Base/Class.hpp"
#include "Serializers/Serializer.hpp"
#include "Entity-generated.hpp"

class FEntitySerializer;


enum class EAttachMode
{
	EAM_SnapToTarget,
	EAM_KeepTrasform
};

struct FAttachmentSettings
{
	EAttachMode AttachMode = EAttachMode::EAM_SnapToTarget;
};

class AEntity : public BSerializer
{
	DEFAULT_BODY_GENERATED()

public:
	void Construct() override;
	void PostConstruct() override;
	void Update(float deltaTime) override;

	void SetOwner(AEntity* owner);
	virtual void AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings);
	virtual void DetachFromParent();
	FString GetParentId();

	template<typename T>
	T* GetParent()
	{
		return Cast<T*>(Parent);
	}

protected:
	AEntity* Owner = nullptr;
	AEntity* Parent = nullptr;
	FAttachmentSettings AttachmentSettings;

	bool bIsAttached = false;
	bool bIsDrawable = false;

	virtual void Draw(float deltaTime) {/* override */ }

private:
	friend class BRenderer;
	friend class UScene;
	friend class FSceneSerializer;
	friend class FEntitySerializer;
};

#endif // !US_ENTITY_HPP