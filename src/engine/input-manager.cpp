#include "input-manager.h"

#include <iostream>

InputManager* InputManager::m_instance = nullptr;

void InputManager::init() {
    if (m_instance != nullptr) {
        std::cout << "WARNING : You cannot initialize the InputManager two times ! \n";
        return;
    }

    m_instance = new InputManager();
}

void InputManager::update() {
    if (m_instance == nullptr) return;
    m_instance->m_keyboard.update();
}

void InputManager::addAction(const char* _name, const Action& _action) {
    if (m_instance == nullptr) return;
    m_instance->m_actions[_name] = _action;
}

bool InputManager::getAction(const char* _action) {
    if (m_instance == nullptr) return false;
    auto it = m_instance->m_actions.find(_action);
    if (it == m_instance->m_actions.end()) return false;

    return (m_instance->m_keyboard.getKey((KeyCode)it->second.keyboardBinding) > 0.0f);
}

bool InputManager::getActionDown(const char* _action) {
    if (m_instance == nullptr) return false;
    auto it = m_instance->m_actions.find(_action);
    if (it == m_instance->m_actions.end()) return false;

    return (m_instance->m_keyboard.getKeyDown((KeyCode)it->second.keyboardBinding) > 0.0f);
}

bool InputManager::getActionUp(const char* _action) {
    if (m_instance == nullptr) return false;
    auto it = m_instance->m_actions.find(_action);
    if (it == m_instance->m_actions.end()) return false;

    return (m_instance->m_keyboard.getKeyUp((KeyCode)it->second.keyboardBinding) > 0.0f);
}