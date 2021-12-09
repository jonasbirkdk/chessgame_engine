#include "helper.h"
#include "../macros.h"
#include <iostream>
#include <functional>

void printBoard(Piece* board[8][8])
{
  for (int rank = 7; rank >= 0; --rank) {
    for (int file = 0; file <= 7; ++file) {
      int someInt = 10;
      int strLen;
      if (board[file][rank] != nullptr) {
        strLen = board[file][rank]->getType().length();
      } else {
        strLen = 7;
      }
      int i = 0;
      if (board[file][rank] != nullptr) {
        std::cout << board[file][rank]->getType();
      } else {
        std::cout << "nullptr";
      }
      while (i < ((someInt - strLen))) {
        std::cout << " ";
        ++i;
      }
    }
    std::cout << std::endl << std::endl;
  }
}

void forEachSquare(Piece* board[8][8], std::function<void(Piece* [8][8])>& func)
{
  for (int rank = 0; rank <= 7; ++rank) {
    for (int file = 0; file <= 7; ++file) {
      func(board);
    }
  }
}

void printMove(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  std::cout << board[srcFile][srcRank]->getColour() << "'s "
            << board[srcFile][srcRank]->getType() << " moves from " << srcSquare
            << " to " << destSquare;

  // If destSquare is not empty, print the piece we capture. As this function
  // comes with the precondition that moves printed are valid, the destSquare
  // will have an opponent piece if not empty
  if (!squareEmpty(destSquare, board)) {
    std::cout << " capturing " << board[destFile][destRank]->getColour()
              << "'s " << board[destFile][destRank]->getType();
  }
  std::cout << std::endl;
}

void printErrorMessage(std::string srcSquare, std::string destSquare,
    Piece* board[8][8], int errorCode)
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  switch (errorCode) {
  case INVALID_INPUT:
    std::cout << "Invalid move: " << srcSquare << " and/or " << destSquare
              << " are not on the board" << std::endl;
    break;
  case EMPTY_SOURCE_SQUARE:
    std::cout << "There is no piece at position " << srcSquare << std::endl;
    break;
  case OWN_KING_IN_CHECK:
    std::cout << board[srcFile][srcRank]->getColour() << "'s "
              << board[srcFile][srcRank]->getType() << " cannot move from "
              << srcSquare << " to " << destSquare;
    std::cout << std::endl;
    break;
  case NOT_YOUR_TURN:
    std::cout << "It is not " << board[srcFile][srcRank]->getColour()
              << "'s turn to move!" << std::endl;
    break;
  case FRIENDLY_FIRE:
    std::cout << board[srcFile][srcRank]->getColour() << "'s "
              << board[srcFile][srcRank]->getType() << " cannot move from "
              << srcSquare << " to " << destSquare;
    std::cout << std::endl;
    break;
  case PIECE_RULES_BROKEN:
    std::cout << board[srcFile][srcRank]->getColour() << "'s "
              << board[srcFile][srcRank]->getType() << " cannot move from "
              << srcSquare << " to " << destSquare;
    std::cout << std::endl;
    break;
  }
}

int fileToInt(std::string square) { return (square[0] - 'A'); }

int rankToInt(std::string square) { return (square[1] - '0' - 1); }

std::string integersToSquare(int file, int rank)
{
  std::string square;
  square.push_back(file + 'A');
  square.push_back(rank + '0' + 1);

  return square;
}

bool inputValid(std::string square)
{
  int file = fileToInt(square);
  int rank = rankToInt(square);

  if (file < 0 || file > 7) {
    return false;
  }

  if (rank < 0 || rank > 7) {
    return false;
  }

  return true;
}

bool diagonalMove(std::string srcSquare, std::string destSquare)
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  if (abs(srcFile - destFile) == abs(srcRank - destRank)) {
    return (abs(srcFile - destFile) > 0);
  }

  return false;
}

