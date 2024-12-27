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
	int camAngle = 0; // Measured from typical x-axis, and clockwise (rather than typical CCW)

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

		// Change the camera orientation based on left/right input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			camAngle-=1;
			if(camAngle<0) {
				camAngle+=360;
			}
			std::cout << "Camr angle is: " << camAngle << "\n";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			camAngle+=1;
			if(camAngle>360) {
				camAngle-=360;
			}
			std::cout << "Camr angle is: " << camAngle << "\n";
		}

		// Change the camera position based on WASD
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			camX += cos(toRad(camAngle));
			camY += sin(toRad(camAngle));

			std::cout << "X position is: " << camX << "\n";
			std::cout << "Y position is: " << camY << "\n";

			/*
			camAngle+=1;
			if(camAngle>360) {
				camAngle-=360;
			}
			std::cout << camAngle << "\n";
			*/
		}

		// Each frame, assuming the window wasn't closed, run these lines: 
		window.clear(); // 1. Clear the framebuffer

		// 2. Draw everything into the framebuffer that you must
		window.draw(shape); 
		
		window.display(); // 3. Draw the framebuffer
	}
	return 0; // Return a normal exit code
}

