#pragma once

// Global constants
#define MAX_FILE 7
#define MAX_RANK 7

// Starting positions for pieces
#define CASTLE 0
#define KNIGHT 1
#define BISHOP 2
#define QUEEN 3
#define KING 4
#define PAWN 5

// Error codes
#define INVALID_INPUT 0
#define EMPTY_SOURCE_SQUARE 1
#define OWN_KING_IN_CHECK 2
#define NOT_YOUR_TURN 3
#define FRIENDLY_FIRE 4
#define PIECE_RULES_BROKEN 5
#define GAME_OVER 6
#define NO_MOVE 7
#define INVALID_CASTLING 8