#include <SFML/Graphics.hpp>
#include "engine/input-manager.h"
#include <iostream>


int main() {
	sf::RenderWindow window(sf::VideoMode(960, 540), "Input Manager");
	window.setFramerateLimit(0);

	sf::CircleShape shape(60.0f);
	shape.setFillColor(sf::Color::Red);

	InputManager::init();

	InputManager::addAxis("horizontal"	,	{ Keyboard::Key::RIGHT, Keyboard::Key::LEFT , Mouse::Key::DELTA_RIGHT, Mouse::Key::DELTA_LEFT});
	InputManager::addAxis("vertical"	,	{ Keyboard::Key::UP, Keyboard::Key::DOWN, Mouse::Key::DELTA_UP, Mouse::Key::DELTA_DOWN });

	InputManager::addAction("jump"		,	{ Keyboard::Key::SPACE, Mouse::Key::BUTTON_LEFT	});

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

		InputManager::update();

		float speed = deltaTime * 512.0f;

		float x = InputManager::getAxis("horizontal");
		float y = -InputManager::getAxis("vertical");

		if (InputManager::getActionDown("jump")) {
			std::cout << "JUMPED !" << std::endl;
		}
		
		shape.move({x * speed, y * speed });

		window.clear();

		window.draw(shape);

		window.display();
	}
	return 0;
}