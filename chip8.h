#include <cstdint>

class chip8 {
  uint16_t opcode;
  uint8_t memory[4096];
  //Registers
  //V[0] = V0 -> V[16] = VF
  uint8_t V[16];
  uint16_t I;
  uint16_t pc;
  uint8_t gfx[64][32];
  uint8_t delay_timer;
  uint8_t sound_timer;
  uint16_t stack[16];
  uint8_t sp;


  public:
    //initialize registers and memory
    void initialize();

    void cycle();

    void load();
};
