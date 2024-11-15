#pragma once
#include "Weapon.h"

class Collider;
class Weapon;
class Player;

class Lance : public Weapon
{
public:
	Lance(Player *player);
	void update(float dt) override;
	void updateLance();
	virtual void draw(sf::RenderTarget &window, sf::RenderStates) const override;

private:
	Player *m_pPlayer;
	float m_wpnTimer;
	float m_drawTimer;
	float m_drawTime;
	sf::Vector2f m_wpnSize;
	sf::Vector2f m_wpnPos;
	sf::Color m_color;
	sf::RectangleShape m_lance;
};