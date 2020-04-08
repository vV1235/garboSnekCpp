#pragma once
#include <string>

class ScoreBoard {
public:
	ScoreBoard() = delete;
	ScoreBoard(int r, int c);
	~ScoreBoard();
	std::string getName(int r_, int c_) const;
	//TODO score display on screen
	//wchar_t getScore(int r_, int c_) const;
	int getRow() const;
	int getCol() const;
	std::string getGameOverText() const;
private:
	struct Info {
		std::string name;
		short score;
	};
	int r;
	int c;
	Info** table;
	void aloc(int r, int c);
	const std::string gameOverText = "GAME OVER PRESS SPACE TO PLAY AGAIN";
};
