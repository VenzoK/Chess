#include <iostream>
#include <string>
#include <map>
#include "Board.h"
#include "Player.h"
#include "Piece.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"
Piece* CreatePiece(char piece, int CurrentVerticalPosition, int CurrentHorizontalPosition, bool OwnerColor)
{
	switch (piece)
	{
	case 'B':
		return new Bishop(CurrentVerticalPosition, CurrentHorizontalPosition, OwnerColor);
	case 'R':
		return new Rook(CurrentVerticalPosition, CurrentHorizontalPosition, OwnerColor);
	case 'N':
		return new Knight(CurrentVerticalPosition, CurrentHorizontalPosition, OwnerColor);
	case 'Q':
		return new Queen(CurrentVerticalPosition, CurrentHorizontalPosition, OwnerColor);
	case 'K':
		return new King(CurrentVerticalPosition, CurrentHorizontalPosition, OwnerColor);
	case 'P':
		return new Pawn(CurrentVerticalPosition, CurrentHorizontalPosition, OwnerColor);
	}
}
	void StartGame(std::string WhitePlayerName, std::string BlackPlayerName)
	{
		Board board;
		board.initialize_board();
		board.reset_board();
		Player WhitePlayer(WhitePlayerName, true);
		Player BlackPlayer(BlackPlayerName, false);
		board.show_board();
		while (!WhitePlayer.checkmate && !BlackPlayer.checkmate)
		{

			WhitePlayer.TakeTurn(true, board);


			if (BlackPlayer.IsInCheck(board, BlackPlayer.PlayerColor))
			{
				if (BlackPlayer.IsCheckmated(board, BlackPlayer.PlayerColor))
				{
					BlackPlayer.checkmate = true;
					std::cout << "Game is over. " << WhitePlayerName << " won the game.";
					return;
				}
				else
				{
					std::cout << BlackPlayerName << " is in check." << "\n";
				}
			}
			if (BlackPlayer.IsStalemate(board))
			{
				std::cout << "Game is over. It's stalemate.";
				return;
			}
			BlackPlayer.TakeTurn(false, board);


			if (WhitePlayer.IsInCheck(board, WhitePlayer.PlayerColor))
			{
				if (WhitePlayer.IsCheckmated(board, WhitePlayer.PlayerColor))
				{
					WhitePlayer.checkmate = true;
					std::cout << "Game is over. " << BlackPlayerName << " won the game.";
					return;
				}
				else
				{
					std::cout << WhitePlayerName << " is in check." << "\n";
				}
			}
			if (WhitePlayer.IsStalemate(board))
			{
				std::cout << "Game is over. It's stalemate.";
				return;
			}


		}


	}

	int main(void)
	{
		std::string WhitePlayerName;
		std::string BlackPlayerName;
		std::cout << "Enter white players name:";
		std::cin >> WhitePlayerName;
		std::cout << "Enter black players name:";
		std::cin >> BlackPlayerName;
		std::cout << "The moves should be of the next form without spaces: first letter of the piece, square where it moves from, square where to moves to." << std::endl;
	    StartGame(WhitePlayerName, BlackPlayerName);


		return 0;
	}

