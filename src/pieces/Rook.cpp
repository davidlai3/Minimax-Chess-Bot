#include "../../include/pieces/Rook.h"

Rook::Rook(Color color, int x, int y) 
	: Piece(ROOK, color, x, y) {}

ull Rook::get_legal_moves(Piece* board[8][8], ull mask) const {
	ull moves = 0;
	int cur_x = get_pos().first;
	int cur_y = get_pos().second;

	int dx[4] = {1, 1, -1, -1};
	int dy[4] = {1, -1, 1, -1};

	for (int i = 0; i < 4; i++) {
		int cpy_x = cur_x, cpy_y = cur_y;
		while (true) {
			// bounds check
			bool valid_x = cpy_x + dx[i] >= 0 && cpy_x + dx[i] < 8;
			bool valid_y = cpy_y + dy[i] >= 0 && cpy_y + dy[i] < 8;
			if (!(valid_x && valid_y)) break;
			cpy_x += dx[i]; cpy_y += dy[i];

			// break if same color
			if (board[cpy_x][cpy_y]->get_color() == get_color()) break;
			
			moves |= 1ULL << Utils::MSK(cpy_x, cpy_y);

			// break if opposite color
			if (board[cpy_x][cpy_y]->get_color() == get_opp()) break;
			if (mask & (1ULL << Utils::MSK(cpy_x, cpy_y))) break;
		}
	}

	return moves;
}
