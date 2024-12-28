#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


int main() {

	// Initialize player position and angle
	sf::Vector2 playerPos(50.0f, 50.0f);
	sf::Vector2 playerVision(1.0f, 0.0f);
	// sf::Angle camAngle = sf::degrees(0); // Measured from typical x-axis, and clockwise (rather than typical CCW)

	// Create a temporary quad. In particular, these are just two points, a left and right
	sf::Vector2 quadLeft(100.0f, 40.0f);
	sf::Vector2 quadRight(100.0f, 60.0f);

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
			playerVision = playerVision.rotatedBy(-1.0*deltaCamAngle);
			std::cout << "Camr angle is: " << playerVision.angle().asDegrees() << "\n";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			playerVision = playerVision.rotatedBy(deltaCamAngle);
			std::cout << "Camr angle is: " << playerVision.angle().asDegrees() << "\n";
		}

		// Velocity magnitude
		double playerSpeed = 5*deltaTime.asSeconds();
		// Change the camera position based on WASD. Or, I guess, just W in this case. 
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			playerPos.x += std::cos(playerVision.angle().asRadians())*playerSpeed;
			playerPos.y += std::sin(playerVision.angle().asRadians())*playerSpeed;

			std::cout << "X position is: " << playerPos.x << "\n";
			std::cout << "Y position is: " << playerPos.y << "\n";
			
		}

		// Here, we'll place the logic to allow our sample quad to be rendered
		// Step 1: Determine the displacement vectors between the player and the left/right edges of the quad.
		sf::Vector2 displacementLeft = quadLeft-playerPos;
		sf::Vector2 displacementRight = quadRight-playerPos;
		// Step 2: Save the apparent height of each edge of the quad based on the displacement.
		float apparentHeightLeft = 100/displacementLeft.length();
		float apparentHeightRight = 100/displacementRight.length();
		// Step 3: Determine the angles between the playerVision and each displacement.
		sf::Angle quadLeftAngle = playerVision.angleTo(displacementLeft);
		sf::Angle quadRightAngle = playerVision.angleTo(displacementRight);
		// (DEBUG): Print the quadLeftAngle and quadRightAngle
		std::cout << "LAngle: " << quadLeftAngle.asDegrees() << "\n";
		std::cout << "RAngle: " << quadRightAngle.asDegrees() << "\n";
		// Step 4: Convert the view angle to a place on screen

		// The last step in the loop is to actually draw everything to the screen. 
		// Each frame, assuming the window wasn't closed, run these lines: 
		window.clear(); // 1. Clear the framebuffer

		// 2. Draw everything into the framebuffer that you must
		// window.draw(shape); 
		
		window.display(); // 3. Draw the framebuffer

		deltaTime = clock.restart(); // 4. Save the deltaTime and restart the clock
	}
	return 0; // Return a normal exit code. Don't think this is necessary but it's ok.
}

