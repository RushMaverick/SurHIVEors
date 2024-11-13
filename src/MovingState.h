#pragma once

#include "PlayerState.h"
#include <SFML/Graphics.hpp>

class PlayerState;
class Player;

class MoveState : public PlayerState
{
public:
	MoveState() : m_Pos(.0f, 0.f) {};
	~MoveState() override {};
	void enter(Player &player) override;
	void exit(Player &player) override;
	void update(float dt, Player &player) override;
	sf::Vector2f clampSpeed(sf::Vector2f speed);
	void handleInput(InputData input, Player &player) override;

private:
	float m_accel;
	sf::Vector2f m_Pos;
	bool m_hMovement;
	bool m_vMovement;
	float m_hDirection = 0;
	float m_vDirection = 0;
};
