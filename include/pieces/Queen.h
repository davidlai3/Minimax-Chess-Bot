#ifndef QUEEN_H
#define QUEEN_H

#include "../Piece.h"

class Queen : public Piece {
	public:
		Queen(Color color, int x, int y);
		ull get_legal_moves(Piece* board[8][8], ull mask = 0) const;
};

#endif
