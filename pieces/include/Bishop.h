#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {

    public:

        Bishop(pos startingPosition, Color pieceColor);
        std::vector<pos> getMoves(Piece (&board)[8][8]) override;

};


#endif
