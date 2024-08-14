#include "include/Knight.h"

Knight::Knight(pos startingPosition, Color pieceColor) {
	setNewPosition(startingPosition);
	setColor(pieceColor);
}

std::vector<pos> Knight::getMoves(Piece (&board)[8][8]) {
	std::vector<pos> res;
	pos currentPos = getCurrentPosition();

	Color currentColor = getColor();

	int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
	int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

	// TODO: Check if move creates discovered check
	for (int i = 0; i < 8; i++) {

		int newRow = currentPos.row + dx[i];
		int newCol = currentPos.col + dy[i];

		if (newRow < 0 || newRow >= 8) continue;
		if (newCol < 0 || newCol >= 8) continue;

		if (board[newRow][newCol].getColor() == currentColor) {
			continue;
		}
		else {
			res.push_back(std::make_pair(newRow, newCol));
		}
	}


	return res;
}
