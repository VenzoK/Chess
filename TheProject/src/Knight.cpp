#include <string>
#include <vector>
#include "Piece.h"
#include "Knight.h"
	Knight::Knight(int CurrentVerticalPosition, int CurrentHorizontalPosition, bool OwnerColor)
	{
		this->CurrentHorizontalPosition = CurrentHorizontalPosition;
		this->CurrentVerticalPosition = CurrentVerticalPosition;
		this->OwnerColor = OwnerColor;
		this->PieceChar = OwnerColor ? KNIGHT_WHITE : KNIGHT_BLACK;
		this->PieceKind = 'N';
	}
	bool Knight::isLegalMove(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType)
	{
		bool ChessboardBounds = MoveChessboardBoundsCheck(value, NewVerticalPosition, NewHorizontalPosition);
		if (!ChessboardBounds)
		{
			return false;
		}
		bool isSum = abs(NewHorizontalPosition - CurrentHorizontalPosition) + abs(NewVerticalPosition - CurrentVerticalPosition) == 3;
		bool isHorizontalZero = abs(NewHorizontalPosition - CurrentHorizontalPosition) != 0;
		bool isVerticalZero = abs(NewVerticalPosition - CurrentVerticalPosition) != 0;
		if (isVerticalZero && isHorizontalZero && isSum)
		{
			switch (MoveType)
			{
			case '-':
				if (value.boardmap[NewVerticalPosition][NewHorizontalPosition] != nullptr)
				{
					return false;
				}
				return true;
			case 'x':
				if (value.boardmap[NewVerticalPosition][NewHorizontalPosition] == nullptr)
				{
					return false;
				}
				if (value.boardmap[NewVerticalPosition][NewHorizontalPosition]->Get_OwnerColor() == this->Get_OwnerColor())
				{
					return false;
				}
				return true;
			default:
				return false;
			}
		}
		return false;

	}
	std::vector<std::pair<int, int>> Knight::GenerateLegalMoves(Board& value)
	{
		std::vector<std::pair<int, int>> legalMoves;
		int directions[][2] = { {-1, 2}, {1, 2}, {-1, -2}, {1, -2}, {-2, 1}, {2, -1}, {-2, -1}, {2, 1} }; // knight moves
		for (int dir = 0; dir < 8; ++dir)
		{
			int dVertical = directions[dir][0];
			int dHorizontal = directions[dir][1];

			int iterateVertical = CurrentVerticalPosition + dVertical;
			int iterateHorizontal = CurrentHorizontalPosition + dHorizontal;

			if(isLegalMove(value, iterateVertical, iterateHorizontal, '-'))
			{
			    legalMoves.emplace_back(iterateVertical, iterateHorizontal);
			}
			if (isLegalMove(value, iterateVertical, iterateHorizontal, 'x'))
			{
				legalMoves.emplace_back(iterateVertical, iterateHorizontal);
			}
		}
		return legalMoves;

	}