#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {

    public:

        King(pos startingPosition, Color pieceColor);
        std::vector<pos> getMoves() override;

};


#endif