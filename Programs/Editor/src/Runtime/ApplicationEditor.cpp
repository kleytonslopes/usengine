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

DEFAULT_BODY(UApplicationEditor)

void UApplicationEditor::Create()
{
	DefaultGameInstance = UEditorGameInstance::GetClass();
	DefaultRenderer = URendererOpenGL::GetClass();

	Super::Create();
}
