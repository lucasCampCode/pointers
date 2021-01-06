#include "Character.h"
#include <iostream>

Character::Character()
{
	m_health = 100;
	m_damage = 10;
	strncpy_s(m_name, "???", 16);
}

Character::Character(float health, float damage)
{
	m_health = health;
	m_damage = damage;
	strncpy_s(m_name, "???", 16);
}

Character::Character(float health, float damage,const char* name)
{
	m_health = health;
	m_damage = damage;
	strncpy_s(m_name, name, 16);
}

char Character::getInput(char input, const char* option1, const char* option2, const char* query)
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

void Character::attack(Character* other)
{
	other->takeDamage(getDamage());
}

float Character::takeDamage(float damageAmount)
{
	m_health -= damageAmount;
	return damageAmount;
}

void Character::levelUp()
{
	char input = ' ';
	input = getInput(input, "{1} health", "{2} damage", "you have reached the end of the round now what do you wish to level up");
	if (input == '1') {
		m_health += 50;
	}
	else
	{
		m_damage += 10;
	}
}

void Character::printStats()
{
	std::cout << "name: " << m_name << "\n";
	std::cout << "health: " << m_health << "\n";
	std::cout << "damage: " << m_damage << std::endl;
	std::cout << "------------" << std::endl;

}

void Character::heal()
{
	m_health = 100;
}
