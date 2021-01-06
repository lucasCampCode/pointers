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


int Game::getNumber(char input, const char* query)
{
	input = ' ';
	std::cout << query << std::endl;
	std::cin >> input;
	while (input == ' ') {
		switch (input) {
		case '1':
			return 0;
		case '2':
			return 1;
		case '3':
			return 2;
		case '4':
			return 3;
		case '5':
			return 4;
		case '6':
			return 5;
		case '7':
			return 6;
		case '8':
			return 7;
		case '9':
			return 8;
		case '10':
			return 9;
		case '11':
			return 10;
		case '12':
			return 11;
		case '13':
			return 12;
		case '14':
			return 13;
		case '15':
			return 14;
		default:
			return 0;
		}
	}
}

char Game::getInput(char input,const char* option1,const char* option2,const char* query)
{
	input = ' ';
	std::cout << query << std::endl;
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
		//players turn
		if (turn1)
		{
			if (m_player1->isAlive()) {
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
				turn1 = !turn1;
		}
		else
		{
			if (m_player2->isAlive()) {
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
			else
				turn1 = !turn1;
		}
		//enemies turn
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
		}
		int enemyAttack = rand() % 100 + 1;
		if (enemyAttack < 50)
		{
			std::cout << "the unknown entity attacks " << m_player1->getName() << std::endl;
			enemy->attack(m_player1);
		}
		else
		{
			std::cout << "the unknown entity missed " << std::endl;
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

bool Game::showSaveData()
{
	std::fstream file;
	int blocksOfData = 0;
	file.open("gameData.txt", std::ios::in | std::ios::binary);
	if (!file.is_open())
		return false;
	//while end of file isnt reached
	while (file.peek() != EOF)
	{
		file.read((char*)&m_roundNum, sizeof(int));
		file.read((char*)&m_player1, sizeof(Character));
		file.read((char*)&m_player2, sizeof(Character));
		file.read((char*)m_enemies, sizeof(Character) * 10);
		std::cout << "save:" << blocksOfData + 1 << std::endl;
		std::cout << "last round: " << m_roundNum << std::endl;
		if (m_player1 != NULL) {
			std::cout << "player 1: " << std::endl;
			m_player1->printStats();
		}
		if (m_player2 != NULL) {
			std::cout << "player 2: " << std::endl;
			m_player2->printStats();
		}
		blocksOfData++;
		//file.seekg(sizeof(int), std::ios::cur);
		//file.seekg((sizeof(Character) * 12), std::ios::cur);
	}
	file.close();
	return true;
}

bool Game::saveToSlot()
{
	std::fstream file;
	char input = ' ';
	showSaveData();
	file.open("gameData.txt", std::ios::app | std::ios::binary);
	if (!file.is_open())
		return false;
	int slot = getNumber(input, "where do you want to save?");
	for (int i = 0; i < slot; i++)
	{
		if(i == 0)
			file.seekp(sizeof(int), std::ios::beg);
		else
			file.seekp(sizeof(int), std::ios::cur);
		file.seekp((sizeof(Character) * 12), std::ios::cur);
	}
	file.write((char*)&m_roundNum, sizeof(int));
	file.write((char*)&m_player1, sizeof(Character));
	file.write((char*)&m_player2, sizeof(Character));
	file.write((char*)m_enemies, sizeof(Character) * 10);
	file.close();
	return true;
}

bool Game::load()
{
	std::fstream file;
	char input = ' ';
	int blocksOfData = 0;
	showSaveData();

	file.open("gameData.txt", std::ios::in | std::ios::binary);
	if (!file.is_open())
		return false;

	blocksOfData = getNumber(input,"where do you want to load from?");

	file.seekg(std::ios::beg);
	for (int i = 1; i < blocksOfData; i++) {
		file.seekg(sizeof(int), std::ios::cur);
		file.seekg((sizeof(Character) * 12), std::ios::cur);
	}
	file.read((char*)&m_roundNum, sizeof(int));
	file.read((char*)&m_player1, sizeof(Character));
	file.read((char*)&m_player2, sizeof(Character));
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

	input = getInput(input, "{1} for yes", "{2} for no", "Do you want to load an old save");
	if (input == '1')
	{
		load();
	}
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
			if (m_player1->isAlive())
				m_player1->printStats();
			if(m_player2->isAlive())
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
	input = getInput(input, "{1} continue", "{2} save", "you reached a temporary safe place");
	if (input == '1') {
		if (multiPlayer) {
			if (m_player1->isAlive())
				m_player1->levelUp();
			else
			{
				std::cout << m_player2->getName() << " revives you so you can fight another day" << std::endl;
				m_player1->heal();
			}
			if (m_player2->isAlive())
				m_player2->levelUp();
			else
			{
				std::cout << m_player1->getName() << " revives you so you can fight another day" << std::endl;
				m_player2->heal();
			}
		}
		else
			m_player1->levelUp();
	}
	else
	{
		save();
	}

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
