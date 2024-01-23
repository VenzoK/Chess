#include <string>
#include <vector>
#include "Piece.h"
#include "Board.h"
#include "Queen.h"
Queen::Queen(int CurrentVerticalPosition, int CurrentHorizontalPosition, bool OwnerColor)
{
	this->CurrentHorizontalPosition = CurrentHorizontalPosition;
	this->CurrentVerticalPosition = CurrentVerticalPosition;
	this->OwnerColor = OwnerColor;
	this->PieceChar = OwnerColor ? QUEEN_WHITE : QUEEN_BLACK;
	this->PieceKind = 'Q';
};
	bool Queen::isLegalMove(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType)
	{
		bool ChessboardBounds = MoveChessboardBoundsCheck(value, NewVerticalPosition, NewHorizontalPosition);
		if (!ChessboardBounds)
		{
			return false;
		}
		bool isDiagonal = (abs(NewVerticalPosition - CurrentVerticalPosition) == abs(NewHorizontalPosition - CurrentHorizontalPosition));
		bool isVertical = NewHorizontalPosition == CurrentHorizontalPosition;
		bool isHorizontal = NewVerticalPosition == CurrentVerticalPosition;
		if (abs(NewVerticalPosition - CurrentVerticalPosition) == 0 && abs(NewHorizontalPosition - CurrentHorizontalPosition == 0))
		{
			return false;
		}
		if (isDiagonal || isVertical || isHorizontal)
		{
			return IsPathClear(value, NewVerticalPosition, NewHorizontalPosition, MoveType);
		};
		return false;  // Not a diagonal, vertical or horizontal move
		
	} 
	std::vector<std::pair<int, int>> Queen::GenerateLegalMoves(Board& value)
	{
		std::vector<std::pair<int, int>> legalMoves;
		int directions[][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} }; // right, left, down, up + 4 diagonals
		for (int dir = 0; dir < 8; ++dir)
		{
			int dVertical = directions[dir][0];
			int dHorizontal = directions[dir][1];

			int iterateVertical = CurrentVerticalPosition + dVertical;
			int iterateHorizontal = CurrentHorizontalPosition + dHorizontal;

			while (isLegalMove(value, iterateVertical, iterateHorizontal, '-'))
			{
				legalMoves.emplace_back(iterateVertical, iterateHorizontal);
				iterateVertical += dVertical;
				iterateHorizontal += dHorizontal;
			}

			while (isLegalMove(value, iterateVertical, iterateHorizontal, 'x'))
			{
				legalMoves.emplace_back(iterateVertical, iterateHorizontal);
				break;
			}
		}
		return legalMoves;

	}