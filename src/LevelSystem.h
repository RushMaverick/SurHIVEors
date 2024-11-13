#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Player;
class Weapon;
class Collider;
class Game;

class LevelSystem : public sf::Transformable, public sf::Drawable
{
	enum upgrades
	{
		FIRERATE = 0,
		MOVESPEED = 1,
		WEAPONLVL = 2,
		MAXHEALTH = 4
	};

public:
	LevelSystem(Player *player, Game *game);
	~LevelSystem();

	virtual void draw(sf::RenderTarget &window, sf::RenderStates) const override;

	void initialise();
	void levelUp();
	void update(const Player *player);
	void setExp(int add)
	{
		m_exp += add;
		if (m_exp >= m_expBeforeLvl)
			levelUp();
	};
	void setLevel(int level) { m_level = level; };
	void setString(std::string text) { m_prevUpgrade.setString(text); };
	void setExpBeforeLvl(int value) { m_expBeforeLvl = value; };

	std::string getString() const { return m_prevUpgrade.getString(); };
	int getLevel() const { return m_level; };
	int getExp() const { return m_exp; };
	int getExpBeforeLvl() const { return m_expBeforeLvl; };
	int getNextLvl() const { return m_expBeforeLvl; };

private:
	int m_level;
	int m_exp;
	int m_expBeforeLvl;

	Player *m_pPlayer;
	Game *m_pGame;

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_prevUpgrade;
	sf::RectangleShape m_background;
	sf::Vector2f m_position;
	unsigned int m_fontSize;
};