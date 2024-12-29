#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


int main() {

	// Initialize player position and angle
	sf::Vector2 playerPos(50.0f, 50.0f);
	sf::Vector2 playerVision(1.0f, 0.0f);
	// sf::Angle camAngle = sf::degrees(0); // Measured from typical x-axis, and clockwise (rather than typical CCW)

	// Create a temporary quad. In particular, these are just two points, a left and right
	sf::Vector2 quadLeft(100.0f, 49.5f);
	sf::Vector2 quadRight(100.0f, 50.5f);

	// Create the clock (this will be used for calculating deltaTime, which is the time between frames)
	sf::Clock clock;
	sf::Time deltaTime; // I must multiply everything by deltaTime. Otherwise, I am committing a crime

	// Create the level layout
	/*
	int levelLayout[5][5] = {
	{1, 1, 1, 1, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1}
	};*/
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
		sf::Angle deltaCamAngle = sf::degrees(15*deltaTime.asSeconds());
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
		double playerSpeed = 12*deltaTime.asSeconds();
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
		// Step 2: Determine the angles between the playerVision and each displacement.
		sf::Angle quadLeftAngle = playerVision.angleTo(displacementLeft);
		sf::Angle quadRightAngle = playerVision.angleTo(displacementRight);
		// Step 3: Save the apparent height of each edge of the quad based on the displacement.
		// float apparentHeightLeft = 100/(abs(std::cos(quadLeftAngle.asRadians()))*displacementLeft.length());
		// float apparentHeightRight = 100/(abs(std::cos(quadRightAngle.asRadians()))*displacementRight.length());
		float apparentHeightLeft = 500/(displacementLeft.length());
		float apparentHeightRight = 500/(displacementRight.length());
	
		// Step 4: Convert the view angle to a place on screen
		sf::ConvexShape quadDrawn;
		quadDrawn.setPointCount(4);
		
		quadDrawn.setPoint(0, {8.0f*quadLeftAngle.asDegrees()+320, 180-0.5f*apparentHeightLeft});
		quadDrawn.setPoint(1, {8.0f*quadLeftAngle.asDegrees()+320, 180+0.5f*apparentHeightLeft});
		quadDrawn.setPoint(2, {8.0f*quadRightAngle.asDegrees()+320, 180+0.5f*apparentHeightRight});
		quadDrawn.setPoint(3, {8.0f*quadRightAngle.asDegrees()+320, 180-0.5f*apparentHeightRight});
		
		/*
		quadDrawn.setPoint(0, {20.f, 20.f});
		quadDrawn.setPoint(1, {20.f, 340.f});
		quadDrawn.setPoint(2, {620.f, 300.f});
		quadDrawn.setPoint(3, {620.f, 60.f});
		*/
		quadDrawn.setFillColor(sf::Color::Green);

		// Print debug information if Z is being pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			std::cout << "DEBUG:\n";
			std::cout << "X position is:      " << playerPos.x << "\n";
			std::cout << "Y position is:      " << playerPos.y << "\n";
			std::cout << "Camr angle is:      " << playerVision.angle().asDegrees() << "\n";
			std::cout << "LeftDisplacementX:  " << displacementLeft.x << "\n";
			std::cout << "LeftDisplacementY:  " << displacementLeft.y << "\n";
			std::cout << "RightDisplacementX: " << displacementRight.x << "\n";
			std::cout << "RightDisplacementY: " << displacementRight.y << "\n";
			std::cout << "QuadLeftAngle:      " << quadLeftAngle.asDegrees() << "\n";
			std::cout << "QuadRightAngle:     " << quadRightAngle.asDegrees() << "\n";
			std::cout << "ApparHeightLeft:    " << apparentHeightLeft << "\n";
			std::cout << "ApparHeightRight:   " << apparentHeightRight << "\n";
			std::cout << "Quad corner screencoords:\n";
			std::cout << "0. X: " << 8.0f*quadLeftAngle.asDegrees()+320 << " Y: " << 180-0.5f*apparentHeightLeft << "\n";
			std::cout << "1. X: " << 8.0f*quadLeftAngle.asDegrees()+320 << " Y: " << 180+0.5f*apparentHeightLeft << "\n";
			std::cout << "2. X: " << 8.0f*quadRightAngle.asDegrees()+320 << " Y: " << 180+0.5f*apparentHeightRight << "\n";
			std::cout << "3. X: " << 8.0f*quadRightAngle.asDegrees()+320 << " Y: " << 180-0.5f*apparentHeightRight << "\n";

		}

		// The last step in the loop is to actually draw everything to the screen. 
		// Each frame, assuming the window wasn't closed, run these lines: 
		window.clear(); // 1. Clear the framebuffer

		// 2. Draw everything into the framebuffer that you must
		window.draw(quadDrawn); 
		
		window.display(); // 3. Draw the framebuffer

		deltaTime = clock.restart(); // 4. Save the deltaTime and restart the clock
	}
	return 0; // Return a normal exit code. Don't think this is necessary but it's ok.
}

