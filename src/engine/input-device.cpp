#include "input-device.h"

// External dependencies
#include <algorithm>

KeyValue IInputDevice::getKey(KeyCode _keycode) const {
	return m_keys[_keycode];
}

bool IInputDevice::hasActivity() const {
	return m_activity;
}

void IInputDevice::beginUpdate() {
    m_activity = false;
}

void IInputDevice::setKey(KeyCode _keycode, KeyValue _value) {
    _value = std::clamp(_value, 0.0f, 1.0f);

    if (m_keys[_keycode] != _value) {
        m_keys[_keycode] = _value;
        m_activity = true;
    }
}

void IInputDevice::setKeyRaw(KeyCode _keycode, KeyValue value) {
    if (m_keys[_keycode] != value) {
        m_keys[_keycode] = value;
        m_activity = true;
    }
}