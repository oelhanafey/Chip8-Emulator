#include <iostream>
#include <chrono>
#include <thread>
#include "stdint.h"
#include "SDL2/SDL.h"
#include "chip8.h"

using namespace std;


int main(int argc, char **argv) {

    // If no ROM given
    if (argc != 2) {
        cout << "Usage: chip8 <ROM file>" << endl;
        return 1;
    }

    //Initialize Chip8 and screen
    Chip8 chip8;
    chip8.initialize();
    chip8.getScreen()->initScreen();


    chip8.load(argv[1]);

    while (!chip8.getKeyboard()->isExit()) {
        chip8.cycle();
        chip8.getKeyboard()->keyPressHandler();

        //if drawflag is set, redraw screen
        if (chip8.getDrawFlag()) {
            chip8.setDrawFlag(false);
            chip8.getScreen()->drawScreen(chip8.gfx);
        }

        //Slow down cpu
        std::this_thread::sleep_for(std::chrono::microseconds(1200));

    }

    chip8.destroy();
}
