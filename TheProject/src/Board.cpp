#include <iostream>
#include <vector>
#include "Board.h"
#include "Constants.h"
#include "Piece.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
Board::Board()
{
	for (int i = 0; i < vertical; ++i)
	{
		for (int j = 0; j < horizontal; ++j)
		{
			boardmap[i][j] = nullptr;
		}
	}

	empty_board();
}
void Board::initialize_board()
{
	// White pieces 
	boardmap[0][0] = new Rook(0, 0, true);
	WhitePieces.push_back(boardmap[0][0]);

	boardmap[0][1] = new Knight(0, 1, true);
	WhitePieces.push_back(boardmap[0][1]);

	boardmap[0][2] = new Bishop(0, 2, true);
	WhitePieces.push_back(boardmap[0][2]);

	boardmap[0][3] = new King(0, 3, true);
	WhitePieces.push_back(boardmap[0][3]);

	boardmap[0][4] = new Queen(0, 4, true);
	WhitePieces.push_back(boardmap[0][4]);

	boardmap[0][5] = new Bishop(0, 5, true);
	WhitePieces.push_back(boardmap[0][5]);

	boardmap[0][6] = new Knight(0, 6, true);
	WhitePieces.push_back(boardmap[0][6]);

	boardmap[0][7] = new Rook(0, 7, true);
	WhitePieces.push_back(boardmap[0][7]);
	
	// Black pieces
	boardmap[7][0] = new Rook(7, 0, false);
	BlackPieces.push_back(boardmap[7][0]);

	boardmap[7][1] = new Knight(7, 1, false);
	BlackPieces.push_back(boardmap[7][1]);

	boardmap[7][2] = new Bishop(7, 2, false);
	BlackPieces.push_back(boardmap[7][2]);

	boardmap[7][3] = new King(7, 3, false);
	BlackPieces.push_back(boardmap[7][3]);

	boardmap[7][4] = new Queen(7, 4, false);
	BlackPieces.push_back(boardmap[7][4]);

	boardmap[7][5] = new Bishop(7, 5, false);
	BlackPieces.push_back(boardmap[7][5]);

	boardmap[7][6] = new Knight(7, 6, false);
	BlackPieces.push_back(boardmap[7][6]);

	boardmap[7][7] = new Rook(7, 7, false);
	BlackPieces.push_back(boardmap[7][7]);

	
	// White pawns
	for (int j = 0; j < horizontal; j++)
	{
		boardmap[1][j] = new Pawn(1, j, true);
		WhitePieces.push_back(boardmap[1][j]);
	}
	
	// Black pawns
	for (int j = 0; j < horizontal; j++)
	{
		boardmap[6][j] = new Pawn(6, j, false);
		BlackPieces.push_back(boardmap[6][j]);
	}

	 WhiteKing = boardmap[0][3];
	 BlackKing = boardmap[7][3];
}
	void Board::show_board()
	{
		std::cout << "  -----------------" << std::endl;
		for (int i = 0; i < vertical; i++)
		{
			std::cout << i + 1;
			std::cout << "| ";
			for (int j = 0; j < horizontal; j++)
			{
				std::cout << boardview[i][j] << ' ';
			};
			std::cout << "|" << std::endl;
		};
		std::cout << "  -----------------" << std::endl;
		std::cout << "   h g f e d c b a" << std::endl;
	}
	void Board::reset_board()
	{

		for (int i = 0; i < vertical; i++)
		{
			for (int j = 0; j < horizontal; j++)
			{
				boardview[i][j] = defaultboard[i][j];
			}
		}
	}

	void Board::empty_board()
	{
		for (int i = 0; i < vertical; i++)
		{
			for (int j = 0; j < horizontal; j++)
			{
				boardview[i][j] = emptyboard[i][j];
			}
		}
	}
	char Board::CurrentSquareColor(int CurrentVerticalPosition, int CurrentHorizontalPosition)
	{
		return ((CurrentVerticalPosition + CurrentHorizontalPosition) % 2 == 0) ? EMPTY_WHITE : EMPTY_BLACK;
	}