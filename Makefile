main: main.o chip8.o
	g++ -o main main.o chip8.o

main.o: main.cc chip8.h
	g++ -c main.cc

chip8.o: chip8.cc chip8.h
	g++ -c chip8.cc

clean:
	rm main main.o chip8.o
