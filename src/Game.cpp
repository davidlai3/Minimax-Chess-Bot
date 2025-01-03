#include "../include/pieces/Rook.h"
#include "../include/pieces/Knight.h"
#include "../include/pieces/Bishop.h"
#include "../include/pieces/Queen.h"
#include "../include/pieces/King.h"
#include "../include/pieces/Pawn.h"
#include "../include/Game.h"

#include <iostream>
#include <fstream>

/* Public functions */

// Row 0: Black (lowercase)
// Row 8: White (uppercase)
Game::Game(Piece::Color player_color, std::string init_file) {
	Game::player_color = player_color;

	for (int i = 0; i < 2; i++) {
		int row = (i == 0 ? 0 : 7);
		Piece::Color side = (i == 0 ? Piece::BLACK : Piece::WHITE);
		for (int j = 0; j < 8; j++) {
			if (j == 0 || j == 7) board[row][j] = new Rook(side, row, j);
			if (j == 1 || j == 6) board[row][j] = new Knight(side, row, j);
			if (j == 2 || j == 5) board[row][j] = new Bishop(side, row, j);
			if (j == 3) board[row][j] = new Queen(side, row, j);
			if (j == 4) board[row][j] = new King(side, row, j);
		} 
	}
	for (int i = 0; i < 8; i++) {
		board[1][i] = new Pawn(Piece::BLACK, 1, i);
		board[6][i] = new Pawn(Piece::WHITE, 6, i);
	}
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = new Piece(Piece::EMPTY, Piece::NONE, i, j);
		}
	}

	if (init_file == "") return;

	std::ifstream file(init_file);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file." << std::endl;
    }
    std::string move;
    while (std::getline(file, move)) {
		player_move(move);
    }

    file.close();
}

Game::~Game() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			delete board[i][j];
		}
	}
}

// Query player for move and update board
void Game::player_move(std::string move) {
	std::string s; 
	if (move == "") {
		std::cout << "Enter move: "; std::cin >> s;
	}
	else s = move;

	if (s == "exit") {
		if (color_to_move == Piece::WHITE) forfeit_white = true;
		else forfeit_black = true;
		return;
	}

	int src_row, src_col, dst_row, dst_col;
	Piece::Type prom;
	parse_move(s, src_row, src_col, dst_row, dst_col, prom);

	// if invalid move then prompt again
	if (!validate_move(src_row, src_col, dst_row, dst_col, prom)) {
		std::cout << "Invalid move " << s << ". Try again." << std::endl;
		player_move();
	}
	// Update new values
	else {
		make_move(src_row, src_col, dst_row, dst_col, prom);
		std::cout << "move successful" << std::endl;
		move_counter++;
		color_to_move = (color_to_move == Piece::WHITE ? Piece::BLACK : Piece::WHITE);

		if (board[dst_row][dst_col]->get_type() == Piece::KING) {
			if (board[dst_row][dst_col]->get_color() == Piece::WHITE) {
				white_king = std::make_pair(dst_row, dst_col);
			}
			else {
				black_king = std::make_pair(dst_row, dst_col);
			}
			((King*) board[dst_row][dst_col])->moved = true;
		}
		if (board[dst_row][dst_col]->get_type() == Piece::PAWN) {
			if (abs(src_row - dst_row) == 2) {
				((Pawn*) board[dst_row][dst_col])->two_move_turn = move_counter;
			}
		}
		if (board[dst_row][dst_col]->get_type() == Piece::ROOK) {
			((Rook*) board[dst_row][dst_col])->moved = true;
		}
	}
}

/* Private functions invoked by player_move() */

// Parses move string
void Game::parse_move(std::string move, int &src_row, int &src_col, int &dst_row, int &dst_col, Piece::Type &prom) {
	if (move.length() < 4) {
		std::cerr << "ERROR: Invalid move string." << std::endl;
		src_row = -1; src_col = -1; dst_row = -1; dst_col = -1;
		return;
	}
	src_row = 8 - (move[1] - '0');
	src_col = move[0] - 'a';
	dst_row = 8 - (move[3] - '0');
	dst_col = move[2] - 'a';
	if (move.length() == 5) {
		char prom_char = tolower(move[4]);
		switch (prom_char) {
			case 'q': prom = Piece::QUEEN; break;
			case 'r': prom = Piece::ROOK; break;
			case 'b': prom = Piece::BISHOP; break;
			case 'n': prom = Piece::KNIGHT; break;
			default : prom = Piece::EMPTY;
		}
	}
	else {
		prom = Piece::EMPTY;
	}
}

