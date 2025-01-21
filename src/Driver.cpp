#include "../include/Game.h"
#include "../include/Engine.h"

#include <sstream>
#include <iostream>
#include <getopt.h>

using namespace std;

int main(int argc, char** argv) {

	int c; 
	bool f_flag = false;
	string file;
	while ((c = getopt(argc, argv, "hf:")) != -1) {
		switch (c) {
			case 'h':
				cout << "To move, type [a-h][1-8][a-h][1-8]";
				cout << "To forfeit, type `exit`";
				return 0;
			case 'f':
				f_flag = true; file = optarg;
				break;
			default:
				break;
		}
	}


	Game* game;
	if (f_flag) game = new Game(Piece::WHITE, file);
	else game = new Game(Piece::WHITE);

	/* MAIN LOOP */


	bool cur_state = game->check_endstate(game->get_color_to_move()) == Game::ONGOING;
	bool forfeit = game->forfeit_white || game->forfeit_black;


	Engine chess_engine( 2, Piece::BLACK, game );


	while (cur_state && !forfeit) {
		bool inv = game->get_color_to_move() == Piece::BLACK;
		game->print_board(inv);
		game->player_move();
		chess_engine.update_game( *game );

		// send to engine to make move
		string engine_move = chess_engine.best_engine_move();
		std::cout << "Engine plays: " << engine_move << std::endl;
		game->player_move( engine_move );
		

		cur_state = game->check_endstate(game->get_color_to_move()) == Game::ONGOING;
		forfeit = game->forfeit_white || game->forfeit_black;
	}

	/* END OF GAME */

	Piece::Color loser = game->get_color_to_move();
	game->print_board(loser == Piece::BLACK);

	if (forfeit) {
		cout << "Forfeit! " << (loser == Piece::WHITE ? "Black" : "White") << " wins!" << endl;
	}
	else {
		if (game->check_endstate(game->get_color_to_move()) == Game::CHECKMATE) {
			cout << "Checkmate! " << (loser == Piece::WHITE ? "Black" : "White") << " wins!" << endl;
		}
		else {
			cout << "Stalemate!" << endl;
		}
	}

	return 0;
}
