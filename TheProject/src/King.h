#pragma once
class King : public Piece
{
public:
	King(int CurrentVerticalPosition, int CurrentHorizontalPosition, bool OwnerColor);
private:
	bool isLegalMove(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType) override;
	bool IsPathClear(Board& value, int NewVerticalPosition, int NewHorizontalPosition, char MoveType) override;
	std::vector<std::pair<int, int>>GenerateLegalMoves(Board& value) override;

};