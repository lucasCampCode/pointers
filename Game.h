#pragma once
#include "Character.h"
class Game {
public: 
	void run();

	bool getGameOver() { return m_gameOver; }
	void setGameOver(bool value) { m_gameOver = value; }
private:
	int getInput(int input,const char* option1,const char* option2,const char* qurry);
	int startBattle(Character* enemy,int num);
	void start();
	void update();
	void draw();
	void end();
private:
	bool multiPlayer;
	bool m_gameOver = false;
	Character* m_player1;
	Character* m_player2;
	Character* m_enemies[10];
};