all: 
	make clean && make run

# The first target is the one that gets built if you run `make` with no arguments.
run: a.out
	./a.out

a.out: Game.cpp Piece.cpp driver.cpp
	g++ Game.cpp Piece.cpp driver.cpp

# Clean up the build
clean:
	rm -f *.o && rm -f *.out

