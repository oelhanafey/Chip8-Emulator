#include "SDL2/SDL.h"
#ifndef SCREEN
#define SCREEN
class Screen {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int pixels[2048];

    public:
    //Initiate the screen
    void initScreen();
    //Draw the pixels in gfx to the screen
    void drawScreen(uint8_t gfx[64*32]);
};
#endif
