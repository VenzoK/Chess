#pragma once
#include <string>
#include <vector>
class Player
{
public:
	Player(std::string name, bool PlayerColor);
	void TakeTurn(bool PlayerColor, Board& value);
	bool IsInCheck(Board& value, bool PlayerColor);
	bool IsCheckmated(Board& value, bool PlayerColor);
	bool IsStalemate(Board& value);
	friend void StartGame(std::string WhitePlayerName, std::string BlackPlayerName);
private:
	std::string PlayerName;
	bool PlayerColor; // 1 for white, 0 for black

protected:
	bool checkmate = false;
	bool check = false;
	std::vector<Piece*> checkingPieces;

};