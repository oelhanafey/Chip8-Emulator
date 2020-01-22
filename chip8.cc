#include "chip8.h"
//temp for debug
#include <iostream>

void Chip8::initialize() {
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
  for(int i=0; i<64*32;i++) {
    gfx[i] = 0;
  }


  //Clear stack
  for(int i=0; i<16; i++) {
    stack[i] = 0;
  }

  //initialize all memory to 0
  for(int i=0; i<4096; i++) {
    memory[i] = 0;
  }
  //initialize all registers to 0
  for(int i=0; i<16; i++) {
    V[i] = 0;
  }




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

  screen = new Screen();
  key = new Keyboard();


}

void Chip8::destroy() {
  free(key);
  free(screen);
}

Keyboard* Chip8::getKeyboard() {
  return key;
}

Screen* Chip8::getScreen() {
  return screen;
}

bool Chip8::getDrawFlag() {
  return drawFlag;
}

void Chip8::setDrawFlag(bool set) {
  drawFlag = set;
}

void Chip8::cycle() {
  //fetch opcode
  opcode = (memory[pc] << 8) | memory[pc + 1];
  //decode opcode
  opcodeHandler();

  //update timers
  delayTimer--;
  soundTimer--;


}

void Chip8::opcodeHandler() {
  int x,y,nnn,kk,n;
  switch(opcode & 0xF000) {
    case(0x0000):
      switch(opcode & 0x000F) {
        case(0x0000):
          //00E0 - Clear the display
          for(int j=0;j<2048;j++) {
            gfx[j] = 0;
          }
          pc += 2;
          drawFlag = true;

          break;
        case(0x000E):
          //00EE - Return from a subroutine
          sp--;
          pc = stack[sp];
          pc += 2;
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
          V[0xF] = V[x] & 0x1;
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
      x = V[(opcode & 0x0F00) >> 8];
			y = V[(opcode & 0x00F0) >> 4];
			n = opcode & 0x000F;
			unsigned short pixel;

			V[0xF] = 0;
			for (int yline = 0; yline < n; yline++)
			{
				pixel = memory[I + yline];
				for(int xline = 0; xline < 8; xline++)
				{
					if((pixel & (0x80 >> xline)) != 0)
					{
						if(gfx[(x + xline + ((y + yline) * 64))] == 1)
						{
							V[0xF] = 1;
						}
						gfx[x + xline + ((y + yline) * 64)] ^= 1;
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
          x = V[(opcode & 0x0F00) >> 8];
              if (key->isKeyPressed(x))
                  pc +=  4;
              else
                  pc += 2;
              break;

          // EXA1 - Skips the next instruction if the key stored
          // in VX isn't pressed.
          case 0x00A1:
          x = V[(opcode & 0x0F00) >> 8];
              if(!key->isKeyPressed(x))
                  pc +=  4;
              else
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
          {
              bool key_pressed = false;
              x = V[(opcode & 0x0F00) >> 8];
              for(int i = 0; i < 16; ++i)
              {
                  if(key->isKeyPressed(i))
                  {
                      V[x] = i;
                      key_pressed = true;
                  }
              }

              // If no key is pressed, return and try again.
              if(!key_pressed) {
                pc -= 2;
              }

              pc += 2;
          }
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
          n = I + V[x];
          if(n > 0xFFF) {
            V[0xF] = 1;
          }
          else {
            V[0xF] = 0;
          }
          I = I + V[x];

          pc += 2;
          break;
        case(0x0029):
          //FX29 - Set I = location of sprite for digit VX
          x = (opcode & 0x0F00) >> 8;
          I = V[x] * 5;

          pc += 2;

          break;
        case(0x0033):
          //FX33 - Store BCD representation of VX in memory locations I,I+1,I+2
          x = (opcode & 0x0F00) >> 8;
          memory[I] = V[x] / 100;
          memory[I+1] = (V[x] / 10) % 10;
          memory[I+2] =   V[x] % 10;

          pc += 2;
          break;
        case(0x0055):
          //FX55 - Store registers V0 through VX in memory starting at location I
          x = (opcode & 0x0F00) >> 8;
          for(int j=0;j<=x;j++) {
            memory[I+j] = V[j];
          }

          I += x + 1;
          pc += 2;
          break;
        case(0x0065):
          //FX65 - Read registers V0 - VX from memory starting at location I
          x = (opcode & 0x0F00) >> 8;
          for(int j=0;j<=x;j++) {
            V[j] = memory[I+j];
          }

          I += x + 1;
          pc += 2;
          break;


      }

      break;

  }
}


std::vector<uint8_t> Chip8::readFile(char* prog) {
    // open the file:
    std::streampos fileSize;
    std::ifstream file(prog, std::ios::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    std::vector<uint8_t> fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    return fileData;
}

void Chip8::load(char* prog) {
  std::vector<uint8_t> data = readFile(prog);

  for(int i=0; i<data.size(); i++) {
    memory[i + 0x200] = data.at(i);
  }

}
