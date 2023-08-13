/*********************************************************************
 *   File: PhysicsDebug.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: August 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_PHYSICS_DEBUG_HPP
#define	US_PHYSICS_DEBUG_HPP

#include "Core/MinimalCore.hpp"
#include "glad/glad.h"

class UShaderOpenGL;
class UApplication;

class UPhysicsDebug : public btIDebugDraw
{
	
public:
	GLuint VBO, VAO;
	UShaderOpenGL* Shader = nullptr;
	UApplication* Application = nullptr;
	int mMebugMode;

	explicit UPhysicsDebug();
	virtual ~UPhysicsDebug();

	void drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) override;
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

	void reportErrorWarning(const char* warningString) override;
	void draw3dText(const btVector3& location, const char* textString) override;
	void setDebugMode(int debugMode) override;
	int getDebugMode()  const override;
	void drawContactPoint(const btVector3& PointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
};

#endif // !US_PHYSICS_DEBUG_HPP