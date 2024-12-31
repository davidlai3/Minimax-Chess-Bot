#include <iostream>
#include "../include/Game.h"

using namespace std;

int main() {
	Game game( Piece::WHITE );

	// game.print_board();

	bool cur_state = game.check_endstate(game.get_color_to_move()) == Game::ONGOING;
	bool forfeit = game.forfeit_white || game.forfeit_black;

	while (cur_state && !forfeit) {
		bool inv = game.get_color_to_move() == Piece::BLACK;
		game.print_board(inv);
		game.player_move();

		cur_state = game.check_endstate(game.get_color_to_move()) == Game::ONGOING;
		forfeit = game.forfeit_white || game.forfeit_black;
	}

	Piece::Color loser = game.get_color_to_move();
	game.print_board(loser == Piece::BLACK);

	if (forfeit) {
		cout << "Forfeit! " << (loser == Piece::WHITE ? "Black" : "White") << " wins!" << endl;
	}
	else {
		if (game.check_endstate(game.get_color_to_move()) == Game::CHECKMATE) {
			cout << "Checkmate! " << (loser == Piece::WHITE ? "Black" : "White") << " wins!" << endl;
		}
		else {
			cout << "Stalemate!" << endl;
		}
	}

	return 0;
}
