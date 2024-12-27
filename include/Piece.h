#ifndef PIECE_H
#define PIECE_H

#include "Utils.h"
#include <string>
#define pos std::pair<int, int>
#define ull unsigned long long
// #define row first
// #define col second

class Piece {
	public:
		enum Type { EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };
		enum Color { WHITE, BLACK, NONE };
		static constexpr char type_char[3][7] = {
			'.', 'P', 'N', 'B', 'R', 'Q', 'K',
			'.', 'p', 'n', 'b', 'r', 'q', 'k',
			'.' 
		};

	private:
		Type type;
		Color color;
		int x, y;

	public:
		// Constructor
		Piece(Type type, Color color, int x, int y);

		// Getters
		Type get_type() const;
		Color get_color() const;
		Color get_opp() const;
		pos get_pos() const;

		// Setters
		void set_pos(int x, int y);

		// Virtual functions
		virtual ull get_legal_moves(Piece* board[8][8], ull mask = 0) const;

		// Destructor
		virtual ~Piece();
};

#endif

