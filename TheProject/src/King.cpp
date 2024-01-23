#include <string>
#include <vector>
#include "Piece.h"
#include "Board.h"
#include "King.h"
	King::King(int CurrentVerticalPosition, int CurrentHorizontalPosition, bool OwnerColor)
	{
		this->CurrentHorizontalPosition = CurrentHorizontalPosition;
		this->CurrentVerticalPosition = CurrentVerticalPosition;
		this->OwnerColor = OwnerColor;
		this->PieceChar = OwnerColor ? KING_WHITE : KING_BLACK;
		this->PieceKind = 'K';
	}
	bool King::IsPathClear(Board& value,int NewVerticalPosition,int NewHorizontalPosition, char MoveType)
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
	bool King::isLegalMove(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType)
	{
		bool ChessboardBounds = MoveChessboardBoundsCheck(value, NewVerticalPosition, NewHorizontalPosition);
		if (!ChessboardBounds)
		{
			return false;
		}
		int VerticalOffset = abs(NewVerticalPosition - CurrentVerticalPosition);
		int HorizontalOffset = abs(NewHorizontalPosition - CurrentHorizontalPosition);
		if ((VerticalOffset == 1 || HorizontalOffset == 1) && (HorizontalOffset+VerticalOffset) <= 2)
		{
			return IsPathClear(value, NewVerticalPosition, NewHorizontalPosition, MoveType);
		}
			return false; // Illegal chess move

	}
	std::vector<std::pair<int, int>> King::GenerateLegalMoves(Board& value)
	{
		std::vector<std::pair<int, int>> legalMoves;
		int directions[][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} }; // right, left, down, up + 4 diagonals
		for (int dir = 0; dir < 8; ++dir)
		{
			int dVertical = directions[dir][0];
			int dHorizontal = directions[dir][1];

			int iterateVertical = CurrentVerticalPosition + dVertical;
			int iterateHorizontal = CurrentHorizontalPosition + dHorizontal;

			if (isLegalMove(value, iterateVertical, iterateHorizontal, '-'))
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