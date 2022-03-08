#include "Engine.h"
#include "Actor.h"
#include "Character.h"
#include "PlayerCameraActor.h"
#include "Rock.h"
#include "SimpleNavMesh.h"

int main(int argc, char* argv[])
{
	GEngine->Init();

	ARock* Rock1 = (ARock*)SpawnActor<ARock>(GEngine->GetCurrentWorld());
	Rock1->SetLocation({ 226.f, 245.f });


	ACharacter* Char1 = (ACharacter*)SpawnActor<ACharacter>(GEngine->GetCurrentWorld());
	Char1->SetLocation({ 125.f, 276.f });

	ACharacter* Char2 = (ACharacter*)SpawnActor<ACharacter>(GEngine->GetCurrentWorld());
	Char2->SetLocation({ 525.f, 406.f });

	ASimpleNavMesh* NavMesh = (ASimpleNavMesh*)SpawnActor<ASimpleNavMesh>(GEngine->GetCurrentWorld(), {0.f, 0.f});
	NavMesh->RegisterForInput();

	APlayerCameraActor* CameraActor = (APlayerCameraActor*)SpawnActor<APlayerCameraActor>(GEngine->GetCurrentWorld());
	CameraActor->SetActiveCamera();
	CameraActor->SetBackgroundColor({ 100, 180, 100, 255 });
	CameraActor->RegisterForInput();

	NavMesh->BuildPath(Char1->GetLocation(), Char2->GetLocation());

	while(!GEngine->ShouldStop())
	{
		GEngine->Tick();
	}

	delete GEngine;

	return 0;
}
