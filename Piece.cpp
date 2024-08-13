#include "include/Piece.h"
using namespace std;

pos Piece::getCurrentPosition(){
    return _currentPosition;
}

Piece::Color Piece::getColor(){
    return _color;
}

void Piece::setNewPosition(pos newPosition){
    _currentPosition = newPosition;
}

void Piece::setColor(Color color){
    _color = color;
}