#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {

    public:

        Pawn(pos startingPosition, Color pieceColor);
        std::vector<pos> getMoves(Piece (&board)[8][8]) override;

};


#endif
