#include "IdleState.h"
#include "MovingState.h"
#include "Player.h"

void IdleState::handleInput(InputData input, Player &player)
{
	if (input.m_isMovingLeft || input.m_isMovingRight || input.m_isMovingDown || input.m_isMovingUp)
		player.setMoving(true);
}

void IdleState::update(float dt, Player &player)
{
	if (player.getMoving())
		player.setState(std::make_unique<MoveState>());
}

void IdleState::enter(Player &player)
{
	player.setMovement(sf::Vector2f(0.f, 0.f));
	std::cout << "Entered Idle State" << std::endl;
}

void IdleState::exit(Player &player)
{
	player.setMovement(sf::Vector2f(0.f, 0.f));
	std::cout << "Exited Idle State" << std::endl;
}