#include "GameEngine.h"

GameEngine::GameEngine() : 
	screenWidth{ 60 }, 
	screenHeight{ 60 },
	hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) },
	rectWin{ 0, 0, 1, 1 }
{
	//Alloc memory
	allocBuf(screenBuf, screenHeight, screenWidth);
	/*screenBuf = new CHAR_INFO[screenWidth * screenHeight];
	memset(screenBuf, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);*/
}

GameEngine::~GameEngine() {
	for(int i = 0; i < screenWidth; i++) {
		delete[] screenBuf[i];
	}
	delete[] screenBuf;
}

//GameEngine::~GameEngine() {
//	delete[] screenBuf;
//}

//Dla wersji ze screenBuf**
void GameEngine::allocBuf(CHAR_INFO**& buf, short height, short width) {
	//dev.to/drakargx/c-contiguous-allocation-of-2-d-arrays-446m
	//normal allocation doesn't work properly because the memory allocated by new is not contiguous
	//memory cleanup in destructor
	buf = new CHAR_INFO * [height];
	*buf = new CHAR_INFO[width * height];
	for(int i = 1; i < screenWidth; i++) {
		buf[i] = buf[i - 1] + width;
	}
}

int GameEngine::constructConsole(int width, int height) {
	screenWidth = width;
	screenHeight = height;

	SetConsoleWindowInfo(hConsole, TRUE, &rectWin);

	COORD coord = { (short)screenWidth, (short)screenHeight };
	SetConsoleScreenBufferSize(hConsole, coord);

	SetConsoleActiveScreenBuffer(hConsole);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 8;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = 700;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hConsole, false, &cfi);

	rectWin = { 0, 0, (short)screenWidth - 1, (short)screenHeight - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &rectWin);

	//Przydziel pamiec do screenbuf
	/*screenBuf = new CHAR_INFO[screenWidth * screenHeight];
	memset(screenBuf, 0, sizeof(CHAR_INFO) * screenWidth * screenHeight);*/

	return 1;
}

int GameEngine::constructConsole() {
	screenWidth = 60;
	screenHeight = 60;

	rectWin = { 0, 0, 1, 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &rectWin);

	COORD coord = { (short)screenWidth, (short)screenHeight };
	SetConsoleScreenBufferSize(hConsole, coord);

	SetConsoleActiveScreenBuffer(hConsole);

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 8;
	cfi.dwFontSize.Y = 8;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = 700;
	wcscpy_s(cfi.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hConsole, false, &cfi);

	rectWin = { 0, 0, (short)screenWidth - 1, (short)screenHeight - 1 };
	SetConsoleWindowInfo(hConsole, TRUE, &rectWin);

	//Przydziel pamiec do screenbuf
	//allocBuf(screenBuf, screenHeight, screenWidth);

	return 1;
}

void GameEngine::draw(int x, int y, wchar_t c, short color) {
	if(x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
		screenBuf[y][x].Char.UnicodeChar = c;
		screenBuf[y][x].Attributes = color;
	}
}

//void GameEngine::draw(int x, int y, wchar_t c, short col) {
//	if(x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
//		screenBuf[y * screenWidth + x].Char.UnicodeChar = c;
//		screenBuf[y * screenWidth + x].Attributes = col;
//	}
//}

void GameEngine::start() {
	active = true;

	// Star the thread
	std::thread t = std::thread(&GameEngine::gameThread, this);

	// Wait for thread to be exited
	t.join();
}

void GameEngine::gameThread() {
	// Create user resources as part of this thread
	std::chrono::system_clock::time_point tp1, tp2;
	if(!setup()) {
		active = false;
	}

	while(active) {
		// Handle Timing
		tp1 = std::chrono::system_clock::now();
		tp2 = std::chrono::system_clock::now();
		std::chrono::duration<float> elapsedTime = tp2 - tp1;
		tp1 = tp2;
		float deltaTimeCnt = elapsedTime.count();

		if(!update(deltaTimeCnt))
			active = false;

		WriteConsoleOutputW(hConsole, *screenBuf, { (short)screenWidth, (short)screenHeight }, { 0,0 }, &rectWin);
		//WriteConsoleOutputW(hConsole, screenBuf, { (short)screenWidth, (short)screenHeight }, { 0,0 }, &rectWin);
	}
}