bool sideToSideMove(std::string srcSquare, std::string destSquare)
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  if (srcFile == destFile) {
    return (abs(srcRank - destRank) > 0);
  }

  if (srcRank == destRank) {
    return (abs(srcFile - destFile) > 0);
  }

  return false;
}

bool friendlyFire(
    std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  if (squareEmpty(srcSquare, board) || squareEmpty(destSquare, board)) {
    return false;
  }

  return (board[srcFile][srcRank]->getColour()
      == board[destFile][destRank]->getColour());
}

bool squareEmpty(std::string square, Piece* board[8][8])
{
  int file = fileToInt(square);
  int rank = rankToInt(square);

  return (board[file][rank] == nullptr);
}

void copyArray(Piece* destBoard[8][8], Piece* srcBoard[8][8])
{
  for (int file = 0; file <= 7; ++file) {
    for (int rank = 0; rank <= 7; ++rank) {
      destBoard[file][rank] = srcBoard[file][rank];
    }
  }
}

bool freePath(std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  int currentFile;
  if (srcFile < destFile) {
    currentFile = srcFile + 1;
  } else if (srcFile > destFile) {
    currentFile = srcFile - 1;
  } else {
    currentFile = srcFile;
  }

  int currentRank;
  if (srcRank < destRank) {
    currentRank = srcRank + 1;
  } else if (srcRank > destRank) {
    currentRank = srcRank - 1;
  } else {
    currentRank = srcRank;
  }

  // Values to add to current file / rank in while loop.
  // Will be +1 if sourceFile(or rank) is
  // lower than destFile(or rank); -1 if
  // greater than destFile(or rank); 0 if
  // sourceFile (or rank) equals destFile (or rank)
  int fileValueChange = currentFile - srcFile;
  int rankValueChange = currentRank - srcRank;

  while (currentFile != destFile || currentRank != destRank) {
    if (!squareEmpty(integersToSquare(currentFile, currentRank), board)) {
      return false;
    }
    currentFile += fileValueChange;
    currentRank += rankValueChange;
  }

  return true;
}

bool inCheck(std::string kingColour, Piece* board[8][8])
{
  std::string kingPosition;
  for (int file = 0; file <= 7; ++file) {
    for (int rank = 0; rank <= 7; ++rank) {
      if (board[file][rank] != nullptr) {
        if (board[file][rank]->getType() == "King"
            && board[file][rank]->getColour() == kingColour) {
          kingPosition = integersToSquare(file, rank);
          break;
        }
      }
    }
  }

  for (int file = 0; file <= 7; ++file) {
    for (int rank = 0; rank <= 7; ++rank) {
      std::string currentSquare = integersToSquare(file, rank);
      if (!squareEmpty(currentSquare, board)) {
        if (!friendlyFire(currentSquare, kingPosition, board)) {
          if (board[file][rank]->validMove(
                  currentSquare, kingPosition, board)) {
            return true;
          }
        }
      }
    }
  }

  return false;
}

bool noValidMoves(std::string teamColour, Piece* board[8][8])
{
  for (int srcFile = 0; srcFile <= 7; ++srcFile) {
    for (int srcRank = 0; srcRank <= 7; ++srcRank) {
      std::string srcSquare = integersToSquare(srcFile, srcRank);
      if (board[srcFile][srcRank] != nullptr) {
        if (board[srcFile][srcRank]->getColour() == teamColour) {
          for (int destFile = 0; destFile <= 7; ++destFile) {
            for (int destRank = 0; destRank <= 7; ++destRank) {
              std::string destSquare = integersToSquare(destFile, destRank);
              if (!friendlyFire(srcSquare, destSquare, board)) {
                if (board[srcFile][srcRank]->validMove(
                        srcSquare, destSquare, board)) {
                  Piece* tmpBoard[8][8];
                  copyArray(tmpBoard, board);
                  tmpBoard[destFile][destRank] = tmpBoard[srcFile][srcRank];
                  tmpBoard[srcFile][srcRank] = nullptr;
                  if (!inCheck(teamColour, tmpBoard)) {
                    return false;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return true;
}
