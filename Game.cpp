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


char Game::getInput(char input,const char* option1,const char* option2,const char* qurry)
{
	input = ' ';
	std::cout << qurry << std::endl;
	std::cout << option1 << std::endl;
	std::cout << option2 << std::endl;
	while (input != '1' && input != '2') 
	{
		std::cin >> input; 
		if (input != '1' && input != '2')
		{
			std::cout << "invalid input!";
		}
	}
	return input;
}

void Game::startBattle(Character* enemy)
{
	char input = ' ';
	if (multiPlayer)
	{
		if (turn1)
		{
			input = getInput(input, "{1} for fight ", "{2} for run", "you run into a monster in the woods!");
			if (input == '1')
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
			if (input == '1')
			{
				m_player2->attack(enemy);
				turn1 = !turn1;
			}
			else 
			{
				turn1 = !turn1;
			}
		}
		int enemyAttack = rand() % 100 + 1;
		if (enemyAttack < 50)
		{
			std::cout << "the unknown entity attacks " << m_player1->getName()<< std::endl;
			enemy->attack(m_player1);
		}
		else 
		{
			std::cout << "the unknown entity attacks " << m_player2->getName()<< std::endl;
			enemy->attack(m_player2);
		}
		system("pause");
	}
	else
	{
		input = getInput(input, "{1} for fight ", "{2} for run", "you run into a monster in the woods!");
		if (input == 1)
		{
			m_player1->attack(enemy);
			enemy->attack(m_player1);
		}
	}
	system("cls");
}

bool Game::save()
{
	std::fstream file;

	file.open("gameData.txt", std::ios::app | std::ios::binary);
	if (!file.is_open())
		return false;

	file.write((char*)&m_roundNum, sizeof(int));
	file.write((char*)&m_player1,sizeof(Character));
	file.write((char*)&m_player2, sizeof(Character));
	file.write((char*)m_enemies, sizeof(Character)* 10);
	
	file.close();
	return true;
}

bool Game::load()
{
	std::fstream file;
	char input = ' ';
	int i = 0;
	file.open("gameData.txt", std::ios::in | std::ios::binary);
	if (!file.is_open())
		return false;
	while (file.eof())
	{
		file.seekg((sizeof(int) + (sizeof(Character)* 12))  * i, std::ios::beg);
		file.read((char*)&m_roundNum, sizeof(int));
		file.seekg(sizeof(int), std::ios::cur);
		file.read((char*)&m_player1, sizeof(Character));
		file.seekg(sizeof(Character), std::ios::cur);
		file.read((char*)&m_player2, sizeof(Character));
		file.seekg(sizeof(Character), std::ios::cur);
		file.read((char*)m_enemies, sizeof(Character) * 10);
		std::cout << "last round: " << m_roundNum << std::endl;
		std::cout << "player 1:"<<std::endl;
		m_player1->printStats();
		if (m_player2 != NULL) {
		std::cout << "player 2: " << std::endl;
		m_player1->printStats();
		}
		i++;
	}
	
	file.seekg((sizeof(int) + (sizeof(Character)* 12)) * i, std::ios::beg);
	file.read((char*)&m_roundNum, sizeof(int));
	file.seekg(sizeof(int), std::ios::cur);
	file.read((char*)&m_player1, sizeof(Character));
	file.seekg(sizeof(Character), std::ios::cur);
	file.read((char*)&m_player2, sizeof(Character));
	file.seekg(sizeof(Character), std::ios::cur);
	file.read((char*)m_enemies, sizeof(Character) * 10);

	file.close();
	return true;
}


void Game::start()
{
	srand(time(NULL));
	char input = ' ';
	char name[15];

	for(int i = 0; i < 10;i++)
		m_enemies[i] = new Character((float)(rand() % 80 + 20), (float)(rand() % 20 + 1));

	std::cout << "welcome to the fight whats your name?\n";
	std::cin >> name;
	m_player1 = new Character(100, 10, name);
	input = getInput(input, "{1} for yes", "{2} for no","Is there a second combatant?");
	system("cls");
	if (input == '1')
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
	char input = ' ';
	std::cout << "round " << m_roundNum <<"!\n";
	if (multiPlayer)
	{
		while (m_enemies[m_roundNum]->isAlive() && (m_player1->isAlive() || m_player2->isAlive()))
		{
			std::cout << "------------" << std::endl;
			m_player1->printStats();
			m_player2->printStats();
			m_enemies[m_roundNum]->printStats();

			startBattle(m_enemies[m_roundNum]);
		}
		if (!m_player1->isAlive() && !m_player2->isAlive())
			setGameOver(true);
	}
	else {
		while (m_enemies[m_roundNum]->isAlive() && m_player1->isAlive())
		{
			std::cout << "------------" << std::endl;
			m_player1->printStats();
			m_enemies[m_roundNum]->printStats();

			startBattle(m_enemies[m_roundNum]);
		}
		if (!m_player1->isAlive())
			setGameOver(true);
	}
	m_roundNum++;
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
