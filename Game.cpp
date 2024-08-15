#include <cstring>
#include <iostream>
#include "include/Game.h"

#define BOARD_ROWS 8
#define BOARD_COLS 8

// Uppercase letters: white
// Lowercase letters: black
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
	Game::_playerColor = playerColor;

}
Game::~Game(){return;}

std::set<pos> Game::getFilteredMoves(int row, int col) {
	std::set<pos> unfilteredMoves = Piece::getUnfilteredMoves(row, col, board);
	std::set<pos> filteredMoves;
	std::set<pos>::iterator itr;

	char pieceToMove = board[row][col];
	Piece::PieceColor kingColor = Piece::getColor(row, col, board);

	// getEnPassant --> add to set
	// getCastle --> add to set

	for (itr = unfilteredMoves.begin(); itr != unfilteredMoves.end(); itr++)
	{ 
		pos moveToCheck = *itr;
		
		// Do the move
		board[row][col] = '.';
		char pieceCaptured = board[moveToCheck.first][moveToCheck.second];
		board[moveToCheck.first][moveToCheck.second] = pieceToMove;

		// check if there is a discovered check 
		if ( !checkIfUnderAttack( kingColor ) )
			filteredMoves.insert( moveToCheck );
		
		// revert the game board to original state
		board[row][col] = pieceToMove;
		board[moveToCheck.first][moveToCheck.second] = pieceCaptured;

	}

	return filteredMoves;
}


bool Game::checkIfUnderAttack(Piece::PieceColor kingColor) {

	assert (kingColor != Piece::PieceColor::EMPTY);
	pos kingPosition = (kingColor == WHITE) ? _whiteKing : _blackKing; 
	
	for( int row=0; row < BOARD_ROWS; row++ ){
		for( int col=0; col < BOARD_COLS; col++){
			Piece::PieceColor pieceColor = Piece::getColor( row, col, board );
			if (kingColor != pieceColor){
				auto positionsAttacked = Piece::getUnfilteredMoves(row, col, board);
				if (positionsAttacked.count(kingPosition) >= 1)
					return true;
			}
		}
	}

	return false;

}


void Game::printBoard(bool invert) {

	Color printColor = _playerColor;
	if (invert && printColor == WHITE) {
		printColor = BLACK;
	}
	else if (invert && printColor == BLACK) {
		printColor = WHITE;
	}

	if (printColor == WHITE) {
		for (int i = 0; i < BOARD_ROWS; i++) {
			for (int j = 0; j < BOARD_COLS; j++) {
				std::cout << board[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
	else {
		for (int i = BOARD_ROWS-1; i >= 0; i--) {
			for (int j = BOARD_COLS-1; j >= 0; j--) {
				std::cout << board[i][j] << " ";
			}
			std::cout << "\n";
		}
	}
}


