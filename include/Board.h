#ifndef BOARD_H
#define BOARD_H

#include "Piece.h"

class Board {
	public:
		Board(std::string file);
		~Board();

		Piece* board[8][8];
		Board* prevBoard;


		void parse_and_make_move(std::string move = "");
		void temp_move(int src_row, int src_col, int dst_row, int dst_col, Piece::Type prom);
		bool validate_move(int src_row, int src_col, int dst_row, int dst_col, Piece::Type prom);
		State check_endstate(Piece::Color color);
		void print_board(bool invert=false);
		Piece::color get_player_to_move( std:: )
		

		void undo_move();
	private:
		int curr_move_number;
};



class Game {
	public:

		// Constructor
		Game(Piece::Color player_color, std::string file = "");
		// Destructor
		~Game();

		enum State {
			ONGOING,
			CHECKMATE,
			STALEMATE
		};

		bool forfeit_white = false;
		bool forfeit_black = false;

		
		

	private:
		Piece* board[8][8];
		Piece::Color color_to_move = Piece::WHITE;
		Piece::Color player_color;
		
		pos white_king = std::make_pair(7, 4);
		pos black_king = std::make_pair(0, 4);

		int move_counter = 0;

		// void parse_move(std::string move, int &src_row, int &src_col, int &dst_row, int &dst_col, Piece::Type &prom);

		// void make_move(int src_row, int src_col, int dst_row, int dst_col, Piece::Type prom);
		// bool validate_move(int src_row, int src_col, int dst_row, int dst_col, Piece::Type prom);

		ull check_castle(Piece::Color king_color);
		ull check_en_passant(int row, int col);

		bool check_move(int src_row, int src_col, int dst_row, int dst_col);
		bool check_pos_under_attack(int row, int col, Piece::Color pieceColor);
		Piece* move_tmp(int src_row, int src_col, int dst_row, int dst_col);
		void unmove_tmp(int src_row, int src_col, int dst_row, int dst_col, Piece* tmp);


};


#endif
