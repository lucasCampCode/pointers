#include "Game.h"
#include <iostream>
#include <fstream>


void Game::run() 
{
	start();

	while (!getGameOver()) 
	{
		update();
		draw();
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

void Game::startBattle(Character* enemy)
{
	int input = 0;
	if (multiPlayer)
	{
		if (turn1)
		{
			input = getInput(input, "{1} for fight ", "{2} for run", "you run into a monster in the woods!");
			if (input == 1)
			{
				m_player1->attack(enemy);
				turn1 = !turn1;
			}
			else
			{
				turn1 = !turn1;
			}
		}
		else
		{
			input = getInput(input, "{1} for fight ", "{2} for run", "you run into a monster in the woods!");
			if (input == 1)
			{
				m_player2->attack(enemy);
				turn1 = !turn1;
			}
			else {
				turn1 = !turn1;
			}
		}
	}
	else
	{
		input = getInput(input, "{1} for fight ", "{2} for run", "you run into a monster in the woods!");
		if (input == 1)
		{
			m_player1->attack(enemy);
		}
	}
	system("cls");
}

void Game::save()
{
	std::fstream file;
	file.open("gameData.txt", std::ios::out);
	if (!file.is_open())
		return;

	file.close();
}

bool Game::load()
{
	std::fstream file;
	file.open("gameData.txt", std::ios::in | std::ios::_Nocreate);
	if (!file.is_open())
		return false;

	file.close();
	return true;
}


void Game::start()
{
	int input = 0;
	char name[15];

	for(int i = 0; i < 10;i++)
		m_enemies[i] = new Character((float)(rand() % 100 + 20), (float)(rand() % 20));

	std::cout << "welcome to the fight whats your name?\n";
	std::cin >> name;
	m_player1 = new Character(100, 10, name);
	input = getInput(input, "{1} for yes", "{2} for no","Is there a second combatant?");
	if (input == 1)
	{
		std::cout << "whats the second combatants name?\n";
		std::cin >> name;
		m_player2 = new Character(100, 10, name);
		multiPlayer = true;
	}
	else
		std::cout << "its dangorous to go alone\n";
}

void Game::update()
{
	int input = 0;
	std::cout << "round " << m_entityNum <<"!\n";
	if (multiPlayer)
	{
		while (m_enemies[m_entityNum]->isAlive() && (m_player1->isAlive() || m_player2->isAlive()))
		{
			m_player1->printStats();
			m_player2->printStats();
			m_enemies[m_entityNum]->printStats();

			startBattle(m_enemies[m_entityNum]);
		}
		if (!m_player1->isAlive() && !m_player2->isAlive())
			setGameOver(true);
	}
	else {
		while (m_enemies[m_entityNum]->isAlive() && m_player1->isAlive())
		{
			m_player1->printStats();
			m_enemies[m_entityNum]->printStats();

			startBattle(m_enemies[m_entityNum]);
		}
		if (!m_player1->isAlive())
			setGameOver(true);
	}
	m_entityNum++;
}

void Game::draw() 
{
}

void Game::end()
{
	delete m_player1;
	delete m_player2;
	delete[] m_enemies;
}
