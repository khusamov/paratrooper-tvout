#pragma once
#include <TVout.h>

/**
 * Размеры экрана.
 * Максимальные размеры, при которых сохраняются 
 * нормальные пропорции, составляют: 127x86 пикселов.
 * Оптимальные для данной игры: 120x80 пикселов.
 * 128,96
 */
#define SCREEN_WIDTH 120
#define SCREEN_HEIGHT 80
#define TV_MODE PAL

/**
 * Подключение джойстика.
 */
#define JOISTICK_AXIS_X_PIN A0
#define JOISTICK_AXIS_Y_PIN A1
#define JOISTICK_BUTTON_PIN 4

#define FIRE_BUTTON_PIN 2
#define BOMB_BUTTON_PIN 3