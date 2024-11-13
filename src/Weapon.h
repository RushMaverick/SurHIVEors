#pragma once

#include "Collider.h"
#include <SFML/Graphics.hpp>

class Collider;
class Player;

class Weapon : public Collider
{
public:
	Weapon(float sizeX, float sizeY)
		: Collider(sf::Vector2f(sizeX, sizeY)),
		  m_wpnLevel(1),
		  m_isDrawable(false) { setOrigin(0.f, 0.f); };
	virtual ~Weapon() = default;
	virtual void update(float dt) = 0;

	void setDrawable(bool state) { m_isDrawable = state; };
	void setLevel() { m_wpnLevel += 1; };

	int getLevel() { return m_wpnLevel; };
	bool getDrawState() { return m_isDrawable; };

protected:
	int m_wpnLevel;
	bool m_isDrawable;
};