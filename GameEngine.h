#pragma once
#include <iostream>
#include <chrono>
#include <thread>
#include <windows.h>

class GameEngine {
public:
	GameEngine();
	~GameEngine();
	int constructConsole(int width, int height);
	int constructConsole();
	void start();
private:
	void gameThread();
	void allocBuf(CHAR_INFO**& buf, short height, short width);
protected:
	void draw(int x, int y, wchar_t c, short color);
	virtual bool setup() = 0;
	virtual bool update(float deltaTimeCnt) = 0;
	bool active = false;
	int screenWidth;
	int screenHeight;
	//CHAR_INFO* screenBuf;
	CHAR_INFO** screenBuf;
	HANDLE hConsole;
	SMALL_RECT rectWin;
};

