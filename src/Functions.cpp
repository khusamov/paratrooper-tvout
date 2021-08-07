#include <math.h>
#include <TVout.h>
#include "Constants.h"

/**
 * Функция map, которая работает с числами типа float. 
 */
double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/**
 * Рисование окружности.
 * Штатная функция не работает, если окружность выходит за пределы экрана.
 */
void drawCircle(TVout tv, int x0, int y0, int radius) {
	int x = 0;
	int y = radius;
	int delta = 2 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		tv.setPixel(x0 + x, y0 + y, WHITE);
		tv.setPixel(x0 + x, y0 - y, WHITE);
		tv.setPixel(x0 - x, y0 + y, WHITE);
		tv.setPixel(x0 - x, y0 - y, WHITE);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

bool pointAngleIntoDia(int x, int y, int cx, int cy, float angleFrom, float angleTo) {
	x = x - cx;
	y = y - cy;
	float f = atan(y/x);
	return angleFrom > f && angleTo < f;
}

void setPixel(TVout tv, int x, int y, int cx, int cy, float angleFrom, float angleTo) {
	if (pointAngleIntoDia(x, y, cx, cy, angleFrom, angleTo)) {
		tv.setPixel(x, y, WHITE);
	}
}

/**
 * Рисование дуги.
 */
void drawArc(TVout tv, int x0, int y0, int radius, float angleFrom, float angleTo) {
	int x = 0;
	int y = radius;
	int delta = 2 - 2 * radius;
	int error = 0;
	while (y >= 0) {
		setPixel(tv, x0 + x, y0 + y, x0, y0, angleFrom, angleTo);
		setPixel(tv, x0 + x, y0 - y, x0, y0, angleFrom, angleTo);
		setPixel(tv, x0 - x, y0 + y, x0, y0, angleFrom, angleTo);
		setPixel(tv, x0 - x, y0 - y, x0, y0, angleFrom, angleTo);
		error = 2 * (delta + y) - 1;
		if (delta < 0 && error <= 0) {
			++x;
			delta += 2 * x + 1;
			continue;
		}
		error = 2 * (delta - x) - 1;
		if (delta > 0 && error > 0) {
			--y;
			delta += 1 - 2 * y;
			continue;
		}
		++x;
		delta += 2 * (x - y);
		--y;
	}
}

/**
 * Проверка точки: вышла ли она за пределы экрана или нет.
 */
bool pointOffScreen(int x, int y) {
	return (
		false
		|| x > SCREEN_WIDTH 
		|| x < 0 
		|| y > SCREEN_HEIGHT 
		|| y < 0
	);
}

/**
 * Координаты точки.
 */
struct Coords {
	float x; 
	float y;
};

/**
 * Поворот точки.
 * https://bit.ly/2VKEGFc
 */
Coords rotate(float x, float y, float angle) {
	Coords result;
	result.x = x * cos(angle) - y * sin(angle);
	result.y = x * sin(angle) + y * cos(angle);
	return result;
}