#include "King.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

King::King(std::string colour, std::string type)
    : Piece(colour, type) {};

King::~King() {};

bool King::validMove(std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
    int sourceFile = fileToInt(srcSquare);
    int sourceRank = rankToInt(srcSquare);
    int destFile = fileToInt(destSquare);
    int destRank = rankToInt(destSquare);

    if (abs(sourceFile - destFile) != 1 || abs(sourceRank - destRank) != 1) {
        return false;
    }

    return true;
}