// Actually moves the pieces
void Game::make_move(int src_row, int src_col, int dst_row, int dst_col, Piece::Type prom) {
	bool castle = false, en_passant = false, promote = false;
	Piece::Type type = board[src_row][src_col]->get_type();
	if (type == Piece::KING && abs(src_col - dst_col) == 2) castle = true;
	if (type == Piece::PAWN && abs(src_col - dst_col) == 1) {
		if (board[dst_row][dst_col]->get_type() == Piece::EMPTY) en_passant = true;
		if (dst_row == 0 || dst_row == 7) promote = true;
	}
	
	auto move = [&](int src_r, int src_c, int dst_r, int dst_c) {
		if (board[dst_r][dst_c] != nullptr) {
			delete board[dst_r][dst_c];
			board[dst_r][dst_c] = nullptr;
		}
		else {
			std::cerr << "ERROR: Double free." << std::endl;
		}
		board[dst_r][dst_c] = board[src_r][src_c];
		board[dst_r][dst_c]->set_pos(dst_r, dst_c);
		board[src_r][src_c] = new Piece(Piece::EMPTY, Piece::NONE, src_r, src_c);
	};

	move(src_row, src_col, dst_row, dst_col);

	if (castle) {
		if (dst_col < src_col) move(src_row, 0, dst_row, 3);
		else move(src_row, 7, dst_row, 5);
	}
	if (en_passant) {
		delete board[src_row][dst_col];
		board[src_row][dst_col] = new Piece(Piece::EMPTY, Piece::NONE, src_row, dst_col);
	}
	// Assume auto promote to queen for now
	if (promote) {
		delete board[dst_row][dst_col];
		switch (prom) {
			case Piece::KNIGHT: board[dst_row][dst_col] = new Knight(color_to_move, dst_row, dst_col); break;
			case Piece::BISHOP: board[dst_row][dst_col] = new Bishop(color_to_move, dst_row, dst_col); break;
			case Piece::ROOK: board[dst_row][dst_col] = new Rook(color_to_move, dst_row, dst_col); break;
			case Piece::QUEEN: board[dst_row][dst_col] = new Queen(color_to_move, dst_row, dst_col); break;
			default: board[dst_row][dst_col] = new Queen(color_to_move, dst_row, dst_col); break;
		}
	}
}

// Check if potential move is valid
bool Game::validate_move(int src_row, int src_col, int dst_row, int dst_col, Piece::Type prom) {
	
	// Bounds check
	if (src_row < 0 || src_row >= 8 || src_col < 0 || src_col >= 8) return false;
	if (dst_row < 0 || dst_row >= 8 || dst_col < 0 || dst_col >= 8) return false;

	// Source check
	if (board[src_row][src_col]->get_color() != color_to_move) return false;

	// Add more possible valid moves
	ull moves = board[src_row][src_col]->get_legal_moves(board);
	if (board[src_row][src_col]->get_type() == Piece::KING) {
		// std::cout << "about to check castle" << std::endl;
		moves |= check_castle(board[src_row][src_col]->get_color());
	}
	if (board[src_row][src_col]->get_type() == Piece::PAWN) {
		moves |= check_en_passant(src_row, src_col);
	}

	// Check if promotion is valid, assume empty goes to queen
	if (board[src_row][src_col]->get_type() == Piece::PAWN) {
		if (dst_row == 0 || dst_row == 7) {
			if (prom == Piece::KING) return false;
			else if (prom == Piece::PAWN) return false;
		}
	}

	// Check if destination is within set of valid
	int rep = Utils::MSK(dst_row, dst_col);
	if (!(moves & (1ULL << rep))) return false;

	// Check if move leads to check
	if (!check_move(src_row, src_col, dst_row, dst_col)) return false;

	return true;
}

