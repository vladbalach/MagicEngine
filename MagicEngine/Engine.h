#pragma once

#include "PCH.h"
#include "World.h"

class AActor;

// TODO set this via config and parse in constructor
struct FWindowParams
{
	int32 WindowWidth = 800;
	int32 WindowHeight = 800;
};

class MEngine
{
	/** First tick == 1, not 0. 0 means engine has not started */
	int32 TicksCount = 0;

	float LastDeltaSeconds = 0.f;

	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;

	MWorld* World = nullptr;

	/** if true game will stop on next tick */
	bool bShouldStop = false;

	/** Total summ of all delta seconds from ticks */
	float TotalGameTime = 0.f;

	std::chrono::steady_clock::time_point LastTimePoint;

	std::vector<AActor*> RegisteredForInputActors;

	std::vector<SDL_Event> CurrentEvents;

	FWindowParams WindowParams;

	void ProcessEvents();

	/** Calculates all time variables such as delta seconds, total game time, etc. */
	void CalculateTime();

public:

	virtual ~MEngine();

	void Init();

	/** Returns true if engine should stop execution */
	bool ShouldStop();

	void Tick();

	void Render();

	void RegisterActorForTick(AActor* Actor);

	void RegisterActorForInput(AActor* Actor);

	MWorld* GetCurrentWorld() const { return World; }

	float GetTotalGameTime() const { return TotalGameTime; }

	inline SDL_Renderer* GetRenderer() const { return Renderer; }

};
