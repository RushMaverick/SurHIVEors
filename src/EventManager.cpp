#include "EventManager.h"
#include "Game.h"
#include "Player.h"

EventManager::EventManager(Game *pGame, Player *pPlayer) : m_pGame(pGame), m_pPlayer(pPlayer)
{
}

EventManager::~EventManager()
{
}

void EventManager::update(float dt)
{
	m_pPlayer->handleInput(m_inputs);
}

void EventManager::keyIsPressed(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Space:
		std::cout << "space" << std::endl;
		break;
	case sf::Keyboard::W:
		m_inputs.m_isMovingUp = true;
		break;
	case sf::Keyboard::A:
		m_inputs.m_isMovingLeft = true;
		break;
	case sf::Keyboard::D:
		m_inputs.m_isMovingRight = true;
		break;
	case sf::Keyboard::S:
		m_inputs.m_isMovingDown = true;
		break;
	default:
		break;
	}
}

void EventManager::keyIsReleased(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Space:
		break;
	case sf::Keyboard::W:
		m_inputs.m_isMovingUp = false;
		break;
	case sf::Keyboard::A:
		m_inputs.m_isMovingLeft = false;
		break;
	case sf::Keyboard::D:
		m_inputs.m_isMovingRight = false;
		break;
	case sf::Keyboard::S:
		m_inputs.m_isMovingDown = false;
		break;
	default:
		break;
	}
}
