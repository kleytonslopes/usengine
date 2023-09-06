/*********************************************************************
 *   File: EditorUI.cpp
 *  Brief:
 *
 * Author: Kleyton Lopes
 *   Date: August 2023
 *
 * Copyright (c) 2023 Kyrnness. All rights reserved.
 *********************************************************************/
#include "upch.hpp"
#include "UI/EditorUI.hpp"
#include "Runtime/Application.hpp"
#include "Presentation/Window.hpp"
#include "Camera/Camera.hpp"
#include "imgui.h"
#include "backends/imgui_impl_opengl3.h"
#include <backends/imgui_impl_sdl2.h>

#include "Mesh/StaticMesh.hpp"
#include "Mesh/Mesh.hpp"
#include "Pawns/Pawn.hpp"//remove this

DEFAULT_BODY(UEditorUI)

static float zero{ 0.f };
static float minBoundBox{ 0.1f };
static float maxFov{ 150.f };
static float min{ -999999.f };
static float max{ 999999.f };

void UEditorUI::Construct()
{
	Super::Construct();

	//GetApplication()->OnDrawEvent.Add(this, &UEditorUI::Draw);
	GetWindow()->OnPollEventsEvent.Add(this, &UEditorUI::OnPollEventsEvent);
	GetWindow()->OnMouseButtonEvent.Add(this, &UEditorUI::OnMouseButtonEvent);
	GetWindow()->OnMouseWheelEvent.Add(this, &UEditorUI::OnMouseWheelEvent);
	GetWindow()->OnMouseMovementEvent.Add(this, &UEditorUI::OnMouseMovementEvent);
}

void UEditorUI::PostConstruct()
{
	Super::PostConstruct();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	//io.BackendFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	//io.BackendFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	float fontSize = 18.0f;// *2.0f;
	io.Fonts->AddFontFromFileTTF(FText::Format(Content::FontPath, "Kanit", "Kanit-Regular").c_str(), fontSize);
	io.FontDefault = io.Fonts->AddFontFromFileTTF(FText::Format(Content::FontPath, "Kanit", "Kanit-SemiBold").c_str(), fontSize);
	
	//io.KeyMap[ImGuiKey_Tab] = SDL_KeyCode::SDLK_TAB;
	//io.KeyMap[ImGuiKey_MouseLeft] = SDL_BUTTON_LEFT;
	//io.KeyMap[ImGuiKey_MouseRight] = SDL_BUTTON_RIGHT;
	//io.KeyMap[ImGuiKey_MouseMiddle] = SDL_BUTTON_MIDDLE;

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplSDL2_InitForOpenGL(GetWindow()->GetSDLWIndow(), GetWindow()->GetSDLContext());
	ImGui_ImplOpenGL3_Init("#version 410");
}

