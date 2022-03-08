#include "Engine.h"
#include "Actor.h"
#include "CameraComponent.h"
#include "CameraManager.h"

MEngine* GEngine = new MEngine();

void MEngine::ProcessEvents()
{
	CurrentEvents.clear();
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		CurrentEvents.push_back(event);

		// system input
		if ((SDL_QUIT == event.type)
			|| (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
		{
			bShouldStop = true;
		}
	}

	// pass input data
	for (AActor* InputActors : RegisteredForInputActors)
	{
		// TODO change SDL event to Magic events (mouse click with world location for click...)
		InputActors->InputReceived(CurrentEvents);
	}


}

void MEngine::CalculateTime()
{
	if (TicksCount > 1)
	{
		std::chrono::steady_clock::time_point Now = std::chrono::steady_clock::now();
		LastDeltaSeconds = std::chrono::duration<float>(Now - LastTimePoint).count();
		LastTimePoint = std::chrono::steady_clock::now();
		TotalGameTime += LastDeltaSeconds;

		//LOG(TotalGameTime);
	}
	else
	{
		LastTimePoint = std::chrono::steady_clock::now();
	}
}

MEngine::~MEngine()
{
	SDL_DestroyWindow(Window);
	SDL_Quit();

	delete World;
}

void MEngine::Init()
{
	SDL_DisplayMode Dm;
	SDL_GetCurrentDisplayMode(0, &Dm);
	auto Screen_Width = Dm.w;
	auto Screen_Height = Dm.h;

	SDL_Init(SDL_INIT_VIDEO);

	if (TTF_Init() == -1) {
		printf("TTF_Init: %s\n", TTF_GetError());
		exit(2);
	}

	Window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WindowParams.WindowWidth, WindowParams.WindowHeight, 0);
	//window = SDL_CreateWindow("Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Screen_Width, Screen_Height, SDL_WINDOW_FULLSCREEN_DESKTOP);

	Renderer = SDL_CreateRenderer(Window, -1, 0);

	SDL_SetRenderDrawBlendMode(Renderer, SDL_BLENDMODE_BLEND);

	World = new MWorld;

	// TODO start console thread
}

bool MEngine::ShouldStop()
{
	return bShouldStop;
}

void MEngine::Tick()
{
	TicksCount++;

	CalculateTime();

	ProcessEvents();

	if (LastDeltaSeconds > 0)
	{
		World->Tick(LastDeltaSeconds);
	}

	Render();
}

void MEngine::Render()
{
	MCameraComponent* ActiveCamera = MCameraManager::GetActiveCamera();
	if (ActiveCamera)
	{
		ActiveCamera->Render(Renderer);
	}
}

void MEngine::RegisterActorForTick(AActor* Actor)
{
	World->RegisterActorForTick(Actor);
}

void MEngine::RegisterActorForInput(AActor* Actor)
{
	RegisteredForInputActors.push_back(Actor);
}