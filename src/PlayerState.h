#pragma once

class Player;
struct InputData;

class PlayerState
{
public:
	virtual ~PlayerState() = default;
	virtual void enter(Player &player) = 0;
	virtual void exit(Player &player) = 0;
	virtual void handleInput(InputData input, Player &player) = 0;
	virtual void update(float dt, Player &player) = 0;

private:
};