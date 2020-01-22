#include "keyboard.h"
#include "SDL2/SDL.h"
#include <iostream>

void Keyboard::resetKeys() {
  for(int i=0;i<16;i++) {
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

bool Keyboard::isExit() {
  if(exit) return true;
  return false;
}

void Keyboard::keyPressHandler() {
  SDL_Event event;
  while(SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
      exit = true;
      break;
      case(SDL_KEYDOWN):
      switch(event.key.keysym.sym) {
        case SDLK_1:
        keys[1] = true;
        break;
        case SDLK_2:
        keys[2] = true;
        break;
        case SDLK_3:
        keys[3] = true;
        break;
        case SDLK_4:
        keys[0xC] = true;
        break;
        case SDLK_q:
        keys[4] = true;
        break;
        case SDLK_w:
        keys[5] = true;
        break;
        case SDLK_e:
        keys[6] = true;
        break;
        case SDLK_r:
        keys[0xD] = true;
        break;
        case SDLK_a:
        keys[7] = true;
        break;
        case SDLK_s:
        keys[8] = true;
        break;
        case SDLK_d:
        keys[9] = true;
        break;
        case SDLK_f:
        keys[0xE] = true;
        break;
        case SDLK_z:
        keys[0xA] = true;
        break;
        case SDLK_x:
        keys[0] = true;
        break;
        case SDLK_c:
        keys[0xB] = true;
        break;
        case SDLK_v:
        keys[0xF] = true;
        break;
      }
      break;
      case(SDL_KEYUP):
      switch(event.key.keysym.sym) {
        case SDLK_1:
        keys[1] = false;
        break;
        case SDLK_2:
        keys[2] = false;
        break;
        case SDLK_3:
        keys[3] = false;
        break;
        case SDLK_4:
        keys[0xC] = false;
        break;
        case SDLK_q:
        keys[4] = false;
        break;
        case SDLK_w:
        keys[5] = false;
        break;
        case SDLK_e:
        keys[6] = false;
        break;
        case SDLK_r:
        keys[0xD] = false;
        break;
        case SDLK_a:
        keys[7] = false;
        break;
        case SDLK_s:
        keys[8] = false;
        break;
        case SDLK_d:
        keys[9] = false;
        break;
        case SDLK_f:
        keys[0xE] = false;
        break;
        case SDLK_z:
        keys[0xA] = false;
        break;
        case SDLK_x:
        keys[0] = false;
        break;
        case SDLK_c:
        keys[0xB] = false;
        break;
        case SDLK_v:
        keys[0xF] = false;
        break;
      }
      break;

      }
    }
  }
