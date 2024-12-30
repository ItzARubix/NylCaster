#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

// Let it be known that I thusly have no idea how classes work in C++ lol. 

class Player { // Player class might be moved to a new file at some point. This is just for organization's sake.
	public:
		sf::Vector2<float> position;
		sf::Vector2<float> velocity;
		sf::Vector2<float> vision;
		Player() : position(0.f, 0.f), velocity(0.f, 0.f), vision(1.f, 0.f) {
			
		}
		~Player() {
			
		}
};


int main() {
	
	// Create a player.
	Player player;

	// Create the clock and a time variable to store deltaTime.
	sf::Clock clock;
	sf::Time deltaTime;

	// Create the window.
	sf::RenderWindow window(sf::VideoMode({640,360}), "FeedTheBeast");

	while (window.isOpen()) { // Primary execution loop. This will run for as long as the window is open. 

		while (const std::optional event = window.pollEvent()) { // This while-loop condition will only fail if there are no events left in the window.pollEvent() queue. Thus, for each iteration of this loop, until it fails, it pops one event off the queue, and holds onto it in the event variable...

			if (event->is<sf::Event::Closed>()) { // ... and if that event is sf::Event::Closed...
				window.close(); // ... close the window.
			}

		} // If the program makes it out of this loop, that means we can start the actual logic of the frame.

		// CAMERA LOGIC.
		// 1. Define deltaCamAngle, the amount that CamAngle should change each frame.
		sf::Angle deltaCamAngle = sf::degrees(15*deltaTime.asSeconds());
		// 2. If the player presses Left, the vision vector should be rotated negatively by deltaCamAngle.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
			player.vision = player.vision.rotatedBy(-1.f*deltaCamAngle);
		}
		// 3. If the player presses Right, the vision vector should be rotated positively by deltaCamAngle.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
			player.vision = player.vision.rotatedBy(deltaCamAngle);
		}

		// VELOCITY LOGIC.
		// 1. Define playerSpeed, a scalar that we'll use to ensure the magnitude of the player velocity remains consistent.
		float playerSpeed = 12.f;
		// 2. Create a temporary vector that encodes all the directional information about the player movement.
		sf::Vector2 velocityDirection(0.f, 0.f);
		// 3. Forward/backward direction is governed by player.vision.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
			velocityDirection += player.vision;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
			velocityDirection -= player.vision;
		}
		// 4. Strafing is governed by a vector orthogonal to player.vision, which we define and then use.
		sf::Vector2 strafeVector = player.vision.rotatedBy(sf::degrees(90));
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
			velocityDirection += strafeVector;
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
			velocityDirection -= strafeVector;
		}
		// 5. We want player.velocity to be in the direction of velocityDirection and with the magnitude of playerSpeed.
		if(velocityDirection.lengthSquared()!=0) {
			player.velocity = playerSpeed*velocityDirection.normalized();
		} else {
			player.velocity = velocityDirection;
		}

		// POSITION LOGIC.
		// 1. Add the player's velocity to their position, scaled by deltaTime.
		player.position += deltaTime.asSeconds()*player.velocity;

		// (DEBUG) print all information about player if they press Z.
		// This is done at the end, right before the draw step. 
		// This is because we want the debug info to reflect changes made in the current frame.
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Z)) {
			std::cout << "DEBUG: \n";
			std::cout << "Player position: \n";
			std::cout << "X: " << player.position.x << " Y: " << player.position.y << "\n";
			std::cout << "Player velocity: \n";
			std::cout << "X: " << player.velocity.x << " Y: " << player.velocity.y << "\n";
			std::cout << "Player vision: \n";
			std::cout << "X: " << player.vision.x << " Y: " << player.vision.y << "\n";
			std::cout << "Player angle (relative to positive X): " << player.vision.angle().asDegrees() << "\n";
			std::cout << "deltaTime: " << deltaTime.asSeconds() << "\n";
		}

		// This is the "draw step". It's where we actually draw everything to the screen.
		// 1. Clear the framebuffer.
		window.clear();

		// 2. Draw everything to the framebuffer that you must.
		// window.draw(shape);

		// 3. Draw the framebuffer.
		window.display();

		// 4. Save the deltaTime and restart the clock.
		deltaTime = clock.restart();
	}

	return 0;
}
