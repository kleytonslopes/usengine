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
	virtual void Create();
	void Destroy() override;

	void Initialize() override;
	void Update(float deltaTime) override;

	void SetOwner(AEntity* owner);
	virtual void AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings);
	virtual void DetachFromParent();
	FString GetParentId();

	template<typename T>
	inline T* GetParent()
	{
		return Cast<T*>(Parent);
	}

protected:
	AEntity* Owner = nullptr;
	AEntity* Parent = nullptr;
	FAttachmentSettings AttachmentSettings;

	/*UUniquePtr<UAttachment> Attachments;*/

	bool bIsAttached = false;
	bool bIsCreated = false;

	void Serialize() override { /* override */ }
	void Serialize(SeriFile& otherOut) override;
	bool Deserialize(const FString& scenePath) override { return false; }

	virtual void Draw(float deltaTime);

private:
	//UUniquePtr<FEntitySerializer> Serializer;

	friend class BRenderer;
	friend class UScene;
	friend class FSceneSerializer;
	friend class FEntitySerializer;
};

#endif // !US_ENTITY_HPP