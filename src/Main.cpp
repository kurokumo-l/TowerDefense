#include <cJSON.h>
#include "GameManager.hpp"
#include "SDL.h"

int main(int argc, char** argv)
{
	return GameManager::Instance().Run(argc, argv);
}