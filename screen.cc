#include "screen.h"


void Screen::initScreen() {
  //init pixels
  for(int i=0;i<2048;i++) {
    pixels[i] = 0;
  }

  int w = 1024;                   // Window width
  int h = 512;                    // Window height

  window = NULL;

  // Initialize SDL
  if ( SDL_Init(SDL_INIT_EVERYTHING) < 0 ) {
      printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
      exit(1);
  }
  // Create window
  window = SDL_CreateWindow(
          "CHIP-8 Emulator",
          SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
          w, h, SDL_WINDOW_SHOWN
  );
  if (window == NULL){
      printf( "Window could not be created! SDL_Error: %s\n",
              SDL_GetError() );
      exit(2);
  }

  // Create renderer
  renderer = SDL_CreateRenderer(window, -1, 0);
  SDL_RenderSetLogicalSize(renderer, w, h);

  // Create texture that stores frame buffer
  texture = SDL_CreateTexture(renderer,
          SDL_PIXELFORMAT_ARGB8888,
          SDL_TEXTUREACCESS_STREAMING,
          64, 32);


}


void Screen::drawScreen(uint8_t gfx[]) {
  // Store pixels in temporary buffer
  for (int i = 0; i < 2048; ++i) {
      uint8_t pixel = gfx[i];
      pixels[i] = (0x00FFFFFF * pixel) | 0xFF000000;
  }
  // Update SDL texture
  SDL_UpdateTexture(texture, NULL, pixels, 64 * sizeof(int));
  // Clear screen and render
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, texture, NULL, NULL);
  SDL_RenderPresent(renderer);
}
