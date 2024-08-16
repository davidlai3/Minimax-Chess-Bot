all: driver.o
	./a.out
# The first target is the one that gets built if you run `make` with no arguments.
run: driver.o
	./a.out

driver.o: driver.cpp Game.o Piece.o
	g++ driver.cpp Game.o Piece.o

Game.o: Game.cpp Game.h Piece.o
	g++ Game.cpp Piece.o

Piece.o: Piece.cpp Piece.h
	g++ Piece.cpp

# Clean up the build
clean:
    rm -f *.o && rm -f *.out

