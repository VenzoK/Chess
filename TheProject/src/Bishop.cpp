	#include <string>
	#include <vector>
	#include "Piece.h"
	#include "Bishop.h"

		Bishop::Bishop(int CurrentVerticalPosition, int CurrentHorizontalPosition, bool OwnerColor)
		{
			this->CurrentHorizontalPosition = CurrentHorizontalPosition;
			this->CurrentVerticalPosition = CurrentVerticalPosition;
			this->OwnerColor = OwnerColor;
			this->PieceChar = OwnerColor ? BISHOP_WHITE : BISHOP_BLACK;
			this->PieceKind = 'B';
		};
		bool Bishop::isLegalMove(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType)
		{
			bool ChessboardBounds = MoveChessboardBoundsCheck(value, NewVerticalPosition, NewHorizontalPosition);
			if (!ChessboardBounds)
			{
				return false;
			}
			bool isDiagonal = (abs(NewVerticalPosition - CurrentVerticalPosition) == abs(NewHorizontalPosition - CurrentHorizontalPosition));
			if (abs(NewVerticalPosition - CurrentVerticalPosition) == 0 && abs(NewHorizontalPosition - CurrentHorizontalPosition == 0))
			{
				return false;
			}
			if (isDiagonal)
			{
				return IsPathClear(value, NewVerticalPosition, NewHorizontalPosition, MoveType);
			}
			return false; // Not a diagonal move
		}
		std::vector<std::pair<int, int>> Bishop::GenerateLegalMoves(Board& value)
		{
			std::vector<std::pair<int, int>> legalMoves;
			int directions[][2] = { {1, 1}, {1, -1}, {-1, 1}, {-1, -1} }; //  4 diagonals
			for (int dir = 0; dir < 4; ++dir)
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