#include "Gun.h"
#include "Constants.h"

Gun::Gun(TVout *tv) : Object(tv) {}

void Gun::draw() {
	int gun_length1 = 15;
	int gun_x1 = SCREEN_WIDTH / 2;
	int gun_y1 = SCREEN_HEIGHT;
	int gun_x2 = gun_length1 * cos(this->angle) + SCREEN_WIDTH / 2;
	int gun_y2 = SCREEN_HEIGHT - gun_length1 * sin(this->angle);
	this->tv->drawLine(gun_x1, gun_y1, gun_x2, gun_y2, WHITE);
}

float Gun::getAngle() {
	return this->angle;
}

void Gun::changeAngle(float angle) {
	this->angle += angle;
	if (this->angle >= 2 * PI) this->angle = 0;
}