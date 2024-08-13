#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {

    public:

        Knight(pos startingPosition, Color pieceColor);
        std::vector<pos> getMoves(Piece (&board)[8][8]) override;

};


#endif
