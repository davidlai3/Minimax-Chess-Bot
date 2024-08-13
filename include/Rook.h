#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {

    public:

        Rook(pos startingPosition, Color pieceColor);
        std::vector<pos> getMoves() override;

};


#endif