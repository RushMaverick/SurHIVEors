#include "Collider.h"
#include "iostream"

Collider::Collider(sf::Vector2f size, sf::Vector2f position) : m_size(size)
{
	sf::Transformable::setPosition(position);
}

Collider::~Collider()
{
}

void Collider::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	window.draw(m_sprite);
}

bool Collider::collidesWith(Collider *pOther)
{
	sf::Vector2f thisPosition = getPosition();
	sf::Vector2f thisSize = getSize();

	sf::Vector2f otherPosition = pOther->getPosition();
	sf::Vector2f otherSize = pOther->getSize();

	float thisLeft = thisPosition.x;
	float thisRight = thisPosition.x + thisSize.x;
	float thisTop = thisPosition.y;
	float thisBottom = thisPosition.y + thisSize.y;

	float otherLeft = otherPosition.x;
	float otherRight = otherPosition.x + otherSize.x;
	float otherTop = otherPosition.y;
	float otherBottom = otherPosition.y + otherSize.y;

	if (thisLeft < otherRight && thisRight > otherLeft &&
		thisTop < otherBottom && thisBottom > otherTop)
	{
		// Rectangles overlap
		return true;
	}
	return false;
}

m_collisionSide Collider::collisionSide(Collider *pOther)
{
	float deltaX = (getPosition().x + PlayerWidth / 2) - (pOther->getPosition().x + TileSizeX / 2);
	float deltaY = (getPosition().y + PlayerHeight / 2) - (pOther->getPosition().y + TileSizeY / 2);

	float overlapX = (PlayerWidth / 2 + TileSizeX / 2) - std::abs(deltaX);
	float overlapY = (PlayerHeight / 2 + TileSizeY / 2) - std::abs(deltaY);

	if (overlapY < overlapX)
	{
		// Collision happened on the y-axis
		if (deltaY > 0)
			return m_collisionSide::TOP;
		else
			return m_collisionSide::BOTTOM;
	}
	else
	{
		// Collision happened on the x-axis
		if (deltaX > 0)
			return m_collisionSide::LEFT;
		else
			return m_collisionSide::RIGHT;
	}
	return m_collisionSide::NONE;
}
