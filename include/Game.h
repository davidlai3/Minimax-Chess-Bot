#ifndef GAME_H
#define GAME_H

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

		void printBoard(bool invert=false);

	private:
		char board[BOARD_ROWS][BOARD_COLS];
		Color _playerColor;

};

#endif
