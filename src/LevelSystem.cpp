#include "LevelSystem.h"
#include "Weapon.h"
#include "Player.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

LevelSystem::LevelSystem(Player *player, Game *game)
	: m_pPlayer(player),
	  m_pGame(game),
	  m_level(1),
	  m_exp(0),
	  m_expBeforeLvl(1)
{
}

LevelSystem::~LevelSystem()
{
}

// Initializes text and background for displaying level information
void LevelSystem::initialise()
{
	sf::Vector2f pos = {600.f, 30.f};
	m_font = m_pGame->getFont();
	m_text.setFont(m_font);
	m_text.setCharacterSize(24);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(pos);

	m_background.setFillColor(sf::Color(0, 255, 0, 100));
	m_background.setPosition(pos);
	m_prevUpgrade.setString("");
	m_level = 1;
	m_exp = 0;
	m_expBeforeLvl = 1;
}

// Updates the text with the current player stats
void LevelSystem::update(const Player *player)
{
	std::ostringstream ss;
	ss << "Player Health: (" << player->getHealth() << "/" << player->getMaxHealth() << ")\n";
	ss << "Fire Rate: (" << player->getFireRate() << ")\n";
	ss << "Player Speed: (" << player->getSpeed() << ")\n";
	ss << "Player Weapon Level: (" << player->getWeapon()->getLevel() << ")\n";
	ss << "Exp: (" << player->getLevel()->getExp() << ")\n";
	ss << "Player Level: (" << player->getLevel()->getLevel() << ")\n";
	ss << "Exp before next level: (" << player->getLevel()->getNextLvl() << ")\n";

	m_text.setString(ss.str());

	// Adjust background size based on text dimensions
	sf::FloatRect textBounds = m_text.getGlobalBounds();
	m_background.setSize({textBounds.width + 10, textBounds.height + 10});
}

// Draws the background and text displaying player level information
void LevelSystem::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(m_background);
	window.draw(m_text);
}

// Levels up the player, applying a random upgrade and updating experience requirements
void LevelSystem::levelUp()
{
	int upgrade = std::rand() % 4; // Selects a random upgrade

	switch (upgrade)
	{
	case FIRERATE:
		m_pPlayer->setFireRate(-0.4f);
		m_prevUpgrade.setString("Fire Rate Increased!");
		break;

	case MOVESPEED:
		m_pPlayer->setSpeed(50);
		m_prevUpgrade.setString("Move Speed Increased!");
		break;

	case WEAPONLVL:
		m_pPlayer->getWeapon()->setLevel();
		m_prevUpgrade.setString("Weapon Level Increased!");
		break;

	case MAXHEALTH:
		m_pPlayer->setMaxHealth(50.f);
		m_pPlayer->setHealth(m_pPlayer->getMaxHealth());
		m_prevUpgrade.setString("Max Health Increased!");
		break;

	default:
		break;
	}

	// Increase experience required for next level and increment level
	m_expBeforeLvl += m_level * 2;
	m_level += 1;
}
