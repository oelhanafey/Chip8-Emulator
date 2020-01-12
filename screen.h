#include "SDL2/SDL.h"
#ifndef SCREEN
#define SCREEN
class Screen {
    SDL_Window* window;
    SDL_Renderer* renderer;

    public:
    //Initiate the window and renderer
    void initScreen();

    //Clear the screen
    void clearScreen();

    //Draw a rectangle to represent specified pixel
    //Domain: x = 64 pixels, y = 32 pixels
    void drawPixel(int x,int y);

    void drawScreen(uint8_t gfx[64*32]);
};
#endif