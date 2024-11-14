#include "Vampire.h"
#include "Constants.h"
#include "Game.h"
#include "Weapon.h"
#include "Player.h"
#include "MathUtils.h"
#include <iostream>

Vampire::Vampire(Game *game, sf::Vector2f position)
	: Collider(sf::Vector2f(VampireWidth, VampireHeight)),
	  m_pGame(game),
	  m_maxHealth(20.f)
{
	setPosition(position);
	setOrigin(sf::Vector2f(0.0f, 0.0f));
	setIsKilled(false);

	m_sprite.setTexture(*m_pGame->getVampireTexture());
	m_sprite.setScale(2.0f, 2.0f);
	setHealth(m_maxHealth);
}

void Vampire::update(float deltaTime)
{
	if (m_isKilled)
		return;

	Player *pPlayer = m_pGame->getPlayer();
	const std::vector<std::unique_ptr<Weapon>> &pWeapons = pPlayer->getWeapons();

	for (auto &wpn : pWeapons)
	{

		if (collidesWith(wpn.get()) && wpn->getDrawState())
		{
			setHealth(-5.f);
		}
	}

	if (collidesWith(pPlayer))
	{
		pPlayer->setHealth(-5.f);
		return;
	}

	sf::Vector2f playerCenter = pPlayer->getCenter();
	sf::Vector2f direction = VecNormalized(playerCenter - getCenter());
	direction *= VampireSpeed * deltaTime;
	sf::Transformable::move(direction);
	m_sprite.setPosition(getPosition());
	if (getHealth() <= 0.f)
		setIsKilled(true);
}