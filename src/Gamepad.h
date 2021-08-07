#pragma once

// https://github.com/GyverLibs/EncButton/issues/3
#define EB_DEB 30

#include <Arduino.h>
#include <EncButton.h>
#include "Constants.h"

/**
 * Контроллер ввода команд в игру.
 */
class Gamepad {
	public:
		Gamepad();
		void begin();
		void tick();
		bool isFireButtonPress();
		bool isBombButtonPress();
		int readJoystickAxisX();
		int readJoystickAxisY();
		double mapfJoystickAxisX(double out_min, double out_max);
		double mapfJoystickAxisY(double out_min, double out_max);
	private:
		EncButton<EB_TICK, FIRE_BUTTON_PIN> fireButton;
		EncButton<EB_TICK, BOMB_BUTTON_PIN> bombButton;
};