#pragma once

#include "../input-device.h"

class Mouse : public IInputDevice {
public:
	enum class Key : KeyCode {
		NONE = 0,

		// Buttons
		BUTTON_LEFT = 1,
		BUTTON_RIGHT = 2,
		BUTTON_MIDDLE = 3,
		BUTTON_3 = 4,
		BUTTON_4 = 5,
		BUTTON_5 = 6,
		BUTTON_6 = 7,
		BUTTON_7 = 8,
		BUTTON_8 = 9,

		// Movement Delta
		DELTA_UP = 10,
		DELTA_DOWN = 11,
		DELTA_LEFT = 12,
		DELTA_RIGHT = 13,

		// Scroll Wheel
		SCROLL_UP = 14,
		SCROLL_DOWN = 15,
	};

	static void lock();
	static void unlock();

	virtual void update(float _delta, Rect _viewport) override;

private:
	static bool m_locked; // TO DO : make it non static
	float m_lastX = 0;
	float m_lastY = 0;
	int m_accumulatedScroll = 0;
};