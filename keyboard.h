#ifndef KEY
#define KEY

class Keyboard {
private:
  bool keys[16];
  bool exit = false;

public:

  Keyboard();

  //Return true if 'key is currently pressed
  bool isKeyPressed(int key);

  //Return exit parameter
  bool isExit();

  //Decode key press input and update keys array
  void keyPressHandler();

private:
  //Set all keys in array to false
  void resetKeys();

};

#endif
