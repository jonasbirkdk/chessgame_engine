#pragma once

// Global constants
#define TOTAL_PIECES 12
#define PIECES_PER_TEAM 6

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