#include <SFML/Graphics.hpp>

#include "engine/devices/keyboard-device.h"

int main() {
	sf::RenderWindow window(sf::VideoMode(960, 540), "Input Manager");
	window.setFramerateLimit(0);

	sf::CircleShape shape(60.0f);
	shape.setFillColor(sf::Color::Red);

	Keyboard keyboard;

	sf::Clock delta;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::Resized) {
				window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
			}
		}

		float deltaTime = delta.restart().asSeconds();

		keyboard.update();

		float speed = deltaTime * 512.0f;

		float y = keyboard.getKey((unsigned char)Keyboard::Key::UP) > 0 ? -1 :
			keyboard.getKey((unsigned char)Keyboard::Key::DOWN) ? 1 : 0;

		float x = keyboard.getKey((unsigned char)Keyboard::Key::LEFT) > 0 ? -1 :
			keyboard.getKey((unsigned char)Keyboard::Key::RIGHT) ? 1 : 0;

		shape.move({x * speed, y * speed });

		window.clear();

		window.draw(shape);

		window.display();
	}
	return 0;
}