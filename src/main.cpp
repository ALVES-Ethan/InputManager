#include <SFML/Graphics.hpp>
#include "engine/input-manager.h"
#include <iostream>


int main() {
	sf::RenderWindow window(sf::VideoMode(960, 540), "Input Manager");
	window.setFramerateLimit(0);

	sf::CircleShape shape(60.0f);
	shape.setFillColor(sf::Color::Red);

	InputManager::init();

	InputManager::addAction("left"	,	{ Keyboard::Key::LEFT	});
	InputManager::addAction("right"	,	{ Keyboard::Key::RIGHT	});
	InputManager::addAction("up"	,	{ Keyboard::Key::UP		});
	InputManager::addAction("down"	,	{ Keyboard::Key::DOWN	});

	InputManager::addAction("jump"	,	{ Keyboard::Key::SPACE	});

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

		float x = InputManager::getAction("right") ? 1 : InputManager::getAction("left") ? -1 : 0;
		float y = InputManager::getAction("up") ? -1 : InputManager::getAction("down") ? 1 : 0;

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