#pragma once
class Character
{
private:
	char getInput(char input, const char* option1, const char* option2, const char* query);
public:
	Character();
	Character(float health, float damage);
	Character(float health, float damage,const char* name);

	
	void attack(Character* other);
	float takeDamage(float damageAmount);
	void levelUp();
	void printStats();
	void heal();

	char* getName() { return m_name; }
	float getDamage() { return m_damage; }
	float getHealth() { return m_health; }
	bool isAlive() { return m_health > 0; }

private:
	char m_name[16];
	float m_health;
	float m_damage;
};

