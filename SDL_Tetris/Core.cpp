#include "Core.h"
#include <iostream>

#include "Sprite.h"
#include "TetrisMap.h"

void Core::init() {

    SDL_Joystick* testJoy = SDL_JoystickOpen(0);

    SDL_Init(SDL_INIT_EVERYTHING);
    this->window = SDL_CreateWindow("SDL Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 80 * globalScale.x, 160 * globalScale.y, 0);
    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

    //Test part
    TetrisMap tetrisMap = TetrisMap(this);
    BlockController blockController = BlockController(this, &tetrisMap);
    //

    while (event->type != SDL_QUIT) {
        while (SDL_PollEvent(event)) {
            if (SDL_KEYDOWN) {
                checkInput(*event);
            }
        }

        SDL_RenderClear(renderer);

        //Test part

        blockController.update();

        tetrisMap.render();
        blockController.render();
        //

        SDL_RenderPresent(renderer);
        SDL_Delay(50);
        passedTime++;
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Core::checkInput(SDL_Event& event) {

    inputLeft = inputRight = inputUp = inputDown = inputPrimary = false;
    const Uint8* keystates = SDL_GetKeyboardState(NULL);

    if (keystates[SDL_SCANCODE_W]) {
        inputUp = true;
    }

    if (keystates[SDL_SCANCODE_S]) {
        inputDown = true;
    }

    if (keystates[SDL_SCANCODE_A]) {
        inputLeft = true;
    }

    if (keystates[SDL_SCANCODE_D]) {
        inputRight = true;
    }

    if (keystates[SDL_SCANCODE_SPACE]) {
        inputPrimary = true;
    }
}