#include "SDL2/SDL.h"

class Screen {
    public:
    SDL_Window* window;
    SDL_Renderer* renderer;


    //Initiate the window and renderer
    void initScreen();

    //Clear the screen
    void clearScreen();

    //Draw a rectangle to represent specified pixel
    //Domain: x = 64 pixels, y = 32 pixels
    void drawPixel(int x,int y);
};