#ifndef GAME_H
#define GAME_H

#define BOARD_ROWS 8
#define BOARD_COLS 8

class Game {
	public:

		enum Color {
			WHITE,
			BLACK,
			EMPTY
		};

		Game(Color playerColor);
		~Game();

		void printBoard();

	private:
		char board[BOARD_ROWS][BOARD_COLS];

};

#endif
