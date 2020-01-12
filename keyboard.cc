#include "keyboard.h"
#include "SDL2/SDL.h"
#include <iostream>

void Keyboard::resetKeys() {
  int size = sizeof(keys)/sizeof(keys[0]);
  for(int i=0;i<size;i++) {
    keys[i] = false;
  }
}

Keyboard::Keyboard() {
  resetKeys();
}

bool Keyboard::isKeyPressed(int key) {
  if(keys[key]) {
    return true;
  }
  return false;
}

void Keyboard::keyPressHandler() {
  resetKeys();
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
      exit = true;
      break;
      case(SDL_KEYDOWN):
      switch(event.key.keysym.sym) {
        case SDLK_1:
        keys[0] = true;
        break;
        case SDLK_2:
        keys[1] = true;
        break;
        case SDLK_3:
        keys[2] = true;
        break;
        case SDLK_4:
        keys[3] = true;
        break;
        case SDLK_q:
        std::cout << "TEST";
        keys[4] = true;
        break;
        case SDLK_w:
        keys[5] = true;
        break;
        case SDLK_e:
        keys[6] = true;
        break;
        case SDLK_r:
        keys[7] = true;
        break;
        case SDLK_a:
        keys[8] = true;
        break;
        case SDLK_s:
        keys[9] = true;
        break;
        case SDLK_d:
        keys[10] = true;
        break;
        case SDLK_f:
        keys[11] = true;
        break;
        case SDLK_z:
        keys[12] = true;
        break;
        case SDLK_x:
        keys[13] = true;
        break;
        case SDLK_c:
        keys[14] = true;
        break;
        case SDLK_v:
        keys[15] = true;
        break;
      }
    }
  }
}
