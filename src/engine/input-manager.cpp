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

void InputManager::addAxis(const char* _name, const Axis& _axis) {
    if (m_instance == nullptr) return;
    m_instance->m_axes[_name] = _axis;
}

float InputManager::getAxis(const char* _axis) {
    if (m_instance == nullptr) return false;
    auto it = m_instance->m_axes.find(_axis);
    if (it == m_instance->m_axes.end()) return false;

    KeyValue value = (m_instance->m_keyboard.getKey((KeyCode)it->second.keyboardPositiveBinding)
        - (m_instance->m_keyboard.getKey((KeyCode)it->second.keyboardNegativeBinding)));

    return static_cast<float>(value);
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