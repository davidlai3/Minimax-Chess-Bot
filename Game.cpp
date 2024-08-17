#include <cstring>
#include <cassert>
#include <iostream>
#include "include/Game.h"

#define BOARD_ROWS 8
#define BOARD_COLS 8

// Public methods:

// Uppercase letters: white
// Lowercase letters: black
Game::Game(Piece::Color playerColor) {

	Game::_playerColor = playerColor;
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
Game::~Game(){return;}

bool Game::playerMove() {
	std::string s; std::cin >> s;
	std::pair<pos, pos> parsedMove = parseMove(s);
	return makeMove(parsedMove.first, parsedMove.second);
}

bool Game::makeMove(pos srcPos, pos dstPos) {
	int srcRow = srcPos.first, srcCol = srcPos.second;
	int dstRow = dstPos.first, dstCol = dstPos.second;
	if (srcRow < 0 || srcRow >= 8 || srcCol < 0 || srcCol >= 8) return false;
	if (dstRow < 0 || dstRow >= 8 || dstCol < 0 || dstCol >= 8) return false;
	if (Piece::getColor(srcRow, srcCol, board) != _colorToMove) return false;

	std::set<pos> possibleMoves = getFilteredMoves(srcRow, srcCol);
	if (possibleMoves.count(std::make_pair(dstRow, dstCol)) == 0) return false;
	
	board[dstRow][dstCol] = board[srcRow][srcCol];
	board[srcRow][srcCol] = '.';

	_colorToMove = (_colorToMove == Piece::WHITE ? Piece::BLACK : Piece::WHITE);

	return true;
}

std::set<pos> Game::getFilteredMoves(int row, int col) {
	std::set<pos> unfilteredMoves = Piece::getUnfilteredMoves(row, col, board);
	std::set<pos> filteredMoves;
	std::set<pos>::iterator itr;

	char pieceToMove = board[row][col];
	Piece::Color kingColor = Piece::getColor(row, col, board);

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


bool Game::isCheckmate() {
	pos kingPosition = (_colorToMove == Piece::WHITE ? _whiteKing : _blackKing);
	if (!checkIfUnderAttack(_colorToMove)) return false;
	for (int row = 0; row < BOARD_ROWS; row++) {
		for (int col = 0; col < BOARD_COLS; col++) {

			if (Piece::getColor(row, col, board) != _colorToMove) continue;
			std::set possibleMoves = Piece::getUnfilteredMoves(row, col, board);
			char pieceToMove = board[row][col];

			std::set<pos>::iterator itr;
			for (itr = possibleMoves.begin(); itr != possibleMoves.end(); itr++) {
				pos moveToCheck = *itr;
				
				// Do the move
				board[row][col] = '.';
				char pieceCaptured = board[moveToCheck.first][moveToCheck.second];
				board[moveToCheck.first][moveToCheck.second] = pieceToMove;

				// check if there is a discovered check 
				if (!checkIfUnderAttack(_colorToMove)) return false;
				
				// revert the game board to original state
				board[row][col] = pieceToMove;
				board[moveToCheck.first][moveToCheck.second] = pieceCaptured;
			}
		}
	}
	return true;
}



void Game::printBoard(bool invert) {

	Piece::Color printColor = _playerColor;
	if (invert && printColor == Piece::WHITE) {
		printColor = Piece::BLACK;
	}
	else if (invert && printColor == Piece::BLACK) {
		printColor = Piece::WHITE;
	}

	if (printColor == Piece::WHITE) {
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

// Private methods:

bool Game::checkIfUnderAttack(Piece::Color kingColor) {

	assert (kingColor != Piece::EMPTY);
	pos kingPosition = (kingColor == Piece::WHITE) ? _whiteKing : _blackKing; 

	for (int row=0; row < BOARD_ROWS; row++) {
		for (int col=0; col < BOARD_COLS; col++) {

			Piece::Color pieceColor = Piece::getColor( row, col, board );

			if (kingColor == pieceColor) continue;
			auto positionsAttacked = Piece::getUnfilteredMoves(row, col, board);
			if (positionsAttacked.count(kingPosition) >= 1) return true;

		}
	}
	return false;
}

std::pair<pos, pos> Game::parseMove(std::string move) {
	// i think pawn promotions will have to be length 5
	assert(move.length() == 4);
	pos srcPos = std::make_pair(8 - (move[1] - '0'), move[0] - 'a');
	pos dstPos = std::make_pair(8 - (move[3] - '0'), move[2] - 'a');

	return std::make_pair(srcPos, dstPos);
}
