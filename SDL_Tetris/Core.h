#pragma once
#include "SDL.h"
#include "Vector2.h"

class Core {
public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Event* event = new SDL_Event;
	void checkInput(SDL_Event& event);
	Vector2 blockTileSize = Vector2(8, 8);

	Uint32 passedTime = 0;

	bool inputUp = false, inputDown = false, inputLeft = false, inputRight = false, inputPrimary = false;
	Vector2 globalScale = Vector2(4, 4);

	void init();
};