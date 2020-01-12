#include "screen.h"


void Screen::initScreen() {
    //Create window
    window = NULL;
    window = SDL_CreateWindow
    (
        "Chip-8 Emulator", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        700,
        480,
        SDL_WINDOW_SHOWN
    );

    //Render screen
    renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);

    //Set background colour to black
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    
    // Clear winow
    clearScreen();
}

void Screen::clearScreen() {
    SDL_RenderClear(renderer );
}

void Screen::drawPixel(int x, int y) {
    //Create rect
    SDL_Rect r;
    r.x = x * 10;
    r.y = y * 10;
    r.w = 10;
    r.h = 10;

    // Set colour to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255 );

    // Render rect
    SDL_RenderFillRect(renderer, &r );

    // Render the rect to the screen
    SDL_RenderPresent(renderer);
}
