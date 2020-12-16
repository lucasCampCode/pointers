#include "Game.h"
#include <iostream>


void Game::run() 
{
	start();

	while (!getGameOver()) 
	{
		draw();
		update();

		if (m_player1->isAlive() || m_player2->isAlive())
			setGameOver(true);
	}

	end();
}


int Game::getInput(int input,const char* option1,const char* option2,const char* qurry)
{
	input = 0;
	std::cout << qurry << std::endl;
	std::cout << option1 << std::endl;
	std::cout << option2 << std::endl;
	while (input != 1 && input != 2) 
	{
		std::cin >> input; 
		if (input != 1 && input != 2)
		{
			std::cout << "invalid input!";
		}
	}
	return input;
}

int Game::startBattle(Character* enemy,int num)
{
	int input = 0;
	bool turn1 = true;
	while (enemy->isAlive() || m_player1->isAlive() && m_player2->isAlive()) 
	{
		if (multiPlayer) 
		{
			if (turn1)
			{
				input = getInput(input, "{1} for fight ", "{2} for run", "you run into a monster in the woods!");
				if (input == 1) 
				{
					m_player1->attack(enemy);
				}
				else
					break;
			}
		}
	}
	return num++;
}


void Game::start()
{
	int input = 0;
	char name[15];
	std::cout << "welcome to the fight whats your name?\n";
	std::cin >> name;
	m_player1 = new Character(100, 10, name);
	input = getInput(input, "{1} for yes", "{2} for no","Is there a second combatant?");
	if (input == 1)
	{
		std::cout << "whats the second combatants name?\n";
		std::cin >> name;
		m_player2 = new Character(100, 10, name);
		multiPlayer = false;
	}
	else
		std::cout << "its dangorous to go alone\n";
	for(int i = 0; i < 10;i++)
		m_enemies[i] = new Character((float)(rand() % 100 + 20), (float)(rand() % 20));
}

void Game::update() 
{
	int input = 0;
	int entityNum = 0;
	entityNum = startBattle(m_enemies[entityNum], entityNum);
}

void Game::draw() 
{
	m_player1->printStats();
	if (multiPlayer)
		m_player2->printStats();
}

void Game::end()
{
	delete m_player1;
	delete m_player2;
	delete[] m_enemies;
}
