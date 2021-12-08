#pragma once

#include "../macros.h"
#include "../Piece/Piece.h"
#include <iostream>

class ChessBoard {
public:
    int board[8][8];
    Piece* ptrBoard[8][8];
    Piece* pieceArray[TOTAL_PIECES];
    std::string nextUp = "White";

    ChessBoard();
    void resetPtrBoard();
    bool kingInCheck(std::string srcSquare, std::string destSquare, int kingID);
    bool noValidMoves(int kingID);
    void submitMove(std::string srcSquare, std::string destSquare);
    void resetBoard();
};