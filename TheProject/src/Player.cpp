#include <iostream>
#include <string>
#include "Board.h"
#include "Player.h"
#include "Piece.h"

Player::Player(std::string name, bool PlayerColor)
{
	PlayerName = name;
	this->PlayerColor = PlayerColor;
}
bool Player::IsInCheck(Board& value, bool PlayerColor)
{

	checkingPieces.clear();
	Piece* King = PlayerColor ? value.WhiteKing : value.BlackKing;
	int KingVerticalPosition = King->CurrentVerticalPosition;
	int KingHorizontalPosition = King->CurrentHorizontalPosition;

	for (auto pieces : (PlayerColor ? value.BlackPieces : value.WhitePieces)) 
	{


		if (pieces->isLegalMove(value, KingVerticalPosition, KingHorizontalPosition, 'x')) // Checking if you can capture the king
		{
			if (std::find(checkingPieces.begin(), checkingPieces.end(), pieces) == checkingPieces.end())
			{
				checkingPieces.push_back(pieces); // needed to prevent it from moving in IsCheckmated function
			}
		}

	}
	if (checkingPieces.empty())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Player::IsCheckmated(Board& value, bool PlayerColor)
{
	std::vector<Piece*> AllPieces;
	AllPieces.reserve(value.BlackPieces.size() + value.WhitePieces.size());
	AllPieces.insert(AllPieces.end(), value.BlackPieces.begin(), value.BlackPieces.end());
	AllPieces.insert(AllPieces.end(), value.WhitePieces.begin(), value.WhitePieces.end());

	Piece* capturedPiece = nullptr;
	char capturedPieceNotation;
		
	// iterating through all the pieces on the board
	for (auto pieces : AllPieces)
	{

		if (std::find(checkingPieces.begin(), checkingPieces.end(), pieces) != checkingPieces.end())
		{
			continue;  // skips the pieces that give the check
		}

		auto legalMoves = pieces->GenerateLegalMoves(value);

		if (legalMoves.empty())
		{
			continue;
		}

		int originalHorizontalPosition = pieces->CurrentHorizontalPosition;
		int originalVerticalPosition = pieces->CurrentVerticalPosition;

		for (auto move : legalMoves)
		{
			if (value.boardmap[move.first][move.second] != nullptr) // moves.first is the vertical component of the move, moves.second is the horizontal component
			{
				// Needed to revert the captured piece
				capturedPiece = value.boardmap[move.first][move.second]; 
				capturedPieceNotation = value.boardmap[move.first][move.second]->PieceChar;
			}
			else
			{
				capturedPiece = nullptr;
				capturedPieceNotation = value.CurrentSquareColor(move.first, move.second);
			}

			pieces->temp_move_piece(value, move.first, move.second); // moves.first is the vertical component of the move, moves.second is the horizontal component

			// Checking if making a move doesn't get you in check
			if (!IsInCheck(value, PlayerColor))
			{
				// revert the move 
				pieces->temp_move_piece(value, originalVerticalPosition, originalHorizontalPosition);
				value.boardmap[move.first][move.second] = capturedPiece;
				value.boardview[move.first][move.second] = capturedPieceNotation;

				return false; // there are legal moves that get you out of the check
			}

				// revert the move 
				pieces->temp_move_piece(value, originalVerticalPosition, originalHorizontalPosition);
				value.boardmap[move.first][move.second] = capturedPiece;
				value.boardview[move.first][move.second] = capturedPieceNotation;


		}
	}
	
	 return true;
}

bool Player::IsStalemate(Board& value) // doesn't work
{
	Piece* capturedPiece = nullptr;
	char capturedPieceNotation;
	bool PlayerColor = true; // White player
	bool BlackPlayerStalemate = true;
	bool WhitePlayerStalemate = true;

	// iterating through white pieces on the board
	for (auto pieces : value.WhitePieces)
	{

		auto legalMoves = pieces->GenerateLegalMoves(value);

		if (legalMoves.empty())
		{
			continue;
		}

		int originalHorizontalPosition = pieces->CurrentHorizontalPosition;
		int originalVerticalPosition = pieces->CurrentVerticalPosition;

		for (auto move : legalMoves)
		{
			if (value.boardmap[move.first][move.second] != nullptr) // moves.first is the vertical component of the move, moves.second is the horizontal component
			{
				// Needed to revert the captured piece
				capturedPiece = value.boardmap[move.first][move.second];
				capturedPieceNotation = value.boardmap[move.first][move.second]->PieceChar;
			}
			else
			{
				capturedPiece = nullptr;
				capturedPieceNotation = value.CurrentSquareColor(move.first, move.second);
			}

			pieces->temp_move_piece(value, move.first, move.second); // moves.first is the vertical component of the move, moves.second is the horizontal component

			// Checking if making a move doesn't get you in check
			if (!IsInCheck(value, PlayerColor))
			{
				// revert the move 
				pieces->temp_move_piece(value, originalVerticalPosition, originalHorizontalPosition);
				value.boardmap[move.first][move.second] = capturedPiece;
				value.boardview[move.first][move.second] = capturedPieceNotation;

				WhitePlayerStalemate = false; // there are legal moves 
				break;
			}

			// revert the move 
			pieces->temp_move_piece(value, originalVerticalPosition, originalHorizontalPosition);
			value.boardmap[move.first][move.second] = capturedPiece;
			value.boardview[move.first][move.second] = capturedPieceNotation;


		}
	}

	// iterating through black pieces on the board
	for (auto pieces : value.BlackPieces)
	{
		bool PlayerColor = false; // Black player
		auto legalMoves = pieces->GenerateLegalMoves(value);

		if (legalMoves.empty())
		{
			continue;
		}

		int originalHorizontalPosition = pieces->CurrentHorizontalPosition;
		int originalVerticalPosition = pieces->CurrentVerticalPosition;

		for (auto move : legalMoves)
		{
			if (value.boardmap[move.first][move.second] != nullptr) // moves.first is the vertical component of the move, moves.second is the horizontal component
			{
				// Needed to revert the captured piece
				capturedPiece = value.boardmap[move.first][move.second];
				capturedPieceNotation = value.boardmap[move.first][move.second]->PieceChar;
			}
			else
			{
				capturedPiece = nullptr;
				capturedPieceNotation = value.CurrentSquareColor(move.first, move.second);
			}

			pieces->temp_move_piece(value, move.first, move.second); // moves.first is the vertical component of the move, moves.second is the horizontal component

			// Checking if making a move doesn't get you in check
			if (!IsInCheck(value, PlayerColor))
			{
				// revert the move 
				pieces->temp_move_piece(value, originalVerticalPosition, originalHorizontalPosition);
				value.boardmap[move.first][move.second] = capturedPiece;
				value.boardview[move.first][move.second] = capturedPieceNotation;

				BlackPlayerStalemate = false;  // there are legal moves 
				break;
			}

			// revert the move 
			pieces->temp_move_piece(value, originalVerticalPosition, originalHorizontalPosition);
			value.boardmap[move.first][move.second] = capturedPiece;
			value.boardview[move.first][move.second] = capturedPieceNotation;


		}
	}

	return (BlackPlayerStalemate || WhitePlayerStalemate);
}

void Player::TakeTurn(bool PlayerColor, Board& value)
{
	bool isValidMove = false;
	std::cout << "Enter " << PlayerName << "s move." << std::endl;
	while (!isValidMove)
	{
		try
		{
			std::string movenotation;
			std::cin >> movenotation;
			
			// Checking the length of the movenotation
			if (movenotation.length() != 6)
			{
				throw std::invalid_argument("Invalid chess notation length.");
			}

			// Decoding the movenotation into actual values
			int InitialHorizontalPosition = moves[movenotation[1]];
			int InitialVerticalPosition = movenotation[2] - '1';
			int NewHorizontalPosition = moves[movenotation[4]];
			int NewVerticalPosition = movenotation[5] - '1';
			char MoveType = movenotation[3];
			char firstChar = movenotation[0];

			// Checking if movenotation[0] is a valid chess piece notation
			if (firstChar != 'B' && firstChar != 'K' && firstChar != 'N' &&
				firstChar != 'Q' && firstChar != 'P' && firstChar != 'R')
			{
				throw std::invalid_argument("Invalid chess piece notation.");
			}

			// Checking if the notation is out of chessboard bounds
			if (InitialHorizontalPosition >= horizontal || InitialVerticalPosition >= vertical)
			{
				throw std::invalid_argument("Out of bounds notation");
			}

			Piece* CurrentPiece = value.boardmap[InitialVerticalPosition][InitialHorizontalPosition];

			if (CurrentPiece == nullptr)
			{
				throw std::logic_error("This is not a piece.");
			}

			// Checking if the initial position of the piece matches 
			if (CurrentPiece->CurrentHorizontalPosition != InitialHorizontalPosition || CurrentPiece->CurrentVerticalPosition != InitialVerticalPosition)
			{
				throw std::logic_error("Invalid initial position.");
			}

			// Checking if the piece symbol matches
			if (CurrentPiece->PieceKind != movenotation[0])
			{
				throw std::logic_error("Invalid piece type selection.");
			}

			if (CurrentPiece->OwnerColor != PlayerColor)
			{
				throw std::logic_error("This is not your piece.");
			}

			// Legality of the move
			if (CurrentPiece->isLegalMove(value, NewVerticalPosition, NewHorizontalPosition, MoveType) == false)
			{
				throw std::logic_error("Not a legal chess move.");
			}

			// Making the move 
			CurrentPiece->move_piece(value, NewVerticalPosition, NewHorizontalPosition, PlayerColor);

			// Checking if you are checked after moving
			if (IsInCheck(value, PlayerColor))
			{
				throw std::logic_error("Your king is checked.");
			}

			isValidMove = true;
			std::cout << PlayerName << " moved from " << std::string(1, movenotation[1]) + std::string(1, movenotation[2]) << " to " << std::string(1, movenotation[4]) + std::string(1, movenotation[5]) << "\n";
			value.show_board();
		}

		catch (const std::exception& InvalidNotation)
		{
			std::cerr << "Exception caught: " << InvalidNotation.what() << std::endl;
			std::cout << "Please enter a valid move notation: ";

			
		}

		catch (const std::logic_error& InvalidPieceSelection)
		{
			std::cerr << "Exception caught: " << InvalidPieceSelection.what() << std::endl;
			std::cout << "Please choose a valid piece of your color: ";
		}
	}
}



