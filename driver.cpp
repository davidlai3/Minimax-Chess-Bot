#include <iostream>
#include "include/Game.h"

using namespace std;

int main() {
	Game game( Game::WHITE );
	Game game2( Game::BLACK );

	game.printBoard();
	cout << endl;
	cout << endl;
	cout << endl;
	cout << endl;
	game2.printBoard();

	return 0;
}
