#ifndef CHIP
#define CHIP

#include <cstdint>
#include <vector>
#include <fstream>
#include "keyboard.h"
#include "screen.h"

class Chip8 {
private:
  uint16_t opcode;
  uint8_t memory[4096];
  //Registers
  //V[0] = V0 -> V[16] = VF
  uint8_t V[16];
  //Index pointer
  uint16_t I;
  uint16_t pc;

  uint8_t delayTimer;
  uint8_t soundTimer;
  uint16_t stack[16];
  //stack pointer
  uint8_t sp;

  Keyboard*  key;
  Screen* screen;
  //Set to true when cpu should redraw screen
  bool drawFlag;

public:

    //Graphics
    uint8_t gfx[64 * 32];

    //initialize registers and memory
    void initialize();

    //Compute one cpu cycle
    void cycle();

    //Load specified program into memory
    void load(char* prog);

    //Decode and execute current opcode
    void opcodeHandler();

    //Free used memory
    void destroy();

    //return key
    Keyboard* getKeyboard();

    //return screen
    Screen* getScreen();

    //return drawFlag
    bool getDrawFlag();

    //set drawFlag to set
    void setDrawFlag(bool set);


  private:
    //wrapped function for load
    std::vector<uint8_t> readFile(char* prog);
};

#endif
