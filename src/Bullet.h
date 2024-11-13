#pragma once
#include "Weapon.h"

class Collider;
class Weapon;
class Player;

class Bullet : public Weapon
{
public:
	Bullet(Player *player);
	void update(float dt) override;
	virtual void draw(sf::RenderTarget &window, sf::RenderStates) const override;

	void getActive(bool value) { m_isActive = value; };

	float getDirection() const { return m_direction; };
	bool getActive() const { return m_isActive; };

private:
	Player *m_pPlayer;

	float m_wpnTimer;
	float m_drawTimer;
	float m_direction;

	bool m_isActive;

	sf::Vector2f m_wpnSize;
	sf::Vector2f m_wpnPos;
	sf::Color m_color;

	void fire(float dt);
};