#include "mouse-device.h"

#include <windows.h>
#include <iostream>

void Mouse::update() {
	beginUpdate();

	// --- Update Buttons ---
	// Standard 3 buttons via GetAsyncKeyState
	SHORT leftState = GetAsyncKeyState(VK_LBUTTON);

	setKey(static_cast<KeyCode>(Key::BUTTON_LEFT), (leftState & 0x8000) ? 1.0f : 0.0f);

	SHORT rightState = GetAsyncKeyState(VK_RBUTTON);
	setKey(static_cast<KeyCode>(Key::BUTTON_RIGHT), (rightState & 0x8000) ? 1.0f : 0.0f);

	SHORT middleState = GetAsyncKeyState(VK_MBUTTON);
	setKey(static_cast<KeyCode>(Key::BUTTON_MIDDLE), (middleState & 0x8000) ? 1.0f : 0.0f);

	// Extended buttons (X1, X2)
	SHORT x1State = GetAsyncKeyState(VK_XBUTTON1);
	setKey(static_cast<KeyCode>(Key::BUTTON_3), (x1State & 0x8000) ? 1.0f : 0.0f);

	SHORT x2State = GetAsyncKeyState(VK_XBUTTON2);
	setKey(static_cast<KeyCode>(Key::BUTTON_4), (x2State & 0x8000) ? 1.0f : 0.0f);

	// --- Update Movement Deltas ---
	POINT currentPos;
	GetCursorPos(&currentPos);

	float currentX = static_cast<float>(currentPos.x);
	float currentY = static_cast<float>(currentPos.y);

	static bool first = true;
	if (first) {
		m_lastX = currentX;
		m_lastY = currentY;
		first = false;
	}

	float deltaX = currentPos.x - m_lastX;
	float deltaY = currentPos.y - m_lastY;

	// Set directional keys based on delta
	setKey(static_cast<KeyCode>(Key::DELTA_RIGHT),	(deltaX > 0.0f) ? deltaX : 0.0f);
	setKey(static_cast<KeyCode>(Key::DELTA_LEFT),	(deltaX < 0.0f) ? -deltaX : 0.0f);
	setKey(static_cast<KeyCode>(Key::DELTA_UP),		(deltaY < 0.0f) ? -deltaY : 0.0f);
	setKey(static_cast<KeyCode>(Key::DELTA_DOWN),	(deltaY > 0.0f) ? deltaY : 0.0f);

	m_lastX = currentX;
	m_lastY = currentY;

	// --- Update Scroll Wheel ---
	// Scroll values are accumulated from WndProc WM_MOUSEWHEEL messages
	// Here we just commit the accumulated value and reset
	if (m_accumulatedScroll > 0) {
		setKey(static_cast<KeyCode>(Key::SCROLL_UP), 1.0f);
		setKey(static_cast<KeyCode>(Key::SCROLL_DOWN), 0.0f);
	}
	else if (m_accumulatedScroll < 0) {
		setKey(static_cast<KeyCode>(Key::SCROLL_UP), 0.0f);
		setKey(static_cast<KeyCode>(Key::SCROLL_DOWN), 1.0f);
	}
	else {
		setKey(static_cast<KeyCode>(Key::SCROLL_UP), 0.0f);
		setKey(static_cast<KeyCode>(Key::SCROLL_DOWN), 0.0f);
	}
	m_accumulatedScroll = 0;

	endUpdate();
}