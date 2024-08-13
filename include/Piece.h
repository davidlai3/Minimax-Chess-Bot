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
		void setColor(Color color);

		pos getCurrentPosition();
		Color getColor();
	
	private:
		Color _color;
		pos _currentPosition;
		
		
};

#endif
