#include "ScoreBoard.h"

ScoreBoard::ScoreBoard() : 
	playerCnt { 5 }
{
	alocTable();
	simTablePlayers();
}

//ScoreBoard::ScoreBoard(int size_) : 
//	size{ size_ } 
//{
//	//More explicit in terms of what it does
//	alocTable();
//}

ScoreBoard::~ScoreBoard() {
	clearTable();
}

int ScoreBoard::getPlayerCnt() const {
	return playerCnt;
}

std::string ScoreBoard::getGameOverText() const {
	return gameOverText;
}

int ScoreBoard::getMaxPlayerCnt() const {
	return maxPlayerCnt;
}

std::string ScoreBoard::getName(int index_) const {
	return this->table[index_]->name;
}

int ScoreBoard::getScore(int index_) const {
	return this->table[index_]->score;
}

void ScoreBoard::alocTable() {
	table = new Info * [playerCnt];
	for(int i = 0; i < playerCnt; i++) {
		table[i] = new Info;
	}
}

void ScoreBoard::simTablePlayers() {
	for(int i = 0; i < playerCnt; i++) {
		table[i]->name = "player" + std::to_string(i + 1);
		table[i]->score = i + 6;
	}
}

void ScoreBoard::addNewPlayerToTable() {
	Info** tmpTable = new Info*[playerCnt + 1];
	for(int i = 0; i < playerCnt + 1; i++) {
		tmpTable[i] = new Info;
	}
	for(int i = 0; i < playerCnt; i++) {
		tmpTable[i + 1]->name = table[i]->name;
		tmpTable[i + 1]->score = table[i]->score;
	}
	tmpTable[0]->name = "Nowy";
	tmpTable[0]->score = 9;
	playerCnt++;
	table = tmpTable;
}

void ScoreBoard::popLastPlayer() {
	Info** tmpTable = new Info * [playerCnt - 1];
	for(int i = 0; i < playerCnt - 1; i++) {
		tmpTable[i] = new Info;
	}
	for(int i = playerCnt - 1; i > 0; i--) {
		tmpTable[i - 1]->name = table[i - 1]->name;
		tmpTable[i - 1]->score = table[i - 1]->score;
	}
	delete[] table;
	playerCnt--;
	table = tmpTable;
}

void ScoreBoard::clearTable() {
	for(int i = 0; i < playerCnt; i++) {
		delete[] table[i];
	}
}