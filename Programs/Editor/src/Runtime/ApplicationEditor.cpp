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
#include "UI/EditorUI.hpp"

DEFAULT_BODY(UApplicationEditor)

void UApplicationEditor::Construct()
{
	Super::Construct();

	FConstructorHelper::MakeClassOf<URendererOpenGL>(DefaultRenderer);
	FConstructorHelper::MakeClassOf<UEditorGameInstance>(DefaultGameInstance);
}

void UApplicationEditor::PostConstruct()
{
	Super::PostConstruct();

	GameInstance = FConstructorHelper::CreateObject<UEditorGameInstance>();

	UIEditor = FConstructorHelper::CreateObject<UEditorUI>();
}

void UApplicationEditor::Initialize()
{
	Super::Initialize();

	UIEditor->Initialize();
}
