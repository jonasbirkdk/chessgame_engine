#include "helper.h"
#include "../macros.h"

void forEachSquare(
    std::function<void(int file, int rank)> const& func, bool optional)
{
  for (int file = 0; file <= MAX_FILE; ++file) {
    for (int rank = 0; rank <= MAX_RANK; ++rank) {
      if (optional == true) {
        break;
      }
      func(file, rank);
    }
    if (optional == true) {
      break;
    }
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

  if (file < 0 || file > MAX_FILE) {
    return false;
  }

  if (rank < 0 || rank > MAX_RANK) {
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

void copyArray(Piece* destBoard[8][8], Piece* srcBoard[8][8])
{
  auto copyElement = [&](int rank, int file) {
    destBoard[file][rank] = srcBoard[file][rank];
  };
  forEachSquare(copyElement);
}

bool freePath(std::string srcSquare, std::string destSquare, Piece* board[8][8])
{
  int srcFile = fileToInt(srcSquare);
  int srcRank = rankToInt(srcSquare);
  int destFile = fileToInt(destSquare);
  int destRank = rankToInt(destSquare);

  // Values to add to current file / rank in while loop
  // (representing the 'direction' a piece is moving in)
  // Will be +1 if srcFile(or rank) is lower than dstFile(or rank);
  // -1 if greater than destFile(or rank); 0 if srcFile (or rank)
  // equals destFile (or rank)
  int fileValueChange = (srcFile == destFile)
      ? 0
      : abs(destFile - srcFile) / (destFile - srcFile);
  int rankValueChange = (srcRank == destRank)
      ? 0
      : abs(destRank - srcRank) / (destRank - srcRank);

  int currentFile = srcFile + fileValueChange;
  int currentRank = srcRank + rankValueChange;

  while (currentFile != destFile || currentRank != destRank) {
    if (board[currentFile][currentRank] != nullptr) {
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
  bool kingFound = false;
  bool inCheck = false;

  auto findKing = [&](int file, int rank) {
    if (board[file][rank] == nullptr) {
      return;
    }
    if (board[file][rank]->getType() != "King") {
      return;
    }
    if (board[file][rank]->getColour() == kingColour) {
      kingPosition = integersToSquare(file, rank);
      kingFound = true;
    }
  };
  // Adding bool 'kingFound' to forEachSquare() to ensure
  // for loops break as soon as we find the King
  forEachSquare(findKing, kingFound);

  auto tryKingAttack = [&](int file, int rank) {
    std::string currentSquare = integersToSquare(file, rank);
    if (board[file][rank] == nullptr) {
      return;
    }
    if (board[file][rank]->getColour() == kingColour) {
      return;
    }
    if (!board[file][rank]->validMove(currentSquare, kingPosition, board)) {
      return;
    }
    inCheck = true;
  };
  // Adding bool 'inCheck' to forEachSquare() to stop looping
  // if we know that King is in check
  forEachSquare(tryKingAttack, inCheck);

  return inCheck;
}

bool noValidMoves(std::string teamColour, Piece* board[8][8])
{
  std::string srcSquare;
  std::string destSquare;
  // Bool input to forEachSquare function must initially
  // be false, hence we set this to 'validMoves' and have
  // noValidMoves() return (!validMoves)
  bool validMoves = false;

  auto attemptMove = [&](int destFile, int destRank) {
    if (board[destFile][destRank] == nullptr) {
      destSquare = integersToSquare(destFile, destRank);
    } else if (board[destFile][destRank]->getColour() == teamColour) {
      return;
    } else {
      destSquare = integersToSquare(destFile, destRank);
    }

    int srcFile = fileToInt(srcSquare);
    int srcRank = rankToInt(srcSquare);
    if (!board[srcFile][srcRank]->validMove(srcSquare, destSquare, board)) {
      return;
    }

    Piece* tmpBoard[8][8];
    copyArray(tmpBoard, board);
    tmpBoard[destFile][destRank] = tmpBoard[srcFile][srcRank];
    tmpBoard[srcFile][srcRank] = nullptr;
    if (inCheck(teamColour, tmpBoard)) {
      return;
    }

    validMoves = true;
  };

  auto checkValidMove = [&](int srcFile, int srcRank) {
    if (board[srcFile][srcRank] == nullptr) {
      return;
    }
    if (board[srcFile][srcRank]->getColour() != teamColour) {
      return;
    }
    srcSquare = integersToSquare(srcFile, srcRank);

    forEachSquare(attemptMove, validMoves);
  };
  forEachSquare(checkValidMove, validMoves);

  return !validMoves;
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
  if (board[destFile][destRank] != nullptr) {
    std::cout << " taking " << board[destFile][destRank]->getColour() << "'s "
              << board[destFile][destRank]->getType();
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
  case GAME_OVER:
    std::cout << "Game has ended. Cannot submit more moves. Use resetBoard() "
                 "to start a new game"
              << std::endl;
    break;
  }
}