#pragma once

#include "Constants.h"
#include "Collider.h"
#include "Health.h"
#include "PlayerState.h"
#include "EventManager.h"
#include <SFML/Graphics.hpp>
#include <iostream>

class Collider;
class Game;
class Bullet;
class PlayerState;
class IdleState;
class JumpingState;
class FallingState;
class Weapon;
class LevelSystem;

class Player : public Collider, public Health
{
public:
	Player(Game *pGame);
	~Player();
	void update(float dt);
	bool initialise();

	void resolveCollision(Collider *col);
	void setMovement(sf::Vector2f movement);
	void setState(std::unique_ptr<PlayerState> newState);
	void setIdle(bool state) { m_isIdle = state; };
	void setMoving(bool state) { m_isMoving = state; };
	void setSpeed(float value) { m_playerSpeed += value; };
	void setFireRate(float value) { m_fireRate += value; };
	void handleInput(InputData input) { m_pState->handleInput(input, *this); };
	void setDirection(float value) { m_direction = value; };
	void setMaxHealth(float value) { m_playerMaxHealth = value; };
	void setIsDead(bool value) { m_isKilled = value; };
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

	bool getIdle() const { return m_isIdle; };
	bool getIsDead() const { return m_isKilled; };
	bool getMoving() const { return m_isMoving; };
	float getDirection() const { return m_direction; };
	float getFireRate() const { return m_fireRate; };
	float getSpeed() const { return m_playerSpeed; };
	float getMaxHealth() const { return m_playerMaxHealth; };
	Weapon *getWeapon() const { return m_vWeapons[0].get(); };
	LevelSystem *getLevel() const { return m_pLvlSys.get(); };

private:
	Game *m_pGame;
	sf::Vector2f m_playerPos;
	bool m_isIdle = false;
	bool m_isMoving = false;
	float m_fireRate;
	float m_fireTimer;
	float m_direction;
	float m_playerSpeed;
	float m_playerMaxHealth;
	bool m_isKilled = false;

	std::unique_ptr<PlayerState> m_pState;
	std::unique_ptr<LevelSystem> m_pLvlSys;

	std::vector<std::unique_ptr<Weapon>> m_vWeapons;
};