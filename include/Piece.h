#ifndef PIECE_H
#define PIECE_H

#include <set>
#define pos std::pair<int, int>
// #define row first
// #define col second

class Piece {
	public:
		enum Color {
			WHITE,
			BLACK,
			EMPTY
		};

		static Color getColor(int row, int col, char (&board)[8][8]);
		static std::set<pos> getUnfilteredMoves(int row, int col, char (&board)[8][8]);
		bool checkAttack(int row, int col, char(&board)[8][8]);
	
	private:
		static std::set<pos> getPawnMoves(int row, int col, char (&board)[8][8]);
		static std::set<pos> getRookMoves(int row, int col, char (&board)[8][8]);
		static std::set<pos> getKnightMoves(int row, int col, char (&board)[8][8]);
		static std::set<pos> getBishopMoves(int row, int col, char (&board)[8][8]);
		static std::set<pos> getQueenMoves(int row, int col, char (&board)[8][8]);
		static std::set<pos> getKingMoves(int row, int col, char (&board)[8][8]);
};

#endif

