#include "../../include/pieces/King.h"

King::King(Color color, int x, int y) 
	: Piece(KING, color, x, y) {}

ull King::get_legal_moves(Piece* board[8][8], ull mask) const {
	ull moves = 0;
	int cur_x = get_pos().first;
	int cur_y = get_pos().second;

	int dx[4] = {1, 0, -1, 0};
	int dy[4] = {0, 1, 0, -1};

	for (int i = 0; i < 4; i++) {
		bool valid_x = cur_x + dx[i] >= 0 && cur_x + dx[i] < 8;
		bool valid_y = cur_y + dy[i] >= 0 && cur_y + dy[i] < 8;
		if (!(valid_x && valid_y)) continue;

		// Can move as long as it's not the same color
		if (board[cur_x + dx[i]][cur_y + dy[i]]->get_color() != get_color()) {
			moves |= 1ULL << Utils::MSK(cur_x + dx[i], cur_y + dy[i]);
		}
	}

	return moves;
}
