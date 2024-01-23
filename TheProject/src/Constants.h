#pragma once
#include <map>
#define vertical 8
#define horizontal 8
#define EMPTY_BLACK  '#'//'□'
#define EMPTY_WHITE  ' '//'■'
#define KNIGHT_BLACK 'n'//'♞'
#define KNIGHT_WHITE 'N' //'♘' 
#define BISHOP_WHITE 'B' // '♗'
#define BISHOP_BLACK 'b' // '♝'
#define KING_WHITE 'K' // '♚'
#define KING_BLACK 'k' // '♚'
#define QUEEN_WHITE 'Q' // '♕'
#define QUEEN_BLACK 'q' // '♛'
#define ROOK_WHITE 'R' // '♖'
#define ROOK_BLACK 'r' // '♜'
#define PAWN_WHITE 'P' //'♙'
#define PAWN_BLACK 'p' // '♟'
  static std::map<char, int> moves = {
	{'h', 0}, {'g', 1}, {'f', 2}, {'e', 3}, {'d', 4}, {'c', 5}, {'b', 6}, {'a', 7} };