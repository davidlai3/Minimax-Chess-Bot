#ifndef PAWN_H
#define PAWN_H

#include "../Piece.h"

class Pawn : public Piece {
	public:
		Pawn(Color color, int x, int y);
		ull get_legal_moves(Piece* board[8][8], ull mask = 0) const;
		int two_move_turn = -1;
};

#endif
