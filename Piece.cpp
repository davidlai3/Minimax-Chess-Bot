#include "include/Piece.h"
#include <cassert>
#include <cctype>
#include <utility>

Piece::PieceColor Piece::getColor(int row, int col, char (&board)[8][8]) {
	if (board[row][col] == '.') return EMPTY;
	else if (std::islower(board[row][col])) return WHITE;
	else return BLACK;
}

// returns possible moves for each position
// DOES NOT CHECK FOR DISCOVERED CHECK
std::set<pos> Piece::getUnfilteredMoves(int row, int col, char (&board)[8][8]) {

	switch (board[row][col]) {
		case 'P':
		case 'p':
			return Piece::getPawnMoves(row, col, board);
		case 'r':
		case 'R':
			return Piece::getRookMoves(row, col, board);
		case 'N':
		case 'n':
			return Piece::getKnightMoves(row, col, board);
		case 'B':
		case 'b':
			return Piece::getBishopMoves(row, col, board);
		case 'Q':
		case 'q':
			return Piece::getQueenMoves(row, col, board);
		case 'K':
		case 'k':
			return Piece::getKingMoves(row, col, board);
		default:
			return std::set<pos>();
	}

}



std::set<pos> Piece::getPawnMoves(int row, int col, char (&board)[8][8]) {
	PieceColor curColor = getColor(row, col, board);
	assert(curColor != EMPTY);
	PieceColor oppColor = (curColor == WHITE ? BLACK : WHITE);

	std::set<pos> ans;

	int step = (curColor == WHITE ? -1 : 1);

	// move forward one
	if (row + step >= 0 && row + step < 8) {
		if (getColor(row + step, col, board) == EMPTY) {
			ans.insert(std::make_pair(row + step, col));
		}
	} 

	// move foward two
	if (row == 1 && curColor == BLACK || row == 6 && curColor == WHITE) {
		if (getColor(row + 2*step, col, board) == EMPTY) {
			ans.insert(std::make_pair(row + 2*step, col));
		}
	}

	// capture
	if (row + step >= 0 && row + step < 8) {
		if (col - 1 >= 0 && getColor(row + step, col - 1, board) == oppColor) {
			ans.insert(std::make_pair(row + step, col - 1));
		}
		if (col + 1 < 8 && getColor(row + step, col + 1, board) == oppColor) {
			ans.insert(std::make_pair(row + step, col + 1));
		}
	}

	// TODO: En passant case

	return ans;
}

std::set<pos> Piece::getRookMoves(int row, int col, char (&board)[8][8]) {
	PieceColor curColor = getColor(row, col, board);
	assert(curColor != EMPTY);
	PieceColor oppColor = (curColor == WHITE ? BLACK : WHITE);

	std::set<pos> ans;

	for (int i = row; i < 8; i++) {
		if (getColor(i, col, board) == curColor) {
			break;
		}
		else if (getColor(i, col, board) == oppColor) {
			ans.insert(std::make_pair(i, col));
			break;
		}
		else {
			ans.insert(std::make_pair(i, col));
		}
	}

	for (int i = col; i < 8; i++) {
		if (getColor(row, i, board) == curColor) {
			break;
		}
		else if (getColor(i, col, board) == oppColor) {
			ans.insert(std::make_pair(row, i));
			break;
		}
		else {
			ans.insert(std::make_pair(row, i));
		}
	}

	return ans;
}

std::set<pos> Piece::getKnightMoves(int row, int col, char (&board)[8][8]) {
	PieceColor curColor = getColor(row, col, board);
	assert(curColor != EMPTY);

	std::set<pos> ans;

	int dx[8] = {-2, -1, 1, 2, 2, 1, -1, -2};
	int dy[8] = {-1, -2, -2, -1, 1, 2, 2, 1};

	// TODO: Check if move creates discovered check
	for (int i = 0; i < 8; i++) {
		int newRow = row + dx[i];
		int newCol = col + dy[i];

		if (newRow < 0 || newRow >= 8) continue;
		if (newCol < 0 || newCol >= 8) continue;

		if (getColor(newRow, newCol, board) == curColor) {
			continue;
		}
		else {
			ans.insert(std::make_pair(newRow, newCol));
		}
	}

	return ans;
}

std::set<pos> Piece::getBishopMoves(int row, int col, char (&board)[8][8]) {
	PieceColor curColor = getColor(row, col, board);
	assert(curColor != EMPTY);
	PieceColor oppColor = (curColor == WHITE ? BLACK : WHITE);

	std::set<pos> ans;

	int dx[4] = {1, -1, 1, -1};
	int dy[4] = {1, -1, -1, 1};

	// TODO: Check if move creates discovered check
    for (int i = 0; i < 4; i++) {

        // delta row and delta column
        int dr = dx[i];
        int dc = dy[i];

        int newRow = row + dr;
        int newCol = col + dc; 

        while (col >= 0 && col < 8 && row >= 0 && row < 8) {
            if (getColor(newRow, newCol, board) == curColor) {
                break;
            }

            ans.insert(std::make_pair(newRow, newCol));

            if (getColor(newRow, newCol, board) == oppColor) {
                break;
            }

			newRow += dr;
			newCol += dc;
        }

    }
	return ans;
}

std::set<pos> Piece::getQueenMoves(int row, int col, char (&board)[8][8]) {

	std::set<pos> ansRook = getRookMoves(row, col, board);
	std::set<pos> ansBish = getBishopMoves(row, col, board);

	std::set<pos> ans;

	ans.insert(ansRook.begin(), ansRook.end());
	ans.insert(ansBish.begin(), ansBish.end());

	return ans;
}

std::set<pos> Piece::getKingMoves(int row, int col, char (&board)[8][8]) {
	PieceColor curColor = getColor(row, col, board);
	assert(curColor != EMPTY);

	std::set<pos> ans;

	int dx[8] = {1, 1, 1, 0, 0, -1, -1, -1};
	int dy[8] = {1, 0, -1, 1, -1, 1, 0, -1};

	for (int i = 0; i < 8; i++) {
		int newRow = row + dx[i];
		int newCol = row + dy[i];

		if (newRow < 0 || newRow >= 8) continue;
		if (newCol < 0 || newCol >= 8) continue;

		if (getColor(row + dx[i], col + dy[i], board) == curColor) {
			continue;
		}

		ans.insert(std::make_pair(row + dx[i], col + dy[i]));

	}

	return ans;
}

