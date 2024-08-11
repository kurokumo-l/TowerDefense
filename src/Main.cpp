#include <climits>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

#include <Windows.h>

#include <cJSON.h>
#include "SDL.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL2_gfxPrimitives.h"

constexpr int AUDIO_FREQUENCY = 44100;
constexpr int AUDIO_CHUNK_SIZE = 2048;

constexpr int WINDOW_W = 1280;
constexpr int WINDOW_H = 720;

constexpr int TTF_POINT_SIZE = 32;
constexpr int MIX_FADE_DURATION = 1500;

constexpr int FPS = 60;

void TestSDL()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	TTF_Init();
	Mix_OpenAudio(AUDIO_FREQUENCY, MIX_DEFAULT_FORMAT, 2, AUDIO_CHUNK_SIZE);

	SDL_Window*	  window = SDL_CreateWindow("TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_W, WINDOW_H, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_Surface* surfaceImage = IMG_Load("res/image/home.png");
	SDL_Texture* textureImage = SDL_CreateTextureFromSurface(renderer, surfaceImage);

	TTF_Font*	 font = TTF_OpenFont("res/font/ipix.ttf", TTF_POINT_SIZE);
	SDL_Color	 fontCorlor = { UCHAR_MAX, UCHAR_MAX, UCHAR_MAX, UCHAR_MAX };
	SDL_Surface* surfaceText = TTF_RenderUTF8_Blended(font, "你好，世界", fontCorlor);
	SDL_Texture* textrueText = SDL_CreateTextureFromSurface(renderer, surfaceText);

	Mix_Music* music = Mix_LoadMUS("res/audio/music_bgm.mp3");
	Mix_FadeInMusic(music, -1, MIX_FADE_DURATION);

	bool	  isQuit = false;
	SDL_Event event;

	uint64_t lastCounter = SDL_GetPerformanceCounter();
	uint64_t counterFrequency = SDL_GetPerformanceFrequency();

	SDL_Point cursorPoint = { 0, 0 };
	SDL_Rect  rectImage = { 0, 0, surfaceImage->w, surfaceImage->h };
	SDL_Rect  rectText = { 0, 0, surfaceText->w, surfaceText->h };

	while (!isQuit)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				isQuit = true;
			}
			else if (event.type == SDL_MOUSEMOTION)
			{
				cursorPoint.x = event.motion.x;
				cursorPoint.y = event.motion.y;
			}
		}

		rectImage.x = cursorPoint.x;
		rectImage.y = cursorPoint.y;
		rectText.x = cursorPoint.x;
		rectText.y = cursorPoint.y;

		uint64_t currentCounter = SDL_GetPerformanceCounter();
		double	 delta = double(currentCounter - lastCounter) / (double)counterFrequency;
		lastCounter = currentCounter;

		if (delta * 1000 < 1000.0 / 60)
		{
			SDL_Delay((uint32_t)(1000.0 / 60 - delta * 1000));
		}

		// render
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, textureImage, nullptr, &rectImage);
		filledCircleRGBA(renderer, cursorPoint.x, cursorPoint.y, 50, 255, 0, 0, 255);
		SDL_RenderCopy(renderer, textrueText, nullptr, &rectText);
		SDL_RenderPresent(renderer);
	}
}

void TestJSON()
{
	SetConsoleOutputCP(CP_UTF8);
	std::ifstream file("res/data/test.json");
	if (!file.good())
	{
		std::cout << "文件无法打开\n";
		return;
	}

	std::stringstream sfs;
	sfs << file.rdbuf();
	file.close();

	cJSON* jsonRoot = cJSON_Parse(sfs.str().c_str());

	cJSON* jsonName = cJSON_GetObjectItem(jsonRoot, "name");
	cJSON* jsonAge = cJSON_GetObjectItem(jsonRoot, "age");
	cJSON* jsonPets = cJSON_GetObjectItem(jsonRoot, "pets");

	std::cout << jsonName->string << ": " << jsonName->valuestring << '\n';
	std::cout << jsonAge->string << ": " << jsonAge->valueint << '\n';
	std::cout << jsonPets->string << ": ";

	cJSON* jsonItem = nullptr;
	cJSON_ArrayForEach(jsonItem, jsonPets)
	{
		std::cout << jsonItem->valuestring << ", ";
	}
	std::cout << '\n';
}

void TestCSV()
{
	SetConsoleOutputCP(CP_UTF8);
	std::ifstream file("res/data/test.csv");
	if (!file.good())
	{
		std::cout << "文件无法打开\n";
		return;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::stringstream lineStream(line);
		std::string		  grid;
		while (std::getline(lineStream, grid, ','))
		{
			std::cout << grid << ' ';
		}
		std::cout << '\n';
	}
	file.close();
}

int main(int argc, char** argv)
{
	TestSDL();
	TestJSON();
    TestCSV();
	return 0;
}