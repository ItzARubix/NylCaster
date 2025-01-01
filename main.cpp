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

class Wall {
	public:
		sf::Vector2<float> left;
		sf::Vector2<float> right;
		Wall() : left(10.f, -5.f), right(10.f, 5.f) {
			// This is temporary. Will edit this to give real coords to the wall later.
		}
		~Wall() {

		}
};


int main() {

	// It is helpful to imagine the window as existing in worldspace. I precalculated this on paper, but this number is dependent on the FOV, so I might have to change it later.
	constexpr float camToScreenDistance = 180/std::tan(2*M_PI/9);
	
	// Create a player.
	Player player;

	// (TEMP) Create a wall. 
	Wall wall;

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
		// It should be noted that this is essentially just deltaX = velocity*deltaTime, 
		// which you should know from physics class.

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
			std::cout << "camToScreenDistance: " << camToScreenDistance << "\n";
		}

		// This is the "draw step". It's where we actually draw everything to the screen.
		// 1. Clear the framebuffer.
		window.clear();

		// 2. Draw everything to the framebuffer that you must.
		// RAYCASTING LOGIC.
		// This takes place in a for-loop, where each iteration represents one column of pixels on the window. 
		// In particular, as you shall see, the for-loop iterates from i=-180 to i=180, and the actual column being drawn to is i+180 (because the range of columns on screen is 0 to 360).
		// We also have to calculate, based on the current iteration, what the angle that the ray should be cast at. Note that this is NOT a linear scale, and involves a teeny bit of trig.
		for(int i=-180; i<=180; i++) {
			sf::Angle rayDirectionAngle = sf::radians(std::atan(i/camToScreenDistance));
			sf::Vector2 ray = 100.f*player.vision.rotatedBy(rayDirectionAngle);
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X)) {
				std::cout << "For iteration " << i << " the rayDirectionAngle is " << rayDirectionAngle.asDegrees() << "\n";
			}
			
			// IT'S TIME FOR THE WORST VARIABLE NAMES KNOWN TO MANKIND YAYYYY
			// For the sake of not obfuscating what I'm doing here, https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line_segment
			// Godspeed
			float x_1 = player.position.x;
			float y_1 = player.position.y;
			float x_2 = x_1 + ray.x;
			float y_2 = y_1 + ray.y;
			float x_3 = wall.left.x;
			float y_3 = wall.left.y;
			float x_4 = wall.right.x;
			float y_4 = wall.right.y;
			float t_numerator = ((x_1-x_3)*(y_3-y_4)) - ((y_1-y_3)*(x_3-x_4));
			float t_denominator = ((x_1-x_2)*(y_3-y_4)) - ((y_1-y_2)*(x_3-x_4));
			float s_numerator = ((x_1-x_2)*(y_1-y_3)) - ((y_1-y_2)*(x_1-x_3));
			float s_denominator = ((x_1-x_2)*(y_3-y_4)) - ((y_1-y_2)*(x_3-x_4));
			// The names are only slightly misleading:
			// t is equal to t_numerator/t_denominator,
			// but s is equal to the negative of s_numerator/s_denominator.
			// There's no good reason to include the negative sign in the numerator over the denominator or vice versa,
			// so I didn't bother. When I define s I'll just include the negative sign there.
			if()
		}

		// 3. Draw the framebuffer.
		window.display();

		// 4. Save the deltaTime and restart the clock.
		deltaTime = clock.restart();
	}

	return 0;
}
