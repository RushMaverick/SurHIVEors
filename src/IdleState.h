#pragma once

#include "PlayerState.h"

class PlayerState;
class Player;

class IdleState : public PlayerState
{
public:
	IdleState() {};
	~IdleState() override {};
	void enter(Player &player) override;
	void exit(Player &player) override;
	void update(float dt, Player &player) override;
	void handleInput(InputData input, Player &player) override;

private:
	bool m_isGrounded;
};