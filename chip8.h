#include <cstdint>
#include "keyboard.h"

class chip8 {
  uint16_t opcode;
  uint8_t memory[4096];
  //Registers
  //V[0] = V0 -> V[16] = VF
  uint8_t V[16];
  uint16_t I;
  uint16_t pc;
  uint8_t gfx[64][32];
  uint8_t delayTimer;
  uint8_t soundTimer;
  uint16_t stack[16];
  uint8_t sp;

  Keyboard* key;
  bool drawFlag;


  public:
    //initialize registers and memory
    void initialize();

    void cycle();

    void load();

    void opcodeHandler();

    void destroy();
};
