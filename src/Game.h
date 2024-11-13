#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Collider;
class Player;
class EventManager;
class Vampire;

class Game : public sf::Drawable
{
public:
	enum class State
	{
		WAITING,
		ACTIVE,
	};

	Game();
	~Game();
	void update(sf::RenderTarget &window, float dt);
	void resetLevel();
	bool initialise();

	std::vector<Collider *> getColliders() const;
	void keyIsPressed(sf::Keyboard::Key key);
	void keyIsReleased(sf::Keyboard::Key key);
	void draw(sf::RenderTarget &window, sf::RenderStates states) const override;

	Player *getPlayer() const { return m_pPlayer.get(); };

	sf::Texture *getPlayerTexture() { return &m_playerTexture; }
	sf::Texture *getVampireTexture() { return &m_vampTexture; }
	sf::Font getFont() const { return m_font; };

	void vampireSpawner(float deltaTime);

private:
	std::unique_ptr<EventManager> m_pEvent;
	std::unique_ptr<Player> m_pPlayer;
	std::unique_ptr<sf::Clock> m_pClock;

	std::vector<std::unique_ptr<Vampire>> m_pVampires;
	std::vector<std::unique_ptr<Collider>> m_vLevel;

	sf::Texture m_playerTexture;
	State m_state;

	sf::Font m_font;

	sf::Texture m_vampTexture;
	float m_vampireCooldown = 0.0f;
	float m_nextVampireCooldown = 2.0f;
	int m_spawnCount = 0;
};