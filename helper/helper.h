#pragma once

#include <iostream>
#include "../Piece/Piece.h"

void printBoard(Piece* board[8][8]);

void forEachSquare(
    Piece* board[8][8], std::function<void(Piece* [8][8])>& func);

void printMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8]);

void printErrorMessage(std::string srcSquare, std::string destSquare,
    Piece* board[8][8], int errorCode);

int fileToInt(std::string square);

int rankToInt(std::string square);

std::string integersToSquare(int file, int rank);

bool inputValid(std::string square);

bool diagonalMove(std::string srcSquare, std::string destSquare);

bool sideToSideMove(std::string srcSquare, std::string destSquare);

bool squareEmpty(std::string square, Piece* board[8][8]);

bool friendlyFire(std::string square, std::string colour, Piece* board[8][8]);

void copyArray(Piece* destBoard[8][8], Piece* srcBoard[8][8]);

bool freePath(
    std::string srcSquare, std::string destSquare, Piece* board[8][8]);

bool inCheck(std::string kingColour, Piece* board[8][8]);

bool noValidMoves(std::string teamColour, Piece* board[8][8]);
