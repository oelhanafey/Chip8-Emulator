main: main.o chip8.o keyboard.o
	g++ -o main main.o chip8.o keyboard.o -lSDL2

main.o: main.cc chip8.h keyboard.h
	g++ -c main.cc

chip8.o: chip8.cc chip8.h keyboard.h
	g++ -c chip8.cc

keyboard.o: keyboard.cc keyboard.h
	g++ -c keyboard.cc

clean:
	rm main main.o chip8.o keyboard.o
