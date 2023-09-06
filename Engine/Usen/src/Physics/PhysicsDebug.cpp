/*********************************************************************
 *   File: PhysicsDebug.cpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#include "upch.hpp"
#include "Physics/PhysicsDebug.hpp"
#include "Renderer/OpenGL/ShaderOpenGL.hpp"
#include "Renderer/ShaderParameters.hpp"
#include "Runtime/Application.hpp"
#include "Camera/Camera.hpp"
#include "Presentation/Window.hpp"
#include "Framework/Scene.hpp"

UPhysicsDebug::UPhysicsDebug()
{
	FShaderParameters sp{};
	sp.Name = "debug";
	Shader = new UShaderOpenGL();

	Shader->LoadShader(sp.GetVertexFilePath().c_str(), sp.GetFragmentFilePath().c_str());
}
           
UPhysicsDebug::~UPhysicsDebug()
{
	delete Shader;
}

void UPhysicsDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor)
{
	__super::drawLine(from, to, fromColor, toColor);
}

void UPhysicsDebug::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
	FVector fromVec = FVector{ from.getX(), from.getY() , from.getZ() };
	FVector toVec = FVector{ to.getX(), to.getY() , to.getZ() };
	Application->GetRenderer()->DebugDrawLine(fromVec, toVec, FColor::Blue);
}

void UPhysicsDebug::reportErrorWarning(const char* warningString)
{
}

void UPhysicsDebug::draw3dText(const btVector3& location, const char* textString)
{
}

void UPhysicsDebug::setDebugMode(int debugMode)
{
	mMebugMode = debugMode;
}

int UPhysicsDebug::getDebugMode() const
{
	return btIDebugDraw::DBG_DrawWireframe;
}

void UPhysicsDebug::drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
}
