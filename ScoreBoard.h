#pragma once
#include <string>

class ScoreBoard {
	friend class Game;
public:
	//Default constructor simulates having 5 previous players since no general way of keeping score is implemented atm
	ScoreBoard();
	//This constructor ought to be used later on after implementing saving the scoreboard state to file
	//ScoreBoard(int size_);
	~ScoreBoard();
	
	std::string getName(int index_) const;
	int getScore(int index_) const;
	int getPlayerCnt() const;
	int getMaxPlayerCnt() const;
	std::string getGameOverText() const;
private:
	void addNewPlayerToTable();
	void popLastPlayer();
	struct Info {
		std::string name;
		int score;
	};
	Info** table;

	const std::string gameOverText = "GAME OVER PRESS SPACE TO PLAY AGAIN";
	int playerCnt;
	const int maxPlayerCnt = 10;

	void alocTable();
	void simTablePlayers();
	void clearTable();
};
