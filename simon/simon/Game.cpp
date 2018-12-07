// @Author Michael Rainsford Ryan
// @Date 07/12/2018
// Estimated time: 180m
// Session 1: 09:45 - 10:01 - 07/12/2018

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Simon" },
	m_exitGame{ false }, //when true game will exit

	// Setup the size of the buttons
	m_redButton{ sf::Vector2f{ 200.0f, 200.0f } },
	m_greenButton{ sf::Vector2f{ 200.0f, 200.0f } },
	m_blueButton{ sf::Vector2f{ 200.0f, 200.0f } },
	m_yellowButton{ sf::Vector2f{ 200.0f, 200.0f } }
{
	setupButtons();
	setupFontAndText();
}


Game::~Game()
{
}

/// <summary>
/// @brief Setup text, squares and sounds.
/// 
/// Load font and sound.
/// Setup text messages.
/// Setup tone (pitch)
/// Position and colour of the squares
/// </summary>
void Game::setupButtons()
{
	// Setup green
	m_greenButton.setFillColor(GREEN);
	m_greenButton.setPosition(sf::Vector2f{ 350.0f, 30.0f });

	// Setup red
	m_redButton.setFillColor(RED);
	m_redButton.setPosition(sf::Vector2f{ 570.0f, 30.0f });

	// Setup yellow
	m_yellowButton.setFillColor(YELLOW);
	m_yellowButton.setPosition(sf::Vector2f{ 350.0f, 250.0f });

	// Setup blue
	m_blueButton.setFillColor(BLUE);
	m_blueButton.setPosition(sf::Vector2f{ 570.0f, 250.0f });
}

/// <summary>
/// Setup the font and text used in the game
/// </summary>
void Game::setupFontAndText()
{
	// Load font file
	if (m_impactFont.loadFromFile("assets/fonts/impact.ttf"))
	{
		std::cout << "Font loaded successfully" << std::endl;
	}

	// Setup the text object
	m_titleText.setFont(m_impactFont);
	m_titleText.setFillColor(WHITE);
	m_titleText.setCharacterSize(64);
	m_titleText.setPosition(50.0f, 30.0f);
	m_titleText.setString("S Z Y M O N");
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if ( sf::Event::Closed == event.type) // window message
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == event.type) //user key press
		{
			if (sf::Keyboard::Escape == event.key.code)
			{
				m_exitGame = true;
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);

	// Draw the squares
	m_window.draw(m_greenButton);
	m_window.draw(m_redButton);
	m_window.draw(m_yellowButton);
	m_window.draw(m_blueButton);

	// Draw the text
	m_window.draw(m_titleText);

	m_window.display();
}
