/*********************************************************************
 *   File: Attachment.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_ATTACHMENT_HPP
#define	US_ATTACHMENT_HPP


#include "Base/Class.hpp"
#include "Attachment-generated.hpp"

class AActor;

class UAttachment : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	explicit UAttachment();
	virtual ~UAttachment();

	bool HasAttachments() const;
	void Initialize() override;

private:
	TMap<FString, AActor*> Attachments;

	void Attatch(AActor* actor);
	bool Detach(AActor* actor);

	friend class AEntity;
	friend class AActor;
};

#endif // !US_ATTACHMENT_HPP