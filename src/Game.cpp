#include "Game.h"
#include "EventManager.h"
#include "Player.h"
#include "LevelSystem.h"
#include "Weapon.h"
#include "Collider.h"
#include "ResourceManager.h"
#include "Vampire.h"

// Constructor and Destructor
Game::Game()
	: m_pPlayer(std::make_unique<Player>(this)),
	  m_pClock(std::make_unique<sf::Clock>()),
	  m_vampireCooldown(2.0f),
	  m_nextVampireCooldown(2.0f)
{
	m_pEvent = std::make_unique<EventManager>(this, m_pPlayer.get());
}

Game::~Game() {}

// Initialize resources and reset the level
bool Game::initialise()
{
	if (!m_font.loadFromFile(ResourceManager::getFilePath("Doto.ttf")))
	{
		std::cerr << "Unable to load font" << std::endl;
		return false;
	}
	if (!m_vampTexture.loadFromFile(ResourceManager::getFilePath("vampire.png")) ||
		!m_playerTexture.loadFromFile(ResourceManager::getFilePath("player.png")))
	{
		std::cerr << "Unable to load texture" << std::endl;
		return false;
	}
	resetLevel();
	return true;
}

// Main update loop handling game states and logic updates
void Game::update(sf::RenderTarget &window, float dt)
{
	switch (m_state)
	{
	case State::WAITING:
		if (m_pClock->getElapsedTime().asSeconds() >= 3.f)
		{
			m_state = State::ACTIVE;
			m_pClock->restart();
		}
		break;

	case State::ACTIVE:
		m_pEvent->update(dt);
		m_pPlayer->update(dt);

		vampireSpawner(dt);

		for (auto &temp : m_pVampires)
		{
			temp->update(dt);
		}

		if (m_pPlayer->getIsDead())
		{
			m_state = State::WAITING;
			resetLevel();
		}
		break;
	}

	// Clean up defeated vampires
	auto it = m_pVampires.begin();
	while (it != m_pVampires.end())
	{
		if ((*it)->isKilled())
		{
			m_pPlayer->getLevel()->setExp(1);
			it = m_pVampires.erase(it);
		}
		else
		{
			++it;
		}
	}
	m_pPlayer->getLevel()->update(m_pPlayer.get());
}

// Retrieve colliders for level elements
std::vector<Collider *> Game::getColliders() const
{
	std::vector<Collider *> pColliders;
	for (const auto &pCollider : m_vLevel)
	{
		pColliders.push_back(pCollider.get());
	}
	return pColliders;
}

// Reset the level state
void Game::resetLevel()
{
	m_vLevel.clear();
	m_pVampires.clear();
	m_pPlayer->initialise();
	m_pPlayer->getLevel()->initialise();
}

// Handle keyboard input events
void Game::keyIsPressed(sf::Keyboard::Key key)
{
	m_pEvent->keyIsPressed(key);
}

void Game::keyIsReleased(sf::Keyboard::Key key)
{
	m_pEvent->keyIsReleased(key);
}

// Draw game elements on the screen
void Game::draw(sf::RenderTarget &window, sf::RenderStates states) const
{
	// Draw UI elements based on game state
	if (m_state == State::WAITING)
	{
		sf::Text startText;
		startText.setFont(m_font);
		startText.setString("Game Start!");
		startText.setFillColor(sf::Color::White);
		startText.setPosition(80.0f, 80.0f);
		startText.setStyle(sf::Text::Bold);
		window.draw(startText);
	}
	else
	{
		// Draw timer and previous upgrade text
		sf::Text timerText;
		sf::Text prevUpgrade;
		timerText.setFont(m_font);
		timerText.setFillColor(sf::Color::White);
		timerText.setStyle(sf::Text::Bold);
		timerText.setString(std::to_string(static_cast<int>(m_pClock->getElapsedTime().asSeconds())));
		timerText.setPosition(80.0f, 80.0f);

		prevUpgrade.setFont(m_font);
		prevUpgrade.setFillColor(sf::Color::White);
		prevUpgrade.setStyle(sf::Text::Bold);
		prevUpgrade.setString(m_pPlayer->getLevel()->getString());
		prevUpgrade.setPosition(80.0f, 120.0f);

		window.draw(timerText);
		window.draw(prevUpgrade);
	}

	// Draw game objects
	for (const auto &col : m_vLevel)
		col->draw(window, states);

	for (const auto &vampire : m_pVampires)
		vampire->draw(window, states);

	m_pPlayer->draw(window, states);

	m_pPlayer->getLevel()->draw(window, states);
}

// Spawn vampires at randomized intervals and positions
void Game::vampireSpawner(float deltaTime)
{
	if (m_vampireCooldown > 0.0f)
	{
		m_vampireCooldown -= deltaTime;
		return;
	}

	// Randomize spawn position at screen edges
	float randomXPos = rand() % ScreenWidth;
	float randomYPos = rand() % ScreenHeight;
	float xMinDist = (randomXPos < ScreenWidth / 2) ? -randomXPos : ScreenWidth - randomXPos;
	float yMinDist = (randomYPos < ScreenHeight / 2) ? -randomYPos : ScreenHeight - randomYPos;
	randomXPos += (abs(xMinDist) < abs(yMinDist)) ? xMinDist : 0;
	randomYPos += (abs(yMinDist) < abs(xMinDist)) ? yMinDist : 0;

	// Spawn vampire and adjust cooldown
	sf::Vector2f spawnPosition(randomXPos, randomYPos);
	m_pVampires.push_back(std::make_unique<Vampire>(this, spawnPosition));

	m_spawnCount++;
	if (m_spawnCount % 5 == 0)
	{
		m_nextVampireCooldown -= 0.02f;
	}
	m_vampireCooldown = m_nextVampireCooldown;
}
