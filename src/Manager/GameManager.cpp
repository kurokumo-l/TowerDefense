#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"
#include <cassert>
#include "GameManager.hpp"

GameManager::GameManager(Token token)
{
	int state = 0;
	state = SDL_Init(SDL_INIT_EVERYTHING);
	assert(!state);
	state = TTF_Init();
	assert(!state);
	state = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	assert(state);
	state = Mix_Init(MIX_INIT_MP3);
	assert(state);

	Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, AUDIO_CHUNK_SIZE);

	m_Window = SDL_CreateWindow(
		"村庄保卫战！",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		DEFAULT_WINDOW_WIDTH,
		DEFAULT_WINDOW_HEIGHT,
		SDL_WINDOW_SHOWN);
	assert(m_Window);

	m_Renderer = SDL_CreateRenderer(
		m_Window,
		-1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE);
	assert(m_Renderer);
}

GameManager::~GameManager()
{
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
}

int GameManager::Run(int argc, char** argv)
{
	const Uint64 counterFrequency = SDL_GetPerformanceFrequency();
	Uint64		 lastCounter = SDL_GetPerformanceCounter();

	while (!m_IsQuit)
	{
		while (SDL_PollEvent(&m_Event))
		{
			HandleInput();
		}

		Uint64 currentCounter = SDL_GetPerformanceCounter();
		double delta = (double)(currentCounter - lastCounter) / (double)counterFrequency;
		lastCounter = currentCounter;
		if (delta < m_InterframeDelay)
		{
			SDL_Delay(Uint32(m_InterframeDelay * 1000 - delta * 1000));
		}

		Update(delta);

		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer);
		Render();
		SDL_RenderPresent(m_Renderer);
	}
	return 0;
}

void GameManager::HandleInput()
{
	if (m_Event.type == SDL_QUIT)
		m_IsQuit = true;
}

void GameManager::Update(double delta)
{
}

void GameManager::Render()
{
}
