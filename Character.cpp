#include "Character.h"
#include <iostream>

Character::Character()
{
	char name[] = "???";
	m_health = 100;
	m_damage = 10;
	*m_name = name;
}

Character::Character(float health, float damage)
{
	char name[] = "???";
	m_health = health;
	m_damage = damage;
	*m_name = name;
}

Character::Character(float health, float damage, char* name)
{
	m_health = health;
	m_damage = damage;
	*m_name = name;
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

void Character::printStats()
{
	std::cout << "name: " << *m_name << "\n";
	std::cout << "health: " << m_health << "\n";
	std::cout << "damage: " << m_damage << "\n";

}

void Character::setName(char* name)
{
	*m_name = name;
}
