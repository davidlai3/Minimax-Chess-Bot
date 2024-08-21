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
	
	checkPawnMove(srcPos, dstPos); // update array if pawn moves 2
	
	// check for en passant and capture
	if (board[srcRow][srcCol] == 'p' || board[srcRow][srcCol] == 'P') {
		if (board[dstRow][dstCol] == '.' && srcCol != dstCol) {
			board[srcRow][dstCol] = '.';
		}
	}

	board[dstRow][dstCol] = board[srcRow][srcCol];
	board[srcRow][srcCol] = '.';

	_colorToMove = (_colorToMove == Piece::WHITE ? Piece::BLACK : Piece::WHITE);
	_moveCounter++;

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

	for (itr = unfilteredMoves.begin(); itr != unfilteredMoves.end(); itr++) { 
		pos moveToCheck = *itr;
		
		// Do the move
		board[row][col] = '.';
		char pieceCaptured = board[moveToCheck.first][moveToCheck.second];
		board[moveToCheck.first][moveToCheck.second] = pieceToMove;

		// check if there is a discovered check 
		if ( !checkKingUnderAttack( kingColor ) )
			filteredMoves.insert( moveToCheck );
		
		// revert the game board to original state
		board[row][col] = pieceToMove;
		board[moveToCheck.first][moveToCheck.second] = pieceCaptured;

	}

	pos enPassant = checkEnPassant(row, col);
	if (enPassant.first != -1 && enPassant.second != -1) {
		filteredMoves.insert(enPassant);
	}

	return filteredMoves;
}


