#include "chip8.h"
//temp for debug
#include <iostream>

void chip8::initialize() {
  //For debug
  std::cout << "chip8::initialize() run" << std::endl;

  pc = 0x200;
  opcode = 0;
  I = 0;
  sp = 0;

  //Clear display

  //Clear stack
  for(int i=0; i<16; i++) {
    stack[i] = 0;
  }

  //initialize all memory to 0
  for(int i=0; i<4096; i++) {
    memory[i] = 0x0;
  }
  //initialize all registers to 0
  for(int i=0; i<16; i++) {
    V[i] = 0x0;
  }

  //Load fontset

}

void chip8::cycle() {
  //fetch opcode
  //opcode = memory[pc] << 8 | memory[pc+1];
  //decode opcode

  //execute opcode

  //update timers

}
