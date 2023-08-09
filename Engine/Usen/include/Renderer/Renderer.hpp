/*********************************************************************
 *   File: Renderer.hpp
 *  Brief: 
 * 
 * Author: Kleyton Lopes
 *   Date: July 2023
 * 
 * Copyright (c) 2023 Kyrnness. All rights reserved. 
 *********************************************************************/
#pragma once

#ifndef US_RENDERER_HPP
#define	US_RENDERER_HPP


#include "Base/Class.hpp"
#include "Renderer/ShaderParameters.hpp"
#include "Renderer/OpenGL/ShaderOpenGL.hpp"
#include "Renderer/Shader.hpp"
#include "Renderer-generated.hpp"

class BShader;
class AEntity;
class UShaderOpenGL;

class BRenderer : public BClass
{
	DEFAULT_BODY_GENERATED()
public:
	void Destroy() override;

	void Draw(AEntity* entity, float deltaTime);
	virtual void StartFrame() { /* override */ };
	virtual void EndFrame() { /* override */ };
	virtual void OnWindowResize(uint32 width, uint32 height) { /* override */ };


	template<typename T>
	inline T* CreateShader(const FShaderParameters& parameters)
	{
		T* shader = new T();
		shader->LoadShader(parameters.GetVertexFilePath().c_str(), parameters.GetFragmentFilePath().c_str());

		Shaders[parameters.Name] = shader;

		return shader;
	}

	BShader* GetShader(const FString& shaderName);

protected:
	TMap<FString, BShader*> Shaders;
};

#endif // !US_RENDERER_HPP