ull Game::check_castle(Piece::Color king_color) {
	int row	= (king_color == Piece::WHITE ? white_king.first : black_king.first);
	int col = (king_color == Piece::WHITE ? white_king.second : black_king.second);
	Piece::Color opp = board[row][col]->get_opp();

	ull mask = 0;
	// if king has moved then return 0
	if (board[row][col]->get_type() == Piece::KING) {
		if (((King*) board[row][col])->moved) return mask;
	}

	bool queen_side = true, king_side = true;
	if (board[row][0]->get_type() == Piece::ROOK) {
		// only if queen side rook hasn't moved
		if (!((Rook*) board[row][0])->moved) {
			// check if the path is clear
			for (int i = 1; i <= 3; i++) {
				if (board[row][i]->get_type() != Piece::EMPTY) queen_side = false;
				if (check_pos_under_attack(row, i, opp)) queen_side = false;
			}
		}
	}
	if (board[row][7]->get_type() == Piece::ROOK) {
		if (!((Rook*) board[row][0])->moved) {
			for (int i = 5; i <= 6; i++) {
				if (board[row][i]->get_type() != Piece::EMPTY) king_side = false;
				if (check_pos_under_attack(row, i, opp)) king_side = false;
			}
		}
	}
	if (queen_side) mask |= (1ULL << Utils::MSK(row, 2));
	if (king_side) mask |= (1ULL << Utils::MSK(row, 6));
	return mask;
}

ull Game::check_en_passant(int row, int col) {
	if (board[row][col]->get_type() != Piece::PAWN) return 0;

	Piece::Color opp = board[row][col]->get_opp();
	int dir = board[row][col]->get_color() == Piece::WHITE ? -1 : 1;

	ull mask = 0;
	bool left = false, right = false;
	if (col > 0 && board[row][col-1]->get_type() == Piece::PAWN) {
		if (board[row][col-1]->get_color() == opp) {
			if (((Pawn*) board[row][col-1])->two_move_turn == move_counter) {
				left = true;
			}
		}
	}
	if (col < 7 && board[row][col+1]->get_type() == Piece::PAWN) {
		if (board[row][col+1]->get_color() == opp) {
			if (((Pawn*) board[row][col+1])->two_move_turn == move_counter) {
				right = true;
			}
		}
	}

	if (left) mask |= (1ULL << Utils::MSK(row + dir, col - 1));
	if (right) mask |= (1ULL << Utils::MSK(row + dir, col + 1));

	return mask;
}

// Check if move leads to check
bool Game::check_move(int src_row, int src_col, int dst_row, int dst_col) {
	
	bool castle = false, en_passant = false, promote = false;
	Piece::Type type = board[src_row][src_col]->get_type();
	if (type == Piece::KING && abs(src_col - dst_col) == 2) castle = true;
	if (type == Piece::PAWN && abs(src_col - dst_col) == 1) {
		if (board[dst_row][dst_col]->get_type() == Piece::EMPTY) en_passant = true;
		if (dst_row == 0 || dst_row == 7) promote = true;
	}
	Piece* tmp2;
	if (castle) {
		if (dst_col < src_col) tmp2 = move_tmp(src_row, 0, dst_row, 3); // Queenside
		else tmp2 = move_tmp(src_row, 7, dst_row, 5);							// Kingside
	}
	if (en_passant) {
		tmp2 = board[src_row][dst_col];
		board[src_row][dst_col] = new Piece(Piece::EMPTY, Piece::NONE, src_row, dst_col);
	}
	if (promote) {
		tmp2 = board[dst_row][dst_col];
		board[dst_row][dst_col] = new Queen(color_to_move, dst_row, dst_col);
	}
	
	Piece::Color color = board[src_row][src_col]->get_color();
	Piece* tmp = move_tmp(src_row, src_col, dst_row, dst_col);
	bool res = true;

	if (color == Piece::WHITE) {
		if (check_pos_under_attack(white_king.first, white_king.second, Piece::BLACK)) res = false;
	}
	else if (color == Piece::BLACK) {
		if (check_pos_under_attack(black_king.first, black_king.second, Piece::WHITE)) res = false;
	}

	unmove_tmp(src_row, src_col, dst_row, dst_col, tmp);

	if (promote) {
		board[dst_row][dst_col]->~Piece();
		board[dst_row][dst_col] = tmp2;
	}
	if (en_passant) {
		board[src_row][dst_col]->~Piece();
		board[src_row][dst_col] = tmp2;
	}
	if (castle) {
		if (dst_col < src_col) unmove_tmp(src_row, 0, dst_row, 3, tmp2);
		else unmove_tmp(src_row, 7, dst_row, 5, tmp2);
	}

	return res;
}

