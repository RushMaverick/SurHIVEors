#pragma once

class Health
{
public:
	float getHealth() const { return m_health; };
	void setHealth(float value) { m_health += value; };

private:
	float m_health;
};