void UEditorUI::Draw(float deltaTime)
{
	

	int width = GetWindow()->GetWidth();
	int height = GetWindow()->GetHeight();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = ImVec2(width, height);
	io.DeltaTime = deltaTime;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	static bool dockspaceOpen = true;
	static bool opt_fullscreen = true;
	static bool opt_padding = false;
	static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

	ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
	if (opt_fullscreen)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->WorkPos);
		ImGui::SetNextWindowSize(viewport->WorkSize);
		ImGui::SetNextWindowViewport(viewport->ID);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
		ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
	}
	else
	{
		dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
	}

	if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
		window_flags |= ImGuiWindowFlags_NoBackground;

	if (!opt_padding)
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

	ImGui::Begin("DockSpace Editor", &dockspaceOpen, window_flags);

	if (!opt_padding)
		ImGui::PopStyleVar();

	if (opt_fullscreen)
		ImGui::PopStyleVar(2);

	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
	{
		ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
		ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
	}

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Save"))
			{
				GetScene()->SaveScene();
			}

			ImGui::Separator();

			if (ImGui::MenuItem("Exit"))
			{
				GetWindow()->SetShouldClose(true);
			}

			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	}

	{ // 3D Viewport
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2{ 0,0 });

		ImGui::Begin("Viewport");
		ImVec2 vpSize = ImGui::GetContentRegionAvail();
		if ((viewportSize.x != vpSize.x) || (viewportSize.y != vpSize.y))
		{
			viewportSize.x = vpSize.x;
			viewportSize.y = vpSize.y;
			GetScene()->GetCamera()->SetViewSize((int)viewportSize.x, (int)viewportSize.y);
			GetRenderer()->OnViewportResize((int)viewportSize.x, (int)viewportSize.y);
		}

		uint32 textureId = GetRenderer<URendererOpenGL>()->GetScreenTex();

			ImGui::GetWindowDrawList()->AddImage(
				(void*)textureId, ImVec2(ImGui::GetCursorScreenPos()),
				ImVec2(ImGui::GetCursorScreenPos().x + viewportSize.x, ImGui::GetCursorScreenPos().y + viewportSize.y), ImVec2(0, 1), ImVec2(1, 0));

		ImGui::PopStyleVar();
		ImGui::End();

		//ImGui::Image((void*)textureId, ImVec2{ viewportSize.x, viewportSize.y }, ImVec2{0, 1}, ImVec2{ 1, 0 });
		/*
		ImGui::PopStyleVar();
		ImGui::End();
		*/

	}

	{ // Camera

		ImGui::Begin("Camera");
		{
			if (ImGui::TreeNode("m1001", "Position"))
			{
				FVector& location = GetScene()->GetCamera()->GetLocation();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &location.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &location.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &location.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				GetScene()->GetCamera()->SetLocation(location);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("m10002","Rotation"))
			{
				FVector& rotation = GetScene()->GetCamera()->GetRotation();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &rotation.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &rotation.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &rotation.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				//GetScene()->GetCamera()->SetRotation(rotation);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("m10003", "Axis"))
			{
				float pitch = GetScene()->GetCamera()->GetPitch();
				float yaw = GetScene()->GetCamera()->GetYaw();
				float roll = GetScene()->GetCamera()->GetRoll();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("Pitch", ImGuiDataType_Float, &pitch, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Yaw", ImGuiDataType_Float, &yaw, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Roll", ImGuiDataType_Float, &roll, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();

				//GetScene()->GetCamera()->SetPitch(pitch);
				//GetScene()->GetCamera()->SetYaw(yaw);
				//GetScene()->GetCamera()->SetRoll(roll);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("m10004", "Settings"))
			{
				FVector& rotation = GetScene()->GetCamera()->GetRotation();
				ACamera* camera = GetScene()->GetCamera();
				float fov = camera->GetFieldOfView();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("FOV", ImGuiDataType_Float, &fov, 0.05f, &zero, &maxFov, "%f"); ImGui::SameLine();
				ImGui::PopItemWidth();
				GetScene()->GetCamera()->SetFieldOfView(fov);
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}

	{ //Floor
		UStaticMesh* Floor = GetScene()->Floor;

		ImGui::Begin("Floor");
		{
			if (ImGui::TreeNode("m0004", "Position"))
			{
				FVector location = Floor->GetLocation();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &location.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &location.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &location.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				Floor->SetLocation(location);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("m0004B", "Origin"))
			{
				FVector location = Floor->GetOrigin();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &location.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &location.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &location.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				Floor->SetOrigin(location);
				ImGui::TreePop();
			}
		}
		{
			if (ImGui::TreeNode("m00005", "Rotation"))
			{
				FVector rotation = Floor->GetRotation();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &rotation.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &rotation.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &rotation.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				Floor->SetRotation(rotation);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("m00006", "Scale"))
			{
				FVector scale = Floor->GetScale();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &scale.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &scale.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &scale.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				Floor->SetScale(scale);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("m00007", "Bounds"))
			{
				FVector scale = Floor->GetBoundBox();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &scale.x, 0.05f, &minBoundBox, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &scale.y, 0.05f, &minBoundBox, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &scale.z, 0.05f, &minBoundBox, &max, "%f");
				ImGui::PopItemWidth();
				Floor->SetBoundBox(scale);
				ImGui::TreePop();
			}
		}

		

		{
			//if (ImGui::TreeNode("m00003", "Settings"))
			//{
			//	FVector& rotation = Floor->GetRotation();
			//	ACamera* camera = Floor;
			//	float fov = camera->GetFieldOfView();
			//	ImGui::PushItemWidth(80);
			//	ImGui::DragScalar("FOV", ImGuiDataType_Float, &fov, 0.05f, &zero, &maxFov, "%f"); ImGui::SameLine();
			//	ImGui::PopItemWidth();
			//	Floor->SetFieldOfView(fov);
			//	ImGui::TreePop();
			//}
		}
		ImGui::End();
	}

	{//Pawn
		APawn* Pawn = GetScene()->Pawn;
		ImGui::Begin("Pawn");
		{
			if (ImGui::TreeNode("m0008", "Position"))
			{
				FVector location = Pawn->GetLocation();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &location.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &location.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &location.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				Pawn->SetLocation(location);
				ImGui::TreePop();
			}
			if (ImGui::TreeNode("m0009", "Origin"))
			{
				FVector location = Pawn->GetMesh()->GetOrigin();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &location.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &location.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &location.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				Pawn->GetMesh()->SetOrigin(location);
				ImGui::TreePop();
			}

			if (ImGui::TreeNode("m0010", "Capsule Position"))
			{
				FVector location = Pawn->GetCapsuleLocation();
				ImGui::PushItemWidth(80);
				ImGui::DragScalar("X", ImGuiDataType_Float, &location.x, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Y", ImGuiDataType_Float, &location.y, 0.05f, &min, &max, "%f"); ImGui::SameLine();
				ImGui::DragScalar("Z", ImGuiDataType_Float, &location.z, 0.05f, &min, &max, "%f");
				ImGui::PopItemWidth();
				Pawn->SetLocation(location);
				ImGui::TreePop();
			}
		}
		ImGui::End();
	}
	ImGui::End();

	//static bool show = false;
	//ImGui::ShowDemoWindow(&show);
	ImGui::Render();
	glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
	//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	//glClear(GL_COLOR_BUFFER_BIT);


	

	//ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//OnDrawSceneEvent.Broadcast(deltaTime);

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	//glEnable(GL_DEPTH_TEST);
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
}

void UEditorUI::Destroy()
{
	Super::Destroy();

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void UEditorUI::OnMouseButtonEvent(uint32 keyCode, EKeyHandler keyHandler)
{
	ImGuiIO& io = ImGui::GetIO();


	switch (keyHandler)
	{
	case KEY_NONE:
		break;
	case KEY_PRESSED:
		io.MouseDown[keyCode - 1] = true;
		break;
	case KEY_RELEASED:
		io.MouseDown[keyCode - 1] = false;
		break;
	default:
		break;
	}
}

void UEditorUI::OnMouseWheelEvent(uint32 xOffset, uint32 yOffset)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += xOffset;
	io.MouseWheel += yOffset;
}

void UEditorUI::OnMouseMovementEvent(uint32 xPos, uint32 yPos, uint32 xPosRel, uint32 yPosRel)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MousePos = ImVec2(xPos, yPos);
}

void UEditorUI::OnPollEventsEvent(SDL_Event* sEvent)
{
	ImGui_ImplSDL2_ProcessEvent(sEvent);
}
