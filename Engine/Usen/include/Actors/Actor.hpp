/*********************************************************************
 *   File: Actor.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ACTOR_HPP
#define	US_ACTOR_HPP


#include "Actors/Entity.hpp"
#include "Components/TransformComponent.hpp"
#include "Actor-generated.hpp"

class UAttachment;

class AActor : public AEntity
{
	DEFAULT_BODY_GENERATED()

	using ComponentsMap = TMap<FString, AComponent*>;

public:
	void Destroy() override;
	void Construct() override;
	void Initialize() override;
	void Update(float deltaTime) override;

	void AttatchTo(AEntity* parent, FAttachmentSettings& attachmentSettings) override;
	void DetachFromParent() override;
	void Detach(AActor* entity);

	virtual void SetOrigin(FVector& vector);
	virtual void SetLocation(FVector& vector);
	virtual void SetRotation(FVector& vector);
	virtual void SetScale(FVector& vector);
	virtual void SetTransform(FTransform& transform);
	

	FVector GetLocation();
	FVector GetRotation();
	FVector GetScale();
	FVector GetSceneLocation();
	FTransform& GetTransform();

	
	

protected:
	UAttachment* Attachments = nullptr;
	ComponentsMap components;

	UTransformComponent* TransformComponent = nullptr;

	void Serialize(SeriFile& otherOut) override;

	template<typename T>
	bool HasComponent()
	{
		if (components.size() <= 0)
			return false;

		auto& comp = components[typeid(T).name()];
		if (!comp)
			return false;

		return true;
	}

	template<typename T>
	T* AddComponent()
	{
		T* component = FConstructorHelper::CreateWeakObject<T>();
		
		component->SetOwner(Owner);
		component->SetParent(this);
		//component->Construct();
		//component->PostConstruct();

		components[typeid(T).name()] = component;

		return component;
	}

	template<typename T, typename... Args>
	T* AddComponent(Args&& ... args)
	{
		T* component = FConstructorHelper::CreateWeakObject<T>(); //new T(std::forward<Args>(args)...);
		
		component->SetOwner(Owner);
		component->SetParent(this);
		//component->Construct();
		//component->PostConstruct();
		
		components[typeid(T).name()] = component;
		return component;
	}

	template<typename T>
	T* GetComponent()
	{
		return static_cast<T*>(components[typeid(T).name()]);
	}

	void Draw(float deltaTime) override;

	friend class FEntitySerializer;
	friend class UScene;
};

#endif // !US_ACTOR_HPP