#include <iostream>
#include "include/Game.h"

using namespace std;

int main() {
	Game game( Piece::WHITE );

	while (!game.isCheckmate()) {
		game.printBoard();
		if (game.playerMove()) {
			cout << "move successful" << endl;
		}
		else {
			cout << "move failed" << endl;
		}
	}


	return 0;
}
