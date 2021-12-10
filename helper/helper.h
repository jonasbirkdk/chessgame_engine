#pragma once

#include <iostream>
#include <functional>
#include "../Piece/Piece.h"

// Takes function as input as well as optional boolean variable
// then executes function for each square on the chessboard (A1 to H8).
// If boolean is provided, forEachSquare() will stop looping
// once the boolean variable has value set to 'true'. Hence, bool input should
// always be false initially, as otherwise the loop will break immediately
void forEachSquare(
    std::function<void(int file, int rank)> const& func, bool optional = false);

// Takes a string square as input and returns its file
// as a 0-based index into the alphabet (e.g., A8 returns 0)
int fileToInt(std::string square);

// Takes a string square as input and returns its rank
// as a 0-based index number (e.g., A8 returns 7)
int rankToInt(std::string square);

// Takes a 0-based index into the alphabet 'file'
// and 0-based index number 'rank and returns
// the corresponding square on a chessboard as a string
// (e.g., file = 0, rank = 7 returns 'A8')
std::string integersToSquare(int file, int rank);

// Takes square as input and returns true if
// square is on the chessboard, false otherwise
// (e.g., A8 returns true, I8 or A9 returns false)
bool inputValid(std::string square);

// Takes two strings (source and destination squares) as input
// and returns true if move is diagonal, false otherwise
bool diagonalMove(std::string srcSquare, std::string destSquare);

// Takes two strings (source and destination squares) as input
// and returns true if move is side-to-side (i.e., either a horizontal
// or vertical straight line), false otherwise
bool sideToSideMove(std::string srcSquare, std::string destSquare);

// Takes two boards as input and copies all elements of
// the srcBoard to the destBoard
void copyArray(Piece* destBoard[8][8], Piece* srcBoard[8][8]);

// Takes two strings (source and destination squares) and a board as input,
// returning true if all squares BETWEEN srcSquare and destSquare are empty,
// (i.e., not including destSquare itself), false otherwise
bool freePath(
    std::string srcSquare, std::string destSquare, Piece* board[8][8]);

// Precondition: string input kingColour must be either
// "White" or "Black"
// Takes string kingColour and board as input and returns
// true if King of colour kingColour is in check, false otherwise
bool inCheck(std::string kingColour, Piece* board[8][8]);

// Precondition: string teamColour must be either "Black" or "White"
// Takes string teamColour and a board as input and returns true
// if there are no legal moves for any piece of colour teamColour
bool noValidMoves(std::string teamColour, Piece* board[8][8]);

// Precondition: srcSquare and destSquare constitutes a legal move
// on 'board' (e.g., srcSquare not empty, piece on destSquare
// not same colour as srcSquare).
// Takes two strings (source and destination squares, e.g., A2 and A4)
// as well as a chessboard 'board', then prints the move to console
// (including whether a piece was captured with the move).
// It does not print whether the move leads to check, checkmate or stalemate
void printMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8]);

// Takes two strings (source and destination squares), a chessboard
// and an error code (0-6, see 'macros.h'), then prints informative
// error messages corresponding to the error code
void printErrorMessage(std::string srcSquare, std::string destSquare,
    Piece* board[8][8], int errorCode);