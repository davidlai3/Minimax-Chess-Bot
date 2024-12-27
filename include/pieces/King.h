#ifndef KING_H
#define KING_H

#include "../Piece.h"

class King : public Piece {
	public:
		King(Color color, int x, int y);
		ull get_legal_moves(Piece* board[8][8], ull mask = 0) const;
		bool moved = false;
};

#endif
