#include "../../include/pieces/Pawn.h"

Pawn::Pawn(Color color, int x, int y) 
	: Piece(PAWN, color, x, y) {}

ull Pawn::get_legal_moves(Piece* board[8][8], ull mask) const {
	using Utils::MSK;

	ull moves = 0;
	int dir = get_color() == WHITE ? -1 : 1;
	int cur_x = get_pos().first;
	int cur_y = get_pos().second;

	// Move 1
	if (board[cur_x + dir][cur_y]->get_type() == EMPTY) {
		moves |= 1ULL << MSK(cur_x + dir, cur_y);
	}
	// Move 2
	if ((get_color() == WHITE && cur_x == 6) || (get_color() == BLACK && cur_x == 1)) {
		if (board[cur_x + 2 * dir][cur_y]->get_type() == EMPTY) {
			moves |= 1ULL << MSK(cur_x + 2 * dir, cur_y);
		}
	}
	// Capture left
    if (cur_y > 0 && board[cur_x + dir][cur_y - 1]->get_color() == get_opp()) {
		moves |= 1ULL << MSK(cur_x + dir, cur_y - 1);
    }
	// Capture right
	if (cur_y < 7 && board[cur_x + dir][cur_y + 1]->get_color() == get_opp()) {
		moves |= 1ULL << MSK(cur_x + dir, cur_y + 1);
	}

	return moves;
}
