// @Author Michael Rainsford Ryan

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupButtons(); // Setup all button properties
	void setupFontAndText(); // Load font files and setup text

	// Setup the colours for the buttons
	const sf::Color RED{ 255, 85, 85, 255 };
	const sf::Color GREEN{ 85, 255, 85, 255 };
	const sf::Color BLUE{ 85, 85, 255, 255 };
	const sf::Color YELLOW{ 255, 255, 85, 255 };
	const sf::Color WHITE{ 255, 255, 255, 255 };


	sf::RenderWindow m_window; // main SFML window
	
	// Setup the font
	sf::Font m_ArialBlackfont; // font used by message
	sf::Font m_impactFont; // Main font used for the game

	// Setup the text
	sf::Text m_titleText; // Text object for the title
	sf::Text m_instructionsTextBlue; // Text for blue instructions
	sf::Text m_instructionsTextRed; // Text for red instructions
	sf::Text m_instructionsTextGreen; // Text for green instructions
	sf::Text m_instructionsTextYellow; // Text for yellow instructions
	sf::Text m_statusText; // Text for the game status
	
	bool m_exitGame; // control exiting game

	sf::RectangleShape m_redButton; // Big oul' red button in the game
	sf::RectangleShape m_greenButton; // Big oul' green button in the game
	sf::RectangleShape m_blueButton; // Big oul' blue button in the game
	sf::RectangleShape m_yellowButton; // Big oul' yellow button in the game
};

#endif // !GAME

