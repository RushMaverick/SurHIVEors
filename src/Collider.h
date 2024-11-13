#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "Constants.h"

enum class m_collisionSide
{
	NONE = 0,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

class Collider : public sf::Transformable, public sf::Drawable
{
public:
	Collider(sf::Vector2f size, sf::Vector2f position = sf::Vector2f(0, 0));
	~Collider();

	void setColor(sf::Color color) { m_color = color; };
	virtual void draw(sf::RenderTarget &window, sf::RenderStates) const override;

	sf::Vector2f getCenter() const { return getPosition() + (m_size * 0.5f); };

	m_collisionSide collisionSide(Collider *pOther);
	sf::Vector2f getSize() const { return m_size; }

	bool collidesWith(Collider *pOther);

protected:
	sf::Sprite m_sprite;

private:
	sf::Color m_color = sf::Color::White;
	sf::Vector2f m_size;
};