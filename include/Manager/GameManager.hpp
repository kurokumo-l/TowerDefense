#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "SDL.h"
#include "Singleton.hpp"

constexpr int DEFAULT_WINDOW_WIDTH = 1280;
constexpr int DEFAULT_WINDOW_HEIGHT = 720;

constexpr int DEFAULT_FPS = 60;

constexpr int AUDIO_FREQUENCY = 44100;
constexpr int AUDIO_CHUNK_SIZE = 2048;

class GameManager : public Singleton<GameManager>
{
public:
	GameManager(Token token);
	GameManager(const GameManager&) = delete;
	GameManager(GameManager&&) = delete;
	GameManager& operator=(const GameManager&) = delete;
	GameManager& operator=(GameManager&&) = delete;
	~GameManager() override;

	int	 Run(int argc, char** argv);
	void HandleInput();
	void Update(double delta);
	void Render();

private:
	int			  m_FPS = DEFAULT_FPS;
	double		  m_InterframeDelay = 1.0 / m_FPS;
	bool		  m_IsQuit = false;
	SDL_Event	  m_Event{};
	SDL_Window*	  m_Window = nullptr;
	SDL_Renderer* m_Renderer = nullptr;
};

#endif