#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

double toRad(int degrees) {
	return degrees * M_PI/180;
}

int main() {

	// Initialize camera position and angle
	double camX = 50;
	double camY = 50;
	double camAngle = 0; // Measured from typical x-axis, and clockwise (rather than typical CCW)

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
		double deltaCamAngle = 5*deltaTime.asSeconds();
		// Change the camera orientation based on left/right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			camAngle-=deltaCamAngle;
			if(camAngle<0) {
				camAngle+=360;
			}
			std::cout << "Camr angle is: " << camAngle << "\n";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			camAngle+=deltaCamAngle;
			if(camAngle>360) {
				camAngle-=360;
			}
			std::cout << "Camr angle is: " << camAngle << "\n";
		}

		// Velocity magnitude
		double camSpeed = 5*deltaTime.asSeconds();
		// Change the camera position based on WASD. Or, I guess, just W in this case. 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			camX += cos(toRad(camAngle))*camSpeed;
			camY += sin(toRad(camAngle))*camSpeed;

			std::cout << "X position is: " << camX << "\n";
			std::cout << "Y position is: " << camY << "\n";
			
		}

		// Each frame, assuming the window wasn't closed, run these lines: 
		window.clear(); // 1. Clear the framebuffer

		// 2. Draw everything into the framebuffer that you must
		window.draw(shape); 
		
		window.display(); // 3. Draw the framebuffer

		deltaTime = clock.restart(); // 4. Save the deltaTime and restart the clock
	}
	return 0; // Return a normal exit code
}

