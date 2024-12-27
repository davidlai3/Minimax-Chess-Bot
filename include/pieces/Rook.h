#ifndef ROOK_H
#define ROOK_H

#include "../Piece.h"

class Rook : public Piece {
	public:
		Rook(Color color, int x, int y);
		ull get_legal_moves(Piece* board[8][8], ull mask = 0) const;
		bool moved = false;
};

#endif
