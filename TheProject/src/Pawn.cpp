#include <string>
#include <vector>
#include "Piece.h"
#include "Board.h"
#include "Pawn.h"
	Pawn::Pawn(int CurrentVerticalPosition, int CurrentHorizontalPosition, bool OwnerColor)
	{
		this->CurrentHorizontalPosition = CurrentHorizontalPosition;
		this->CurrentVerticalPosition = CurrentVerticalPosition;
		this->OwnerColor = OwnerColor;
		this->PieceChar = OwnerColor ? PAWN_WHITE : PAWN_BLACK;
		this->PieceKind = 'P';
	};
	bool Pawn::IsPathClear(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType)
	{
		int iteration_vertical = CurrentVerticalPosition;
		int iteration_horizontal = CurrentHorizontalPosition;

		switch (MoveType)
		{
		case '-': // move without capture
			if (value.boardmap[NewVerticalPosition][NewHorizontalPosition] != nullptr) 
			{
				return false; // Can't move to an occupied square
			}
			while (iteration_vertical != NewVerticalPosition || iteration_horizontal != NewHorizontalPosition)
			{
				iteration_vertical += (NewVerticalPosition > CurrentVerticalPosition) ? 1 : (NewVerticalPosition < CurrentVerticalPosition) ? -1 : 0;            // Determining whether the movement is towards the increse
				iteration_horizontal += (NewHorizontalPosition > CurrentHorizontalPosition) ? 1 : (NewHorizontalPosition < CurrentHorizontalPosition) ? -1 : 0;  // or decrease in position based on initial and final position	
				if (value.boardmap[iteration_vertical][iteration_horizontal] != nullptr)
				{
					return false; // The path is not clear
				}
			};
			return true;

		case 'x': // capture
			if (value.boardmap[NewVerticalPosition][NewHorizontalPosition] == nullptr)
			{
				return false; // The final position is not occupied
			}
			if (value.boardmap[NewVerticalPosition][NewHorizontalPosition]->Get_OwnerColor() == this->Get_OwnerColor())
			{
				return false; // Cannot capture your own piece
			}
			iteration_vertical += (NewVerticalPosition > CurrentVerticalPosition) ? 1 : (NewVerticalPosition < CurrentVerticalPosition) ? -1 : 0;
			iteration_horizontal += (NewHorizontalPosition > CurrentHorizontalPosition) ? 1 : (NewHorizontalPosition < CurrentHorizontalPosition) ? -1 : 0;
			if (value.boardmap[iteration_vertical][iteration_horizontal] == nullptr)
			{
				return false; // Checking the squares a pawn can capture
			}
			return true;

		default:
			return false;

		};
	};
	bool Pawn::isLegalMove(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType)
	{
		bool ChessboardBounds = MoveChessboardBoundsCheck(value, NewVerticalPosition, NewHorizontalPosition);
		if (!ChessboardBounds)
		{
			return false;
		}
		bool isMovingForward = ((NewVerticalPosition - CurrentVerticalPosition) > 0 && Get_OwnerColor() == true) || ((NewVerticalPosition - CurrentVerticalPosition) < 0 && Get_OwnerColor() == false);
		bool IsInRange = abs(NewVerticalPosition - CurrentVerticalPosition) <= 2;
		bool IsStraight = NewHorizontalPosition == CurrentHorizontalPosition;
		bool IsDiagonal = abs(NewVerticalPosition - CurrentVerticalPosition) == 1 && abs(NewHorizontalPosition - CurrentHorizontalPosition) == 1;
		bool IsFirstMove = ((CurrentVerticalPosition == 1 && Get_OwnerColor() == true) || (CurrentVerticalPosition == 6 && Get_OwnerColor() == false));

		switch (MoveType)
		{
		case '-':
			if (!IsFirstMove && abs(NewVerticalPosition - CurrentVerticalPosition) > 1)
			{
				return false;
			}
			if (isMovingForward && IsInRange && IsStraight) 
			{
				return IsPathClear(value, NewVerticalPosition, NewHorizontalPosition, MoveType);
			}
		case 'x':
			if (isMovingForward && IsDiagonal && IsInRange)
			{
				return IsPathClear(value, NewVerticalPosition, NewHorizontalPosition, MoveType);
			}
		default:
			return false;
		}

		return false; // Not a legal pawn move
	}
	std::vector<std::pair<int, int>> Pawn::GenerateLegalMoves(Board& value)
	{
		std::vector<std::pair<int, int>> legalMoves;
		int verticalDirection = value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition]->Get_OwnerColor() ? 1 : -1;
		bool IsFirstMove = ((CurrentVerticalPosition == 1 && Get_OwnerColor() == true) || (CurrentVerticalPosition == 6 && Get_OwnerColor() == false));
		int directions[][2] = { {verticalDirection, 0}, {verticalDirection, 1}, {verticalDirection, -1}, {verticalDirection*2, 0} };

		for (int dir = 0; dir < 4; dir++)
		{
			int dVertical = directions[dir][0];
			int dHorizontal = directions[dir][1];

			int iterateVertical = CurrentVerticalPosition + dVertical;
			int iterateHorizontal = CurrentHorizontalPosition + dHorizontal;

			if (isLegalMove(value, iterateVertical, iterateHorizontal, '-') && dHorizontal == 0)
			{
				legalMoves.emplace_back(iterateVertical, iterateHorizontal);
				continue;
			}
			if (isLegalMove(value, iterateVertical, iterateHorizontal, 'x') && (dHorizontal == 1 || dHorizontal == -1))
			{
				legalMoves.emplace_back(iterateVertical, iterateHorizontal);
				continue;
			}
			if (IsFirstMove)
			{
				iterateVertical += verticalDirection;
				IsFirstMove = false;
				if (isLegalMove(value, iterateVertical, iterateHorizontal, '-'))
				{
					legalMoves.emplace_back(iterateVertical, iterateHorizontal);
					continue;
				}
			}
		}
		return legalMoves;

	}