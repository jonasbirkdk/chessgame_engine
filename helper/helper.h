#pragma once

#include <iostream>

void printBoard(int board[8][8]);
int fileToInt(std::string square);
int rankToInt(std::string square);
std::string integersToSquare(int file, int rank);
bool inputValid(std::string square);
bool diagonalMove(std::string srcSquare, std::string destSquare);
bool sideToSideMove(std::string srcSquare, std::string destSquare);
bool squareEmpty(std::string square, int board[8][8]);
bool friendlyFire(std::string square, int pieceType, int board[8][8]);
std::string getPieceColour(std::string square, int board[8][8]);
std::string getPieceType(std::string square, int board[8][8]);
void copyArray(int destBoard[8][8], int srcBoard[8][8]);
bool freePath(std::string srcSquare, std::string destSquare, int board[8][8]);