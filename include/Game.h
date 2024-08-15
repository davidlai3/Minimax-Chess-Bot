#ifndef GAME_H
#define GAME_H

#include "Piece.h"
#define BOARD_ROWS 8
#define BOARD_COLS 8


class Game {
	public:

		enum Color {
			WHITE,
			BLACK,
		};

		Game(Color playerColor);
		~Game();

		bool makeMove(int srcRow, int srcCol, int dstRow, int dstCol);
		std::set<pos> getFilteredMoves(int row, int col);

		void printBoard(bool invert=false);


	private:
		char board[BOARD_ROWS][BOARD_COLS];
		Color _playerColor;
		pos _whiteKing;
		pos _blackKing;

		bool checkIfUnderAttack(Piece::PieceColor king);

};

#endif