bool Game::check_pos_under_attack(int row, int col, Piece::Color attacker){
	int rep = Utils::MSK(row, col);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->get_color() == attacker) {
				ull moves = board[i][j]->get_legal_moves(board);
				if (moves & (1ULL << rep)) return true;
			}
		}
	}
	return false;
}

Piece* Game::move_tmp(int src_row, int src_col, int dst_row, int dst_col) {
	Piece* tmp = board[dst_row][dst_col];
	board[dst_row][dst_col] = board[src_row][src_col];
	board[dst_row][dst_col]->set_pos(dst_row, dst_col);
	board[src_row][src_col] = new Piece(Piece::EMPTY, Piece::NONE, src_row, src_col);
	return tmp;
}

void Game::unmove_tmp(int src_row, int src_col, int dst_row, int dst_col, Piece* tmp) {
	if (board[src_row][src_col] != nullptr) {
		delete board[src_row][src_col]; 
		board[src_row][src_col] = nullptr;
	}

	board[src_row][src_col] = board[dst_row][dst_col];
	board[src_row][src_col]->set_pos(src_row, src_col);
	board[dst_row][dst_col] = tmp;
}

/* Public Functions */

// Checks if [color] king can continue playing
// TODO: Check for 3-move rule and 50-move rule
Game::State Game::check_endstate(Piece::Color color) {
	int row = (color == Piece::WHITE ? white_king.first : black_king.first);
	int col = (color == Piece::WHITE ? white_king.second : black_king.second);
	Piece::Color opp = board[row][col]->get_opp();
	ull king_moves = board[row][col]->get_legal_moves(board);
	ull attacks = 0; // possible moves by opposing side
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->get_color() == opp) {
				attacks |= board[i][j]->get_legal_moves(board);
			}
		}
	}
	// If the king can move to a safe square or be then the game can continue
	// We don't need to worry about castles because a castle implies there is a safe square already
	if (king_moves & ~attacks) return ONGOING;
	

	// Check possible blocks/attacker captures
	bool in_check = check_pos_under_attack(row, col, opp);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j]->get_color() != color || board[i][j]->get_type() == Piece::KING) {
				continue;
			}
			ull moves = board[i][j]->get_legal_moves(board);
			moves |= check_en_passant(i, j);
			for (int k = 0; k < 64; k++) {
				if (moves & (1ULL << k)) {
					pos dst = Utils::UNMSK(k);
					if (check_move(i, j, dst.first, dst.second)) return ONGOING;
				}
			}
		}
	}
	// At this point we know that there are no valid moves
	return in_check ? CHECKMATE : STALEMATE;
}

void Game::print_board(bool invert) {
	Piece::Color print_color = player_color;
	if (invert && print_color == Piece::WHITE) {
		print_color = Piece::BLACK;
	}
	else if (invert && print_color == Piece::BLACK) {
		print_color = Piece::WHITE;
	}

	std::cout << " ";
	for (int i = 0; i < 8; i++) {
		char c1 = 'a' + i; char c2 = 'a' + 7 - i;
		if (!invert) std::cout << " " << c1;
		else std::cout << " " << c2;
	}
	std::cout << std::endl;

	if (print_color == Piece::WHITE) {
		for (int i = 0; i < 8; i++) {
			std::cout << 8 - i << " ";
			for (int j = 0; j < 8; j++) {
				Piece::Color color = board[i][j]->get_color();
				Piece::Type type = board[i][j]->get_type();
				std::cout << Piece::type_char[color][type] << " ";
			}
			std::cout << "\n";
		}
	}
	else {
		for (int i = 7; i >= 0; i--) {
			std::cout << 8 - i << " ";
			for (int j = 7; j >= 0; j--) {
				Piece::Color color = board[i][j]->get_color();
				Piece::Type type = board[i][j]->get_type();
				std::cout << Piece::type_char[color][type] << " ";
			}
			std::cout << "\n";
		}
	}

	std::cout << " ";
	for (int i = 0; i < 8; i++) {
		char c1 = 'a' + i; char c2 = 'a' + 7 - i;
		if (!invert) std::cout << " " << c1;
		else std::cout << " " << c2;
	}
	std::cout << std::endl;
}

Piece::Color Game::get_color_to_move() const {
	return color_to_move;
}

