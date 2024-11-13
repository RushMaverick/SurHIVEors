#include "MovingState.h"
#include "IdleState.h"
#include "Player.h"
#include "Constants.h"
#include <iostream>

// Handle player input for movement in MoveState
void MoveState::handleInput(InputData input, Player &player)
{
	// Reset movement flags
	m_hMovement = false;
	m_vMovement = false;

	// Horizontal movement
	if (input.m_isMovingRight)
	{
		m_hDirection = 1.f;
		m_hMovement = true;
	}
	else if (input.m_isMovingLeft)
	{
		m_hDirection = -1.f;
		m_hMovement = true;
	}
	else
	{
		m_hDirection = 0;
	}

	// Update player's facing direction if moving horizontally
	if (m_hMovement)
	{
		player.setDirection(m_hDirection);
	}

	// Vertical movement
	if (input.m_isMovingUp)
	{
		m_vDirection = -1.f;
		m_vMovement = true;
	}
	else if (input.m_isMovingDown)
	{
		m_vDirection = 1.f;
		m_vMovement = true;
	}
	else
	{
		m_vDirection = 0;
	}
}

// Clamp speed to prevent exceeding maximum speed
sf::Vector2f MoveState::clampSpeed(sf::Vector2f velocity)
{
	float speed = std::sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

	// Scale down if above max speed
	if (speed > PlayerMaxSpeed)
	{
		float scaling = PlayerMaxSpeed / speed;
		velocity.x *= scaling;
		velocity.y *= scaling;
	}
	return velocity;
}

// Update player movement based on direction and clamped speed
void MoveState::update(float dt, Player &player)
{
	sf::Vector2f velocity(0.f, 0.f);

	// Apply movement directions
	if (m_vMovement)
		velocity.y = m_vDirection * player.getSpeed();
	if (m_hMovement)
		velocity.x = m_hDirection * player.getSpeed();

	// Clamp and apply movement
	player.setMovement(clampSpeed(velocity) * dt);
}

// State transition actions
void MoveState::enter(Player &player)
{
	std::cout << "Entered Moving State" << std::endl;
}

void MoveState::exit(Player &player)
{
	std::cout << "Exited Moving State" << std::endl;
}
