#include "include/Rook.h"

Rook::Rook(pos startingPosition, Color pieceColor) {
	setNewPosition(startingPosition);
	setColor(pieceColor);
}

std::vector<pos> Rook::getMoves(Piece (&board)[8][8]) {
	std::vector<pos> res;
	pos currentPos = getCurrentPosition();
	Color currentColor = getColor();

	// TODO: Check if move creates discovered check
	for (int i = currentPos.row; i < 8; i++) {
		if (board[i][currentPos.col].getColor() == currentColor) {
			break;
		}
		else if (board[i][currentPos.col].getColor() != Piece::EMPTY) {
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
