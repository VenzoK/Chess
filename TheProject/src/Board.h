#pragma once
#include <vector>
#include "Constants.h"
class Board
{
public:
	Board();
	void show_board();
	void reset_board();
	void initialize_board();
	void empty_board();
	char CurrentSquareColor(int CurrentVerticalPosition, int CurrentHorizontalPosition);
	friend class Knight;
	friend class Bishop;
	friend class Rook;
	friend class King;
	friend class Queen;
	friend class Pawn;
	friend class Piece;
	friend class Player;
private:
	const char defaultboard[vertical][horizontal] = { {ROOK_WHITE, KNIGHT_WHITE, BISHOP_WHITE, KING_WHITE, QUEEN_WHITE, BISHOP_WHITE, KNIGHT_WHITE, ROOK_WHITE},
										  {PAWN_WHITE,PAWN_WHITE,PAWN_WHITE,PAWN_WHITE,PAWN_WHITE,PAWN_WHITE,PAWN_WHITE,PAWN_WHITE },
										  {EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK},
										  {EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK, EMPTY_WHITE},
										  {EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK},
										  {EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK,EMPTY_WHITE,EMPTY_BLACK, EMPTY_WHITE},
										  {PAWN_BLACK,PAWN_BLACK,PAWN_BLACK,PAWN_BLACK,PAWN_BLACK,PAWN_BLACK,PAWN_BLACK,PAWN_BLACK},
										  {ROOK_BLACK, KNIGHT_BLACK, BISHOP_BLACK, KING_BLACK, QUEEN_BLACK, BISHOP_BLACK, KNIGHT_BLACK, ROOK_BLACK} };

	/*{{'♜','♞','♝','♛','♚','♝','♞','♜'},
	   {'♟','♟','♟','♟','♟','♟','♟','♟'},
	   {'□','■','□','■','□','■','□','■'},
	   {'■','□','■','□','■','□','■','□'},
	   {'□','■','□','■','□','■','□','■'},
	   {'■','□','■','□','■','□','■','□'},
	   {'♙','♙','♙','♙','♙','♙','♙','♙'},
	   {'♖','♘','♗','♕','♚','♗','♘','♖'} }; */
	const char emptyboard[vertical][horizontal] = { {EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK},
													 {EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE},
													 {EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK},
													 {EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE},
													 {EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK},
													 {EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE},
													 {EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK},
													 {EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE, EMPTY_BLACK, EMPTY_WHITE} };
	/* {'□','■','□','■','□','■','□','■'},
	   {'■','□','■','□','■','□','■','□'},
	   {'□','■','□','■','□','■','□','■'},
	   {'■','□','■','□','■','□','■','□'},
	   {'□','■','□','■','□','■','□','■'},
	   {'■','□','■','□','■','□','■','□'},
	   {'□','■','□','■','□','■','□','■'},
	   {'■','□','■','□','■','□','■','□'},*/
protected:
	char boardview[vertical][horizontal];
	Piece* boardmap[vertical][horizontal];
	std::vector<Piece*> WhitePieces;
	std::vector<Piece*> BlackPieces;
	int WhiteKingVerticalPosition = 0;    // Initial white king vertical position  
	int WhiteKingHorizontalPosition = 3;  // Initial white king horizontal position
	int BlackKingVerticalPosition = 7;    // Initial black king vertical position
	int BlackKingHorizontalPosition = 3;  // Initial black king horizontal position
	Piece* WhiteKing = NULL;
	Piece* BlackKing = NULL;

};