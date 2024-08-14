#include "include/Queen.h"

Queen::Queen(pos startingPosition, Color pieceColor) {
	setNewPosition(startingPosition);
	setColor(pieceColor);
}

std::vector<pos> Queen::getMoves(Piece (&board)[8][8]) {
	std::vector<pos> res;
	pos currentPos = getCurrentPosition();
	Color currentColor = getColor();

	// TODO: Check if move creates discovered check

	for (int i = 1; i < 8; i++) {
		int newRow = currentPos.row + i;
		int newCol = currentPos.col + i;

		if (newRow >= 8 || newCol >= 8) break;
		if (board[newRow][newCol].getColor() == currentColor) break;
		if (board[newRow][newCol].getColor() != EMPTY) {
			continue;
		}

	}

	for (int i = currentPos.row; i < 8; i++) {
		if (board[i][currentPos.col].getColor() == currentColor) {
			break;
		}
		else if (board[i][currentPos.col].getColor() != EMPTY) {
			res.push_back(std::make_pair(i, currentPos.col));
			break;
		}
		else {
			res.push_back(std::make_pair(i, currentPos.col));
		}
	}

	for (int i = currentPos.col; i < 8; i++) {
		if (board[currentPos.row][i].getColor() == currentColor) {
			break;
		}
		else {
			res.push_back(std::make_pair(currentPos.row, i));
		}
	}

	return res;
}
