#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

int main() {

	// Initialize player position and angle
	double playerX = 50;
	double playerY = 50;
	sf::Angle camAngle = sf::degrees(0); // Measured from typical x-axis, and clockwise (rather than typical CCW)

	// Create the clock (this will be used for calculating deltaTime, which is the time between frames)
	sf::Clock clock;
	sf::Time deltaTime; // I must multiply everything by deltaTime. Otherwise, I am committing a crime

	// Create the level layout
	int levelLayout[5][5] = {
	{1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1}
	};
	// Create the window
	sf::RenderWindow window(sf::VideoMode({640, 360}), "FeedTheBeast");
	sf::CircleShape shape(180.f); // This (temporary) line creates a variable called shape which is a circle of radius 180
	shape.setFillColor(sf::Color::Green); // This (temporary) line fills the circle green
	shape.setPosition({140, 0}); // This (temporary) line positions the circle such that it's in the middle of the screen

	while (window.isOpen()) { // Run as long as the window is open
		while (const std::optional event = window.pollEvent()) { // Check all of the window's events...
			if (event->is<sf::Event::Closed>()) // ... and if one of the events was to close the window...
			window.close(); // ... close the window
		}

		// (DEBUG) print the deltaTime
		// std::cout << "deltaTime is " << deltaTime.asSeconds() << "\n";

		// Define deltaCamAngle, the amount that CamAngle should change each frame
		sf::Angle deltaCamAngle = sf::degrees(5*deltaTime.asSeconds());
		// Change the camera orientation based on left/right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			camAngle-=deltaCamAngle;
			std::cout << "Camr angle is: " << camAngle.asDegrees() << "\n";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			camAngle+=deltaCamAngle;
			std::cout << "Camr angle is: " << camAngle.asDegrees() << "\n";
		}

		// Velocity magnitude
		double playerSpeed = 5*deltaTime.asSeconds();
		// Change the camera position based on WASD. Or, I guess, just W in this case. 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			playerX += std::cos(camAngle.asRadians())*playerSpeed;
			playerY += std::sin(camAngle.asRadians())*playerSpeed;

			std::cout << "X position is: " << playerX << "\n";
			std::cout << "Y position is: " << playerY << "\n";
			
		}

		// Each frame, assuming the window wasn't closed, run these lines: 
		window.clear(); // 1. Clear the framebuffer

		// 2. Draw everything into the framebuffer that you must
		window.draw(shape); 
		
		window.display(); // 3. Draw the framebuffer

		deltaTime = clock.restart(); // 4. Save the deltaTime and restart the clock
	}
	return 0; // Return a normal exit code. Don't think this is necessary but it's ok.
}

