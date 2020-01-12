#include "chip8.h"
//temp for debug
#include <iostream>

void chip8::initialize() {
  //For debug
  std::cerr << "chip8::initialize() run" << std::endl;

  pc = 0x200;
  opcode = 0;
  I = 0;
  sp = 0;
  soundTimer = 0;
  delayTimer = 0;
  drawFlag = false;

  //Clear display
  for(int i=0; i<64;i++) {
    for(int j=0; j<32; j++) {
      gfx[i][j] = 0;
    }
  }

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

  key = new Keyboard();

  //Load fontset
  uint8_t chip8_fontset[80] =
  {
    0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
    0x20, 0x60, 0x20, 0x20, 0x70, // 1
    0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
    0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
    0x90, 0x90, 0xF0, 0x10, 0x10, // 4
    0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
    0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
    0xF0, 0x10, 0x20, 0x40, 0x40, // 7
    0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
    0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
    0xF0, 0x90, 0xF0, 0x90, 0x90, // A
    0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
    0xF0, 0x80, 0x80, 0x80, 0xF0, // C
    0xE0, 0x90, 0x90, 0x90, 0xE0, // D
    0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
    0xF0, 0x80, 0xF0, 0x80, 0x80  // F
  };

  for(int i=0; i<80; i++) {
    memory[i] = chip8_fontset[i];
  }

}

void chip8::destroy() {
  free(key);
}

void chip8::cycle() {
  std::cerr << "chip8::cycle() run" << std::endl;
  //fetch opcode
  opcode = (memory[pc] << 8) | memory[pc + 1];
  //decode opcode
  opcodeHandler();

  //execute opcode

  //update timers

}

