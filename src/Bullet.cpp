#include "Bullet.h"
#include "Player.h"
#include <vector>

// Constructor
Bullet::Bullet(Player *player)
	: Weapon(BulletWidth, BulletHeight),
	  m_pPlayer(player),
	  m_wpnTimer(m_pPlayer->getFireRate()),
	  m_drawTimer(2.f),
	  m_color(sf::Color::Red),
	  m_direction(1.f),
	  m_isActive(false),
	  m_wpnSize(BulletWidth, BulletHeight)
{
	setColor(m_color);
	setOrigin(sf::Vector2f(0.f, 0.f));
}

void Bullet::fire(float dt)
{
	m_wpnPos = m_pPlayer->getPosition();
	m_direction = m_pPlayer->getDirection();
}

// Update logic for weapon state and position
void Bullet::update(float dt)
{
	// // Update weapon timer for firing rate
	m_wpnTimer -= dt;

	// If time is up, make the weapon drawable again
	if (m_wpnTimer >= 0.f && !m_isDrawable)
	{
		fire(dt);
		std::cout << "yo" << std::endl;
		m_isDrawable = true;
		m_wpnTimer = m_pPlayer->getFireRate(); // Reset the weapon timer
	}

	// Handle weapon drawing duration
	if (m_isDrawable)
	{
		m_wpnPos.x += m_direction * 200.f * dt;
		sf::Transformable::move(m_wpnPos);
		m_drawTimer -= dt;
		if (m_drawTimer <= 0.f)
		{
			m_isDrawable = false;
			m_isActive = false;
			m_drawTimer = 2.f;
		}
	}
}

void Bullet::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	sf::CircleShape bullet(BulletRadius);

	bullet.setFillColor(m_color);
	bullet.setPosition(m_wpnPos);
	target.draw(bullet);
}
