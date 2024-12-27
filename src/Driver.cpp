#include <iostream>
#include "../include/Game.h"

using namespace std;

int main() {
	Game game( Piece::WHITE );

	// game.print_board();

	while (game.check_endstate(game.get_color_to_move()) == Game::ONGOING) {
		bool inv = game.get_color_to_move() == Piece::BLACK;
		game.print_board(inv);
		game.player_move();
	}

	Piece::Color loser = game.get_color_to_move();
	game.print_board(loser == Piece::BLACK);

	if (game.check_endstate(game.get_color_to_move()) == Game::CHECKMATE) {
		cout << "Checkmate! " << (loser == Piece::WHITE ? "Black" : "White") << " wins!" << endl;
	}
	else {
		cout << "Stalemate!" << endl;
	}

	return 0;
}