bool Game::isCheckmate() {
	pos kingPosition = (_colorToMove == Piece::WHITE ? _whiteKing : _blackKing);
	if (!checkKingUnderAttack(_colorToMove)) return false;
	if (getFilteredMoves(kingPosition.first, kingPosition.second).size() > 0) return false;
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
				if (!checkKingUnderAttack(_colorToMove)) return false;
				
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

bool Game::checkKingUnderAttack(Piece::Color kingColor) {
	assert (kingColor != Piece::EMPTY);
	pos kingPosition = (kingColor == Piece::WHITE) ? _whiteKing : _blackKing; 

	return checkPosUnderAttack(kingPosition, kingColor);
}

bool Game::checkPosUnderAttack(pos position, Piece::Color playerColor){
	assert (playerColor != Piece::EMPTY);

	for (int row=0; row < BOARD_ROWS; row++) {
		for (int col=0; col < BOARD_COLS; col++) {

			Piece::Color pieceColor = Piece::getColor( row, col, board );

			if (playerColor == pieceColor) continue;
			auto positionsAttacked = Piece::getUnfilteredMoves(row, col, board);
			if (positionsAttacked.count(position) >= 1) return true;

		}
	}
	return false;
}

bool Game::checkCastleKingside(Piece::Color kingColor){
	assert (kingColor != Piece::EMPTY);

	if(kingColor == Piece::BLACK){
		// if the king or the rook has already moved, we can't castle
		if (_blackKingMoved || _blackKingsideRookMoved)
			return false; 

		// check if the path between rook and king is empty
		if (Piece::getColor(0, 6, board) != Piece::EMPTY && Piece::getColor(0, 7, board) != Piece::EMPTY)
			return false;
		
		// check if the positions are under attack
		pos posToCheck1 = std::make_pair(0, 6);
		pos posToCheck2 = std::make_pair(0, 7);

		return checkPosUnderAttack(posToCheck1, Piece::BLACK) && checkPosUnderAttack(posToCheck2, Piece::BLACK);
	} 

	// else kingColor must be white

	// if the king or the rook has already moved, we can't castle
	if (_whiteKingMoved || _whiteKingsideRookMoved)
		return false; 

	// check if the path between rook and king is empty
	if (Piece::getColor(7, 6, board) != Piece::EMPTY && Piece::getColor(7, 7, board) != Piece::EMPTY)
		return false;
	
	// check if the positions are under attack
	pos posToCheck1 = std::make_pair(7, 6);
	pos posToCheck2 = std::make_pair(7, 7);

	return checkPosUnderAttack(posToCheck1, Piece::WHITE) && checkPosUnderAttack(posToCheck2, Piece::WHITE);

}
bool Game::checkCastleQueenside(Piece::Color kingColor){

	assert (kingColor != Piece::EMPTY);

	if(kingColor == Piece::BLACK){
		// if the king or the rook has already moved, we can't castle
		if (_blackKingMoved || _blackQueensideRookMoved)
			return false; 

		// check if the path between rook and king is empty
		if (Piece::getColor(0, 1, board) != Piece::EMPTY 
			&& Piece::getColor(0, 2, board) != Piece::EMPTY 
			&& Piece::getColor(0,3,board) != Piece::EMPTY)
			return false;
		
		// check if the positions are under attack
		// NOTE: I don't think it matters if (0,1) is under attack according to the rules
		// King must not travel through a check or land onto a check
		// 0, 1 is unaffected i believe

		pos posToCheck1 = std::make_pair(0, 2);
		pos posToCheck2 = std::make_pair(0, 3);


		return checkPosUnderAttack(posToCheck1, Piece::BLACK) && checkPosUnderAttack(posToCheck2, Piece::BLACK);
	} 

	// else kingColor must be white

	// if the king or the rook has already moved, we can't castle
	if (_whiteKingMoved || _whiteQueensideRookMoved)
		return false; 

	// check if the path between rook and king is empty
	if (Piece::getColor(7, 1, board) != Piece::EMPTY && Piece::getColor(7, 2, board) != Piece::EMPTY && Piece::getColor(7, 3, board) != Piece::EMPTY)
		return false;
	
	// check if the positions are under attack
	pos posToCheck1 = std::make_pair(7, 2);
	pos posToCheck2 = std::make_pair(7, 3);

	return checkPosUnderAttack(posToCheck1, Piece::WHITE) && checkPosUnderAttack(posToCheck2, Piece::WHITE);
}

void Game::checkPawnMove(pos src, pos dst) {
	if (tolower(board[src.first][src.second]) != 'p') return;
	if (abs(dst.second - src.second) != 2) return;
	Piece::Color pawnColor = Piece::getColor(src.first, src.second, board);
	assert(pawnColor != Piece::EMPTY);

	if (pawnColor == Piece::BLACK) _blackPawns[src.second] = _moveCounter;
	if (pawnColor == Piece::WHITE) _whitePawns[src.second] = _moveCounter;
}

pos Game::checkEnPassant(int row, int col) {
	if (board[row][col] != 'p' && board[row][col] != 'P') {
		return std::make_pair(-1, -1);
	}

	Piece::Color pawnColor = Piece::getColor(row, col, board);
	char oppPiece = (pawnColor == Piece::BLACK ? 'P' : 'p');
	int step = (pawnColor == Piece::BLACK ? 1 : -1);

	if (pawnColor == Piece::BLACK && row != 4) return std::make_pair(-1, -1);
	if (pawnColor == Piece::WHITE && row != 3) return std::make_pair(-1, -1);

	if (col + 1 < 8 && board[row][col+1] == oppPiece) {
		if (oppPiece == 'p' && _blackPawns[col + 1] == _moveCounter - 1) {
			return std::make_pair(2, col + 1);
		}
		if (oppPiece == 'P' && _whitePawns[col + 1] == _moveCounter - 1) {
			return std::make_pair(5, col + 1);
		}
	}
	if (col - 1 >= 0 && board[row][col-1] == oppPiece) {
		if (oppPiece == 'p' && _blackPawns[col - 1] == _moveCounter - 1) {
			return std::make_pair(2, col - 1);
		}
		if (oppPiece == 'P' && _whitePawns[col - 1] == _moveCounter - 1) {
			return std::make_pair(5, col - 1);
		}
	}
	return std::make_pair(-1, -1);
}



std::pair<pos, pos> Game::parseMove(std::string move) {
	// i think pawn promotions will have to be length 5
	assert(move.length() == 4);
	pos srcPos = std::make_pair(8 - (move[1] - '0'), move[0] - 'a');
	pos dstPos = std::make_pair(8 - (move[3] - '0'), move[2] - 'a');

	return std::make_pair(srcPos, dstPos);
}
