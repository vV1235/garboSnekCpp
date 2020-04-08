#include "ScoreBoard.h"

ScoreBoard::ScoreBoard(int r_, int c_) : r{ r_ }, c{ c_ } {
	//More explicit in terms of what it does
	aloc(this->r, this->c);
	//Example
	table[0][0].name = "Jacek1";
	table[0][0].score = 12;
	table[0][1].name = "Jacek2";
	table[0][1].score = 23;
	table[1][0].name = "Jacek3";
	table[1][0].score = 34;
	table[1][1].name = "Jacek4";
	table[1][1].score = 45;
}

ScoreBoard::~ScoreBoard() {
	//TODO table** cleanup
}

int ScoreBoard::getRow() const {
	return r;
}

int ScoreBoard::getCol () const {
	return r;
}

std::string ScoreBoard::getGameOverText() const {
	return gameOverText;
}

std::string ScoreBoard::getName(int r_, int c_) const {
	return table[r_][c_].name;
}

//TODO score display on the screen
//wchar_t ScoreBoard::getScore(int r_, int c_) const {
//	return static_cast<char>(table[r_][c_].score);
//}

void ScoreBoard::aloc(int r, int c) {
	this->table = new Info * [r];
	for(int i = 0; i < r; i++) {
		this->table[i] = new Info[c];
	}
}