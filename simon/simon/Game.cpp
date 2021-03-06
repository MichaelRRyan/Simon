// @Author Michael Rainsford Ryan
// @Date 07/12/2018
// Estimated time: 180m
// Session 1: 09:45 - 11:03 - 07/12/2018

#include "Game.h"
#include <iostream>



Game::Game() :
	m_window{ sf::VideoMode{ 800, 600, 32 }, "Simon" },
	m_exitGame{ false }, //when true game will exit

	// Setup the size of the buttons
	m_redButton{ sf::Vector2f{ 200.0f, 200.0f } },
	m_greenButton{ sf::Vector2f{ 200.0f, 200.0f } },
	m_blueButton{ sf::Vector2f{ 200.0f, 200.0f } },
	m_yellowButton{ sf::Vector2f{ 200.0f, 200.0f } },
	
	// Initiate the game state
	m_currentGameMode{ GameMode::Starting }
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

	// Setup green message - easy game - 8
	m_instructionsTextGreen.setFont(m_impactFont);
	m_instructionsTextGreen.setFillColor(GREEN);
	m_instructionsTextGreen.setCharacterSize(32);
	m_instructionsTextGreen.setPosition(50.0f, 100.0f);
	m_instructionsTextGreen.setString("Press green for \n an easy game");

	// Setup red message - medium game - 16
	m_instructionsTextRed.setFont(m_impactFont);
	m_instructionsTextRed.setFillColor(RED);
	m_instructionsTextRed.setCharacterSize(32);
	m_instructionsTextRed.setPosition(50.0f, 200.0f);
	m_instructionsTextRed.setString("Press red for \n a medium game");

	// Setup yellow message - hard game - 32
	m_instructionsTextYellow.setFont(m_impactFont);
	m_instructionsTextYellow.setFillColor(YELLOW);
	m_instructionsTextYellow.setCharacterSize(32);
	m_instructionsTextYellow.setPosition(50.0f, 300.0f);
	m_instructionsTextYellow.setString("Press yellow for \n a hard game");

	// Setup blue message - exit game
	m_instructionsTextBlue.setFont(m_impactFont);
	m_instructionsTextBlue.setFillColor(BLUE);
	m_instructionsTextBlue.setCharacterSize(32);
	m_instructionsTextBlue.setPosition(50.0f, 400.0f);
	m_instructionsTextBlue.setString("Press blue for \n exit game");

	// Setup status text
	m_statusText.setFont(m_impactFont);
	m_statusText.setFillColor(WHITE);
	m_statusText.setCharacterSize(22);
	m_statusText.setPosition(500.0f, 453.0f);
	m_statusText.setString(""); // No status on the menu screen
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
	const int COL_1_LEFT = 350;
	const int COL_1_RIGHT = 550;
	const int COL_2_LEFT = 570;
	const int COL_2_RIGHT = 770;
	const int ROW_1_TOP = 20;
	const int ROW_1_BOTTOM = 230;
	const int ROW_2_TOP = 250;
	const int ROW_2_BOTTOM = 450;

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
		// Check if the event is a mouse button release
		if (sf::Event::MouseButtonReleased == event.type)
		{
			// Check if it's on the first column
			if (event.mouseButton.x > COL_1_LEFT && event.mouseButton.x < COL_1_RIGHT)
			{
				// Check which row
				if (event.mouseButton.y > ROW_1_TOP && event.mouseButton.y < ROW_1_BOTTOM)
				{
					m_greenButtonPressed = true;
				}
				if (event.mouseButton.y > ROW_2_TOP && event.mouseButton.y < ROW_2_BOTTOM)
				{
					m_yellowButtonPressed = true;
				}
			}
			// Check if it's on the second column
			if (event.mouseButton.x > COL_2_LEFT && event.mouseButton.x < COL_2_RIGHT)
			{
				// Check which row
				if (event.mouseButton.y > ROW_1_TOP && event.mouseButton.y < ROW_1_BOTTOM)
				{
					m_redButtonPressed = true;
				}
				if (event.mouseButton.y > ROW_2_TOP && event.mouseButton.y < ROW_2_BOTTOM)
				{
					m_blueButtonPressed = true;
				}
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

	switch (m_currentGameMode)
	{
	case GameMode::Showing:
		break;
	case GameMode::Recieving:
		break;
	case GameMode::GameOver:
		break;
	case GameMode::Starting:
		break;
	default:
		break;
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

	if (GameMode::Starting == m_currentGameMode) // Draw the instruction text if on the title screen
	{
		m_window.draw(m_instructionsTextBlue);
		m_window.draw(m_instructionsTextGreen);
		m_window.draw(m_instructionsTextRed);
		m_window.draw(m_instructionsTextYellow);
	}

	m_window.draw(m_statusText);

	m_window.display();
}
