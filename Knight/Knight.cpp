#include "Knight.h"
#include "../helper/helper.h"
#include "../macros.h"
#include <iostream>

Knight::Knight(std::string colour, std::string type)
    : Piece(colour, type) {};

Knight::~Knight() {};

bool Knight::validMove(std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
    int sourceFile = fileToInt(srcSquare);
    int sourceRank = rankToInt(srcSquare);
    int destFile = fileToInt(destSquare);
    int destRank = rankToInt(destSquare);

    // Check case where Knight jumps one square horizontally
    if (abs(sourceFile - destFile) == 1) {
        return (abs(sourceRank - destRank) == 2);
    }

    // Check case where Knight jumps one square vertically
    if (abs(sourceRank - destRank) == 1) {
        return (abs(sourceFile - destFile) == 2);
    }

    return false;
}