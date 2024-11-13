#include "Player.h"
#include "Weapon.h"
#include "Lance.h"
#include "Bullet.h"
#include "IdleState.h"
#include "Game.h"
#include "LevelSystem.h"

Player::Player(Game *pGame)
	: Collider(sf::Vector2f(PlayerWidth, PlayerHeight)),
	  m_pGame(pGame),
	  m_fireRate(3.f),
	  m_playerPos(sf::Vector2f(0.f, 0.f)),
	  m_playerSpeed(150.f),
	  m_direction(-1.f),
	  m_playerMaxHealth(300.f),
	  m_pLvlSys(std::make_unique<LevelSystem>(this, m_pGame)),
	  m_pState(std::make_unique<IdleState>())
{
	m_pState->enter(*this);
	setOrigin(sf::Vector2f(0.f, 0.f));
	setColor(sf::Color::Blue);
	m_vWeapons.push_back(std::make_unique<Lance>(this));
	m_vWeapons.push_back(std::make_unique<Bullet>(this));
}

Player::~Player()
{
	if (m_pState)
		m_pState->exit(*this);
}

// Initializes player attributes and settings
bool Player::initialise()
{
	m_sprite.setTexture(*m_pGame->getPlayerTexture());
	m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
	m_sprite.setScale(3.5f, 3.5f);
	setIsDead(false);
	setPosition(ScreenWidth / 2, ScreenHeight / 2);
	m_sprite.setPosition(getPosition());
	setHealth(m_playerMaxHealth);
	m_fireRate = 3.f;
	m_playerSpeed = 150.f;
	m_pLvlSys->initialise();
	return true;
}

// Resolves collisions by determining overlap and moving player accordingly
void Player::resolveCollision(Collider *col)
{
	float deltaX = (getPosition().x + PlayerWidth / 2) - (col->getPosition().x + TileSizeX / 2);
	float deltaY = (getPosition().y + PlayerHeight / 2) - (col->getPosition().y + TileSizeY / 2);
	float overlapX = (PlayerWidth / 2 + TileSizeX / 2) - std::abs(deltaX);
	float overlapY = (PlayerHeight / 2 + TileSizeY / 2) - std::abs(deltaY);

	if (collisionSide(col) == m_collisionSide::LEFT)
		sf::Transformable::move(overlapX, 0.f);
	else if (collisionSide(col) == m_collisionSide::RIGHT)
		sf::Transformable::move(-overlapX, 0.f);
	else if (collisionSide(col) == m_collisionSide::TOP)
		sf::Transformable::move(0.f, overlapY);
	else if (collisionSide(col) == m_collisionSide::BOTTOM)
		sf::Transformable::move(0.f, -overlapY);
}

// Updates player state, weapon, and position
void Player::update(float dt)
{
	if (getHealth() <= 0.f)
		m_isKilled = true;

	m_pState->update(dt, *this);
	for (auto &wpn : m_vWeapons)
		wpn->update(dt);
	sf::Transformable::move(m_playerPos);
}

// Sets the player's movement vector and updates sprite position
void Player::setMovement(sf::Vector2f movement)
{
	m_playerPos = movement;
	m_sprite.setPosition(getPosition());
	m_sprite.setScale(3.5f * (m_direction > 0 ? -1.0f : 1.0f), 3.5f);
}

// Changes the player's state, ensuring the old state is exited cleanly
void Player::setState(std::unique_ptr<PlayerState> newState)
{
	if (m_pState)
		m_pState->exit(*this);

	m_pState = std::move(newState);
	m_pState->enter(*this);
}

// Draws the player and weapon if drawable
void Player::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	Collider::draw(target, states);

	for (auto &wpn : m_vWeapons)
	{
		if (wpn->getDrawState())
			wpn->draw(target, states);
	}
}
