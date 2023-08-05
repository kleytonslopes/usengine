/*********************************************************************
 *   File: ApplicationEditor.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Runtime/ApplicationEditor.hpp"
#include "Framework/EditorGameInstance.hpp"

UApplicationEditor::UApplicationEditor()
{
	
	ULOG(ELogLevel::ELL_INFORMATION, FText::Format("%s Created!", Identity.c_str()));
}

UApplicationEditor::~UApplicationEditor()
{
	ULOG(ELogLevel::ELL_WARNING, FText::Format("%s Destroyed!", Identity.c_str()));
}

void UApplicationEditor::Create()
{
	DefaultGameInstance = UEditorGameInstance::GetClass();
	DefaultRenderer = URendererOpenGL::GetClass();

	Super::Create();
}
