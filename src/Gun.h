#pragma once
#include <Arduino.h>
#include "Object.h"

/**
 * Пушка.
 */
class Gun : Object {
	public:
		Gun(TVout *tv);
		void update();
		void draw();
		float getAngle();
		void changeAngle(float angle);
	private:
		float angle = PI / 2;
};