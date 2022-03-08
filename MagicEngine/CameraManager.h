#pragma once
#include "PCH.h"

class MCameraComponent;

class MCameraManager
{
	MCameraComponent* ActiveCamera = nullptr;

	static MCameraManager* SingleCameraManager;

public:
	static void SetActiveCamera(MCameraComponent* NewActiveCamera);

	static MCameraComponent* GetActiveCamera();

	static MCameraManager* GetCameraManager();
};

