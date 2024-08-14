#ifndef PIECE_H
#define PIECE_H

#include <vector>
#define pos std::pair<int, int>

class Piece {
	public:
		enum PieceColor {
			WHITE,
			BLACK,
			EMPTY
		};

		static PieceColor getColor(int row, int col, char (&board)[8][8]);
		static std::vector<pos> getMoves(int row, int col, char (&board)[8][8]);
	
	private:
		static std::vector<pos> getPawnMoves(int row, int col, char (&board)[8][8]);
		static std::vector<pos> getRookMoves(int row, int col, char (&board)[8][8]);
		static std::vector<pos> getKnightMoves(int row, int col, char (&board)[8][8]);
		static std::vector<pos> getBishopMoves(int row, int col, char (&board)[8][8]);
		static std::vector<pos> getQueenMoves(int row, int col, char (&board)[8][8]);
		static std::vector<pos> getKingMoves(int row, int col, char (&board)[8][8]);
		static bool checkDiscover(int srcRow, int srcCol, int dstRow, int dstCol, int (&board)[8][8]);
};

#endif

