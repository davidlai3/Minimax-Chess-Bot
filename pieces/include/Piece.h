#ifndef PIECE_H
#define PIECE_H

#include <vector>
#define pos std::pair<int, int>
#define row first
#define col second

class Piece {
	public:

		enum Color {
			WHITE,
			BLACK,
			EMPTY
		};

		virtual std::vector<pos> getMoves(Piece (&board)[8][8]);
		void setNewPosition(pos newPosition);
		void setColor(Color color);

		pos getCurrentPosition();
		Color getColor();
	
	private:
		Color _color;
		pos _currentPosition;
		
		
};

#endif
