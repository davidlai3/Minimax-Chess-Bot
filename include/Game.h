#ifndef GAME_H
#define GAME_H

#include <string>
#include "Piece.h"
#define BOARD_ROWS 8
#define BOARD_COLS 8


class Game {
	public:

		Game(Piece::Color playerColor);
		~Game();

		bool playerMove();
		bool makeMove(pos srcPos, pos dstPos);
		std::set<pos> getFilteredMoves(int row, int col);
		bool isCheckmate();
		bool isStalemate();
		void printBoard(bool invert=false);


	private:
		char board[BOARD_ROWS][BOARD_COLS];
		Piece::Color _colorToMove = Piece::WHITE;
		Piece::Color _playerColor;
		pos _whiteKing;
		pos _blackKing;

		bool checkIfUnderAttack(Piece::Color king);
		std::pair<pos, pos> parseMove(std::string move);

};

#endif
