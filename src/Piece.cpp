#include "../include/Piece.h"

// Constructor
Piece::Piece(Type type, Color color, int x, int y)
	: type(type), color(color), x(x), y(y) {}

// Getters
Piece::Type Piece::get_type() const {
	return type;
}

Piece::Color Piece::get_color() const {
	return color;
}

Piece::Color Piece::get_opp() const {
	return color == WHITE ? BLACK : WHITE;
}

pos Piece::get_pos() const {
	return std::make_pair(x, y);
}

// Setters
void Piece::set_pos(int x, int y) {
	this->x = x;
	this->y = y;
}

// Legal Moves (Empty for parent class)
ull Piece::get_legal_moves(Piece* board[8][8], ull mask) const {
	return 0ULL;
}

// Destructor
Piece::~Piece() {}
