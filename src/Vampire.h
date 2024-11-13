#pragma once

#include "Collider.h"

class Game;

class Vampire : public Collider
{
public:
	Vampire(Game *game, sf::Vector2f position);
	virtual ~Vampire() {}

	void update(float deltaTime);

	void setIsKilled(bool isKilled) { m_isKilled = isKilled; }
	bool isKilled() { return m_isKilled; }

private:
	Game *m_pGame;
	bool m_isKilled = false;
};
