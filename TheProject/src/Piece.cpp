#include <iostream>
#include <string>
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

bool Piece::MoveChessboardBoundsCheck(Board& value, int NewVerticalPosition, int NewHorizontalPosition)
{
	// chessboard bounds 
	if (NewVerticalPosition < 0 || NewVerticalPosition >= vertical ||
		NewHorizontalPosition < 0 || NewHorizontalPosition >= horizontal)
	{
		return false;
	}
	return true;
}
bool Piece::IsPathClear(Board & value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType) 
{
	int iteration_vertical = CurrentVerticalPosition;
	int iteration_horizontal = CurrentHorizontalPosition;
	int dVertical = (NewVerticalPosition > CurrentVerticalPosition) ? 1 : ((NewVerticalPosition < CurrentVerticalPosition) ? -1 : 0);          // Determining whether the movement is towards the increse
	int dHorizontal = (NewHorizontalPosition > CurrentHorizontalPosition) ? 1 : (NewHorizontalPosition < CurrentHorizontalPosition) ? -1 : 0; // or decrease in position based on initial and final position
	switch (MoveType)
	{
	case '-': // move without capture

		if(value.boardmap[NewVerticalPosition][NewHorizontalPosition] != nullptr)
		{
			return false; // Can't move to an occupied square
		}

		while(iteration_vertical != NewVerticalPosition || iteration_horizontal != NewHorizontalPosition)
		{
			iteration_vertical += dVertical;            
			iteration_horizontal += dHorizontal;

			if (value.boardmap[iteration_vertical][iteration_horizontal] != nullptr)
			{
				return false; // The path is not clear
			}
		}
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

		while (iteration_vertical != NewVerticalPosition - dVertical || iteration_horizontal != NewHorizontalPosition - dHorizontal)
		{
			iteration_vertical += dVertical;
			iteration_horizontal += dHorizontal;

			if (value.boardmap[iteration_vertical][iteration_horizontal] != nullptr)
			{
				return false; // The path is not clear 
			}
		}

		return true;
	default:
		return false;
	};
};
	void Piece::move_piece(Board& value, int NewVerticalPosition, int NewHorizontalPosition, bool PlayerColor)
	{
		char SquareColor = value.CurrentSquareColor(CurrentVerticalPosition, CurrentHorizontalPosition);
		value.boardview[CurrentVerticalPosition][CurrentHorizontalPosition] = SquareColor;

		// Initial square
		Piece* MovedPiece = value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition];
	    value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition] = nullptr;

		// Update of coordinates
		CurrentHorizontalPosition = NewHorizontalPosition;
		CurrentVerticalPosition = NewVerticalPosition;

		// Final square
		if (value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition] != nullptr)
		{

			Piece* TakenPiece = value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition];

			// Removing piece from a vector that contains all pieces of a certain color
			if (!PlayerColor) // Iterate through BlackPieces if PlayerColor == 1 (iterating through enemy pieces)
			{
				auto it = std::find(value.WhitePieces.begin(), value.WhitePieces.end(), TakenPiece);

				if (it != value.WhitePieces.end())
				{
					value.WhitePieces.erase(it);
				}
			}
			else // else iterate through WhitePieces if PlayerColor == 0 (iterating through enemy pieces)
			{
				auto it = std::find(value.BlackPieces.begin(), value.BlackPieces.end(), TakenPiece);
				
				if (it != value.BlackPieces.end())
				{
					value.BlackPieces.erase(it);
				}
			}

			delete TakenPiece;
			value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition] = nullptr;
		}
		
		value.boardview[CurrentVerticalPosition][CurrentHorizontalPosition] = PieceChar;
		value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition] = MovedPiece;


	}
	void Piece::temp_move_piece(Board& value, int NewVerticalPosition, int NewHorizontalPosition)
	{
		char SquareColor = value.CurrentSquareColor(CurrentVerticalPosition, CurrentHorizontalPosition);

		// Initial square
		Piece* MovedPiece = value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition];
		value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition] = nullptr;
		value.boardview[CurrentVerticalPosition][CurrentHorizontalPosition] = SquareColor;


		// Update of coordinates
		CurrentHorizontalPosition = NewHorizontalPosition; 
		CurrentVerticalPosition = NewVerticalPosition;

		// Final square
		value.boardmap[CurrentVerticalPosition][CurrentHorizontalPosition] = MovedPiece;
		value.boardview[CurrentVerticalPosition][CurrentHorizontalPosition] = PieceChar;

	}
	bool Piece::Get_OwnerColor()
	{
		return OwnerColor;
	}
	char Piece::Get_PieceKind()
	{
		return PieceKind;
	}
