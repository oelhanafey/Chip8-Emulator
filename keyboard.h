class Keyboard {
  bool keys[16];

public:

  Keyboard();

  //Return true if 'key is currently pressed
  bool isKeyPressed(int key);

  //Decode key press input and update keys array
  void keyPressHandler();

private:
  void resetKeys();

};