void chip8::opcodeHandler() {
  int x,y,nnn,kk,n;
  switch(opcode & 0xF000) {
    case(0x0000):
      switch(opcode & 0x000F) {
        case(0x0000):
          //00E0 - Clear the display
          for(int j=0;j<64;j++) {
            for(int k=0;k<32;k++) {
              gfx[j][k]= 0;
            }
          }
          pc += 2;
          drawFlag = true;

          break;
        case(0x000E):
          //00EE - Return from a subroutine
          sp--;
          pc = stack[sp];
          break;
      }

      break;
    case(0x1000):
      //1NNN - Jump to location NNN
      nnn = opcode & 0x0FFF;
      pc = nnn;
      break;
    case(0x2000):
      //2NNN - Call subroutine at NNN
      nnn = opcode & 0x0FFF;
      stack[sp] = pc;
      sp++;
      pc = nnn;
      break;
    case(0x3000):
      //3XKK - Skip next instruction if VX = kk
      x = (opcode & 0x0F00) >> 8;
      kk = (opcode & 0x00FF);

      if(V[x] == kk) {
        pc += 2;
      }

      pc += 2;
      break;
    case(0x4000):
      //4XKK - Skip next instruction if VX != kk
      x = (opcode & 0x0F00) >> 8;
      kk = (opcode & 0x00FF);

      if(V[x] != kk) {
        pc += 2;
      }
      pc += 2;
      break;
    case(0x5000):
      //5XY0 - Skip next instruction if VX = VY
      x = (opcode & 0x0F00) >> 8;
      y = (opcode & 0x00F0) >> 4;
      pc += 2;
      if(V[x] == V[y]) {
        pc += 2;
      }

      break;
    case(0x6000):
      //6XKK - Set VX = kk
      x = (opcode & 0x0F00) >> 8;
      kk = (opcode & 0x00FF);

      V[x] = kk;

      pc += 2;


      break;

    case(0x7000):
      //7XKK - Set VX = VX + kk
      x = (opcode & 0x0F00) >> 8;
      kk = (opcode & 0x00FF);

      V[x] = V[x] + kk;

      pc += 2;
      break;
    case(0x8000):
      switch(opcode & 0x000F) {
        case(0x0000):
          //8XY0 - Set VX = VY
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;
          V[x] = V[y];

          pc += 2;
          break;
        case(0x0001):
          //8XY1 - Set VX = VY OR VY
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;
          V[x] = V[x] | V[y];

          pc += 2;
          break;
        case(0x0002):
          //8XY2 - Set VX = VX AND VY
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;
          V[x] = V[x] & V[y];

          pc += 2;
          break;
        case(0x0003):
          //8XY3 - Set VX = VX XOR VY
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;
          V[x] = V[x] ^ V[y];

          pc += 2;
          break;
        case(0x0004):
          //8XY4 - Set VX = VX + VY, Set VF = carry
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;
          n = V[x] + V[y];

          //Check overflow
          if(n > 0xFF) {
            V[0xF] = 1;
          }
          else {
            V[0xF] = 0;
          }
          V[x] = V[x] + V[y];

          pc += 2;
          break;
        case(0x0005):
          //8XY5 - Set VX = VX - VY, Set VF = NOT borrow
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;

          if(V[x] >= V[y]) {
            V[0xF] = 1;
          }
          //If overflow
          else {
            V[0xF] = 0;
          }
          V[x] = V[x] - V[y];
          pc += 2;
          break;
        case(0x0006):
          //8XY6 - Set VX = VX SHR 1
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;
          //If least significant digit = 1
          if((V[x] & 0x01) == 1) {
            V[0xF] = 1;
          }
          else {
            V[0xF] = 0;
          }
          V[x] >>= 1;

          pc += 2;
          break;
        case(0x0007):
          //8XY7 - Set VX = VY - VX, set VF = NOT borrow
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;

          if(V[y] >= V[x]) {
            V[0xF] = 1;
          }
          else {
            V[0xF] = 0;
          }
          V[x] = V[y] - V[x];

          pc += 2;
          break;
        case(0x000E):
          //8XYE - Set VX = VX SHL 1
          x = (opcode & 0x0F00) >> 8;
          y = (opcode & 0x00F0) >> 4;

          if(((V[x] & 0x80) != 0)) {
            V[0xF] = 1;
          }
          else {
            V[0xF] = 0;
          }
          V[x] <<= 1;

          pc += 2;
          break;
      }

      break;

    case(0x9000):
      //9XY0 - Skip next instruction if VX != VY
      x = (opcode & 0x0F00) >> 8;
      y = (opcode & 0x00F0) >> 4;

      if(V[x] != V[y]) {
        pc += 2;
      }
      pc += 2;
      break;
    case(0xA000):
      //ANNN - set value of register I to ANNN
      I = opcode & 0x0FFF;

      pc += 2;
      break;
    case(0xB000):
      //BNNN - jump to location NNN + V0
      pc = V[0] + (opcode & 0x0FFF);
      break;
    case(0xC000):
      //CXKK - set Vx = random byte AND kk
      x = (opcode & 0x0F00) >> 8;
      kk = (opcode & 0x00FF);

      V[x] = (rand() % 256) & kk;

      pc += 2;
      break;
    case(0xD000):
      //DXYN - Display n-byte sprite starting at memory location I at (VX,VY), set VF = collision
      x = (opcode & 0x0F00) >> 8;
      y = (opcode & 0x00F0) >> 4;
      n = opcode & 0x000F;
      uint8_t sprite;

      V[0xF] = 0;
      //draw N rows
      for(int j=0; j<n; j++) {
        sprite = memory[I+j];
        for(int k=0; k<8; k++) {
          //check 1 bit at a time
          if((sprite & (0x80 >> k)) != 0) {
              if(gfx[y+j][x+k] == 1) {
                V[0xF] = 1;
              }
              gfx[y+j][x+k] ^= 1;
          }
        }
      }

      drawFlag = true;
      pc += 2;
      break;
    case(0xE000):
      switch(opcode & 0x00FF) {
        case(0x009E):
          //EX9E - Skip next instruction if key with value VX is pressed
          x = (opcode & 0x0F00) >> 8;
          if(key->isKeyPressed(x)) {
            pc += 2;
          }
          pc += 2;
          break;
        case(0x00A1):
          //EXA1 - Skip next instruction if key with value VX is not pressed
          x = (opcode & 0x0F00) >> 8;
          if(key->isKeyPressed(x)) {
            pc += 2;
          }
          pc += 2;
          break;
        }
      break;
    case(0xF000):
      switch(opcode & 0x00FF) {
        case(0x0007):
          //FX07 - Set VX = delay timers
          x = (opcode & 0x0F00) >> 8;
          V[x] = delayTimer;
          pc += 2;
          break;
        case(0x000A):
          //FX0A - Wait for key press, store value of key in VX
          x = (opcode & 0x0F00) >> 8;
          n=0;

          for(int i=0; i<16;i++) {
            if(key->isKeyPressed(i)) {
              V[x] = i;
              n=1;
            }
          }

          if(n == 0) {
            pc -= 2;
          }

          pc += 2;
          break;
        case(0x0015):
          //FX15 - Set delay timer = VX
          x = (opcode & 0x0F00) >> 8;
          delayTimer = V[x];

          pc += 2;
          break;
        case(0x0018):
          //FX18 - Set sound timer = VX
          x = (opcode & 0x0F00) >> 8;
          soundTimer = V[x];

          pc += 2;
          break;
        case(0x001E):
          //FX1E - Set I = I + VX
          x = (opcode & 0x0F00) >> 8;
          I = I + V[x];

          pc += 2;
          break;
        case(0x0029):
          //FX29 - Set I = location of sprite for digit VX
          x = (opcode & 0x0F00) >> 8;
          switch(x) {
            case(0):
              I = memory[0];
              break;
            case(1):
              I = memory[5];
            break;
            case(2):
              I = memory[10];
              break;
            case(3):
              I = memory[15];
              break;
            case(4):
              I = memory[20];
              break;
            case(5):
              I = memory[25];
              break;
            case(6):
              I = memory[30];
              break;
            case(7):
              I = memory[35];
              break;
            case(8):
              I = memory[40];
              break;
            case(9):
              I = memory[45];
              break;
            case(0xA):
              I = memory[50];
              break;
            case(0xB):
              I = memory[55];
              break;
            case(0xC):
              I = memory[60];
              break;
            case(0xD):
              I = memory[65];
              break;
            case(0xE):
              I = memory[70];
              break;
            case(0xF):
              I = memory[75];
              break;
          }

          pc += 2;

          break;
        case(0x0033):
          //FX33 - Store BCD representation of VX in memory locations I,I+1,I+2
          x = (opcode & 0x0F00) >> 8;
          memory[I] = V[x] / 100;
          memory[I+1] = (V[x] / 10) % 10;
          memory[I+2] = V[x] % 10;

          pc += 2;
          break;
        case(0x0055):
          //FX55 - Store registers V0 through VX in memory starting at location I
          x = (opcode & 0x0F00) >> 8;
          for(int j=0;j<=x;j++) {
            memory[I+j] = V[j];
          }


          pc += 2;
          break;
        case(0x0065):
          //FX65 - Read registers V0 - VX from memory starting at location I
          x = (opcode & 0x0F00) >> 8;
          for(int j=0;j<=x;j++) {
            V[j] = memory[I+j];
          }

          pc += 2;
          break;


      }

      break;

  }
}


void chip8::load() {

}
