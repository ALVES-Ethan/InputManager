#pragma once

#include "input-device.h"
#include "devices/keyboard-device.h"

#include <unordered_map>
#include <string>

struct Action {
	Keyboard::Key keyboardBinding = Keyboard::Key::NONE;
};

class InputManager {
public:
	static void init();

	static void addAction(const char* _name, const Action& _action);

	static bool getAction(const char* _action);
	static bool getActionDown(const char* _action);
	static bool getActionUp(const char* _action);

	static void update();

private:
	static InputManager* m_instance;

	std::unordered_map<std::string, Action> m_actions;

	// Devices
	Keyboard m_keyboard;
};