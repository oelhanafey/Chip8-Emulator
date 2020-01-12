#include <cstdint>
#include <vector>
#include <fstream>
#include "keyboard.h"
#include "screen.h"

class Chip8 {
  public:
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
  bool drawFlag;

  Keyboard* key;
  Screen* screen;


  public:
    //initialize registers and memory
    void initialize();

    //Compute one cpu cycle
    void cycle();

    //Load specified program into memory
    void load(const char* prog);

    //Decode and execute current opcode
    void opcodeHandler();

    //Free used memory
    void destroy();

  private:
    std::vector<uint8_t> readFile(const char* prog);
};
