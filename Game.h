#pragma once
#include "Character.h"
class Game {
public: 
	void run();

	bool getGameOver() { return m_gameOver; }
	void setGameOver(bool value) { m_gameOver = value; }
private:
	int getNumber(char input, const char* query);
	char getInput(char input,const char* option1,const char* option2,const char* query);
	void startBattle(Character* enemy);

	bool save();
	bool showSaveData();
	bool saveToSlot();
	bool load();

	void start();
	void update();
	void draw();
	void end();
private:
	bool multiPlayer = false;
	bool m_gameOver = false;
	bool turn1 = true;
	int m_roundNum = 0;

	Character* m_player1;
	Character* m_player2;
	Character* m_enemies[10];
};