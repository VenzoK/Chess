#pragma once
#include "Board.h"
class Piece
{
public:
	virtual bool isLegalMove(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType) = 0;
	virtual bool IsPathClear(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType);
	virtual std::vector<std::pair<int, int>>GenerateLegalMoves(Board& value) = 0;
	bool MoveChessboardBoundsCheck(Board& value, int NewVerticalPosition, int NewHorizontalPosition);
	void move_piece(Board& value, int NewVerticalPosition, int NewHorizontalPosition, bool PlayerColor);
	void temp_move_piece(Board& value, int NewVerticalPosition, int NewHorizontalPosition);
	bool Get_OwnerColor();
	char Get_PieceKind();
	friend class Player;
	friend class Board;
protected:
	char PieceKind;
	char PieceChar; 
	int CurrentHorizontalPosition;
	int CurrentVerticalPosition;
	bool OwnerColor;
};