#include <iostream>
#include "chip8.h"
#include "screen.h"
#include "SDL2/SDL.h"

int main(void) {
  Chip8 cpu;
  cpu.initialize();

  //setup graphics
  cpu.display->initScreen();

  //load game into memory
  cpu.load("Pong.ch8");

  //loop
  while(!cpu.key->exit) {
    //Cycle cpu
    cpu.cycle();

    //If draw flag is set then draw screen
    if(cpu.drawFlag) {
      cpu.display->drawScreen(cpu.gfx);
      cpu.drawFlag = false;
    }

    //Check keys
    cpu.key->keyPressHandler();
  }


  return 0;
}
