#ifndef PIECE_H
#define PIECE_H

#include <vector>
#define pos std::pair<int, int>

class Piece {

	public:

		virtual std::vector<pos> getMoves() = 0;


};

#endif
