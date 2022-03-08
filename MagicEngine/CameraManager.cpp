#include "CameraManager.h"
#include "CameraComponent.h"

MCameraManager* MCameraManager::SingleCameraManager = nullptr;

void MCameraManager::SetActiveCamera(MCameraComponent* NewActiveCamera)
{
	GetCameraManager()->ActiveCamera = NewActiveCamera;
}

MCameraComponent* MCameraManager::GetActiveCamera()
{
	return GetCameraManager()->ActiveCamera;
}

MCameraManager* MCameraManager::GetCameraManager()
{
	if (SingleCameraManager == nullptr)
	{
		SingleCameraManager = new MCameraManager();
	}
	return SingleCameraManager;
}
