#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

class Board {
	public:
		Board(std::string file);
		~Board();

		Piece* board[8][8];
		Board* prevBoard;

		void make_move(int x1, int y1, int x2, int y2);
		void undo_move();
	private:
};

#endif
