#ifndef PIECE_H
#define PIECE_H

#include <vector>
#define pos std::pair<int, int>

class Piece {
	public:

		enum Color {
			WHITE,
			BLACK
		};

		virtual std::vector<pos> getMoves() = 0;
		void setNewPosition(pos newPosition);
	
	private:
		Color color;
		pos currentPosition;
		
		
};

#endif
