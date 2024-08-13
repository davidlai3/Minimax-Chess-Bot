#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {

    public:

        Queen(pos startingPosition, Color pieceColor);
        std::vector<pos> getMoves() override;

};


#endif