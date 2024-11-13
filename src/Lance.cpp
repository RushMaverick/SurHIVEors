#include "Lance.h"
#include "Player.h"

// Constructor
Lance::Lance(Player *player)
	: Weapon(LanceWidth, LanceHeight),
	  m_pPlayer(player),
	  m_wpnTimer(m_pPlayer->getFireRate()),
	  m_drawTime(0.4f),
	  m_drawTimer(0.4f),
	  m_color(sf::Color::Red),
	  m_wpnSize(LanceWidth, LanceHeight)
{
	setColor(m_color);
	setOrigin(sf::Vector2f(0.f, 0.f));
	setPosition(m_pPlayer->getPosition());
}

// Update logic for weapon state and position
void Lance::update(float dt)
{
	// Update weapon timer for firing rate
	m_wpnTimer -= dt;

	// If time is up, make the weapon drawable again
	if (m_wpnTimer <= 0.f)
	{
		setDrawable(true);
		m_wpnTimer = m_pPlayer->getFireRate();
	}

	// Handle weapon drawing duration
	if (m_isDrawable)
	{
		m_drawTimer -= dt;
		if (m_drawTimer <= 0.f)
		{
			m_drawTimer = m_drawTime;
			setDrawable(false);
		}
	}
	// Update weapon position based on player direction
	sf::Vector2f weaponOffset = (m_pPlayer->getDirection() > 0) ? sf::Vector2f(15, -5) : sf::Vector2f(-15, -5);
	setPosition(m_pPlayer->getPosition() + weaponOffset);
}

void Lance::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	sf::RectangleShape wpn(m_wpnSize);
	sf::Vector2f weaponOffset = (m_pPlayer->getDirection() > 0) ? sf::Vector2f(15, -5) : sf::Vector2f(-15, -5);

	wpn.setFillColor(m_color);
	wpn.setPosition(m_pPlayer->getPosition() + weaponOffset);
	wpn.setScale(m_pPlayer->getDirection() > 0 ? 1.0f : -1.0f, 1.0f);
	// Draw the weapon on the window
	window.draw(wpn);
}
