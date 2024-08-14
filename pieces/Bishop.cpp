#include "include/Bishop.h"

Bishop::Bishop(pos startingPosition, Color pieceColor) 
{

    setNewPosition(startingPosition);
    setColor(pieceColor);

}

std::vector<pos> Bishop::getMoves(Piece (&board)[8][8])
{
    std::vector<pos> res;
	pos currentPos = getCurrentPosition();
	Color currentColor = getColor();

    std::vector<std::pair<int, int>> directions = {
        {1, 1},
        {-1, -1},
        {1, -1},
        {-1, 1}
    };

	// TODO: Check if move creates discovered check
    for (const auto &dir : directions) {

        // delta row and delta column
        int dr = dir.first;
        int dc = dir.second;

        int new_row = currentPos.row + dr;
        int new_col = currentPos.col + dc; 


        while (currentPos.col >= 0 && currentPos.col < 8 && currentPos.row >= 0 && currentPos.row <8) {
            
            if (board[new_row][new_col].getColor() == currentColor) {
                break;
            }

            res.push_back(std::make_pair(new_row, new_col));
            
            if (board[new_row][new_col].getColor() != Piece::EMPTY) {
                break;
            }

        }

    }
	return res;
}
