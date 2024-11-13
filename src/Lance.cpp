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
	setPosition(sf::Vector2f(
		m_pPlayer->getCenter().x - (m_pPlayer->getDirection() == -1 ? LanceWidth : 0.0f),
		m_pPlayer->getCenter().y - LanceHeight / 2.0f));
}

void Lance::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	sf::RectangleShape wpn(m_wpnSize);
	sf::Vector2f offset((PlayerWidth / 2) + 10.f, PlayerHeight / 3.f);

	wpn.setFillColor(m_color);
	wpn.setPosition(sf::Vector2f(
		m_pPlayer->getCenter().x - (m_pPlayer->getDirection() == -1 ? LanceWidth : 0.0f),
		m_pPlayer->getCenter().y - LanceHeight / 2.0f));

	// Draw the weapon on the window
	window.draw(wpn);
}
