#ifndef BISHOP_H
#define BISHOP_H

#include "../Piece.h"

class Bishop : public Piece {
	public:
		Bishop(Color color, int x, int y);
		ull get_legal_moves(Piece* board[8][8], ull mask = 0) const;
};

#endif
