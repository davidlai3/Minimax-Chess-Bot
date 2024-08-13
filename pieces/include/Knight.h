#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

    public:

        Knight(pos startingPosition, Color pieceColor);
        std::vector<pos> getMoves() override;

};


#endif