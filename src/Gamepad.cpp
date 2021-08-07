#include <Arduino.h>
#include "Gamepad.h"
#include "Constants.h"
#include "Functions.h"

Gamepad::Gamepad() {}

void Gamepad::begin() {
	pinMode(JOISTICK_AXIS_X_PIN, INPUT);
	pinMode(JOISTICK_AXIS_Y_PIN, INPUT);
	pinMode(JOISTICK_BUTTON_PIN, INPUT);
}

void Gamepad::tick() {
	this->fireButton.tick(); 
	this->bombButton.tick();
}

bool Gamepad::isBombButtonPress() {
	return this->bombButton.isPress();
}

bool Gamepad::isFireButtonPress() {
	return this->fireButton.isPress();
}

int Gamepad::readJoystickAxisX() {
	return analogRead(JOISTICK_AXIS_X_PIN);
}

int Gamepad::readJoystickAxisY() {
	return analogRead(JOISTICK_AXIS_Y_PIN);
}

double Gamepad::mapfJoystickAxisX(double out_min, double out_max) {
	return mapf(this->readJoystickAxisX(), 0, 1024, out_min, out_max);
}

double Gamepad::mapfJoystickAxisY(double out_min, double out_max) {
	return mapf(this->readJoystickAxisY(), 0, 1024, out_min, out_max);
}