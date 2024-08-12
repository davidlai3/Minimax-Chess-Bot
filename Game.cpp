#include <cstring>
#include <iostream>
#include "include/Game.h"

#define BOARD_ROWS 8
#define BOARD_COLS 8

Game::Game(Color playerColor) {

	if (playerColor == WHITE) {
		char row1[8] = {'r','n','b','q','k','b','n','r'};
		char row2[8] = {'p','p','p','p','p','p','p','p'};
		char row3[8] = {'.','.','.','.','.','.','.','.'};
		char row4[8] = {'P','P','P','P','P','P','P','P'};
		char row5[8] = {'R','N','B','Q','K','B','N','R'};

		memcpy(board[0], row1, sizeof(row1));
		memcpy(board[1], row2, sizeof(row2));
		memcpy(board[2], row3, sizeof(row3));
		memcpy(board[3], row3, sizeof(row3));
		memcpy(board[4], row3, sizeof(row3));
		memcpy(board[5], row3, sizeof(row3));
		memcpy(board[6], row4, sizeof(row4));
		memcpy(board[7], row5, sizeof(row5));
	}
	else {
		char row5[8] = {'r','n','b','k','q','b','n','r'};
		char row4[8] = {'p','p','p','p','p','p','p','p'};
		char row3[8] = {'.','.','.','.','.','.','.','.'};
		char row2[8] = {'P','P','P','P','P','P','P','P'};
		char row1[8] = {'R','N','B','K','Q','B','N','R'};

		memcpy(board[0], row1, sizeof(row1));
		memcpy(board[1], row2, sizeof(row2));
		memcpy(board[2], row3, sizeof(row3));
		memcpy(board[3], row3, sizeof(row3));
		memcpy(board[4], row3, sizeof(row3));
		memcpy(board[5], row3, sizeof(row3));
		memcpy(board[6], row4, sizeof(row4));
		memcpy(board[7], row5, sizeof(row5));
	}

}

void Game::printBoard() {
	for (int i = 0; i < BOARD_ROWS; i++) {
		for (int j = 0; j < BOARD_COLS; j++) {
			std::cout << board[i][j] << " ";
		}
		std::cout << "\n";
	}
}


