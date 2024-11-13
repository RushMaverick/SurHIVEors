#pragma once

#include "Constants.h"
#include <SFML/Graphics.hpp>

class Player;
class Game;
struct InputData
{
	bool m_isMovingUp = false;
	bool m_isMovingLeft = false;
	bool m_isMovingRight = false;
	bool m_isMovingDown = false;

	bool hasInputs() { return m_isMovingLeft || m_isMovingRight || m_isMovingUp || m_isMovingDown; };
};
class EventManager
{
public:
	EventManager(Game *pGame, Player *pPlayer);
	~EventManager();
	void update(float dt);
	void keyIsPressed(sf::Keyboard::Key key);
	void keyIsReleased(sf::Keyboard::Key key);

private:
	InputData m_inputs;
	Game *m_pGame;
	Player *m_pPlayer;
};