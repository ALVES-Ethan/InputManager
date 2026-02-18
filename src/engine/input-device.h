#pragma once

#include <array>

using KeyCode = unsigned char;
using KeyValue = float;

class IInputDevice {
public:
	virtual ~IInputDevice() = default;

	virtual void update() = 0;

	KeyValue getKey(KeyCode _keycode) const;
	bool hasActivity() const;

protected:
    void beginUpdate();

    void setKey(KeyCode _code, KeyValue _value);
	void setKeyRaw(KeyCode _code, KeyValue _value);

protected:
	std::array<KeyValue, 256> m_keys = {};
	bool m_activity = false;
};