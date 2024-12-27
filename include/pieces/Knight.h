#ifndef KNIGHT_H
#define KNIGHT_H

#include "../Piece.h"

class Knight : public Piece {
	public:
		Knight(Color color, int x, int y);
		ull get_legal_moves(Piece* board[8][8], ull mask = 0) const;
};

#endif
