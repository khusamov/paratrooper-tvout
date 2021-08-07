#include <Arduino.h>

#include <TVout.h>
#include <fontALL.h>

#include "MemoryFree.h"

#include "Constants.h"
#include "Functions.h"

#include "Gamepad.h"
#include "Gun.h"
#include "Bullet.h"
#include "BulletList.h"
#include "AmmuWagonImage.h"

TVout tv;
Gamepad gamepad;
BulletList bulletList;
Gun gun(&tv);

float gun_angle = PI / 2;
int fireCounter = 100;
int bombCounter = 30;
int ammuWagonX = 0;
int ammuWagonSpeedX = 1;

Bullet *currentBullet = nullptr;

void draw();
void update();

void setup() {
	Serial.begin(9600);
	Serial.print(F("Free: "));
	Serial.println(freeMemory());
	tv.begin(TV_MODE, SCREEN_WIDTH, SCREEN_HEIGHT);
	tv.selectFont(font6x8);
	gamepad.begin();
}

void gameLoop() {
	// Serial.print(F("Free: "));
	// Serial.println(freeMemory());
	update();
	tv.clearScreen();
	draw();
	//tv.forceVscale(2);
	tv.delayFrame(1);
	//tv.delay(100);
}

long current_time = 0;

void loop() {
	gameLoop();
	// if (millis() - current_time > 1000 / 15) {
	// 	current_time = millis();
	// 	gameLoop();
	// }
}

// char vscale = 4;

void update() {
	gamepad.tick(); 

	// tv.forceVscale(vscale);
	// Serial.println((int)vscale);
	// float vscaleChange = gamepad.mapfJoystickAxisY(-10, 10);
	// Serial.println(vscaleChange);
	// if (vscaleChange < -5) {
	// 	vscale -= 1;
	// 	tv.forceVscale(vscale);
	// }
	// if (vscaleChange > 5) {
	// 	vscale += 1;
	// 	tv.forceVscale(vscale);
	// }
	

	// Изменение состояния пушки.
	float gun_angle_speed = gamepad.mapfJoystickAxisX(-PI / 60, PI / 60);
	gun.changeAngle(gun_angle_speed);
	

	// Создание пуль и бомб в момент нажатия на кнопки геймпада.
	if (gamepad.isFireButtonPress() && fireCounter > 0) {
		fireCounter--;
		bulletList.addBullet(bulletList.newBullet(Fire, gun.getAngle(), 15));
	}
	if (gamepad.isBombButtonPress() && bombCounter > 0) {
		bombCounter--;
		bulletList.addBullet(bulletList.newBullet(Bomb, gun.getAngle(), 15));
	}

	// Цикл по всем пулям: 
	// 1) перемещение пуль, 
	// 2) удаление пуль, которые вылетили за экран.
	currentBullet = bulletList.firstBullet;
	while (currentBullet != nullptr) {
		currentBullet->radius += 3;
		Bullet *nextBullet = currentBullet->next;
		int bullet_x1 = currentBullet->radius * cos(currentBullet->angle) + tv.hres() / 2;
		int bullet_y1 = tv.vres() - currentBullet->radius * sin(currentBullet->angle);
		if (pointOffScreen(bullet_x1, bullet_y1)) bulletList.deleteBullet(currentBullet);
		currentBullet = nextBullet;
	}

	// Расчет вагонетки.
	ammuWagonX += ammuWagonSpeedX;
	if (ammuWagonX < SCREEN_WIDTH / 2 + 8 || ammuWagonX > SCREEN_WIDTH - 16) {
		ammuWagonSpeedX = -ammuWagonSpeedX;
	}
	if (ammuWagonX < SCREEN_WIDTH / 2 + 8) ammuWagonX = SCREEN_WIDTH / 2 + 8;
	if (ammuWagonX > SCREEN_WIDTH - 16) ammuWagonX = SCREEN_WIDTH - 16;
	if (ammuWagonX == SCREEN_WIDTH / 2 + 8 && ammuWagonSpeedX == -1 && (bombCounter < 30 || fireCounter < 100)) {
		bombCounter++;
		fireCounter++;
	}
}

void draw() {

	// Статусная строка.
	tv.printPGM(3, 3, PSTR("FIRE: "));
	tv.print(fireCounter);
	tv.printPGM(3, 10, PSTR("BOMB: "));
	tv.print(bombCounter);
	tv.printPGM(tv.hres() / 2, 3, PSTR("RAM: "));
	tv.print(freeMemory());

	gun.draw();
	tv.bitmap(ammuWagonX, SCREEN_HEIGHT - 9, AmmuWagonImage);
	
	// Цикл отрисовки пуль на экране.
	currentBullet = bulletList.firstBullet;
	while (currentBullet != nullptr) {
		switch (currentBullet->type) {
			case Fire: {
				int fireSize = 5;
				int bullet_x1 = currentBullet->radius * cos(currentBullet->angle) + tv.hres() / 2;
				int bullet_y1 = tv.vres() - currentBullet->radius * sin(currentBullet->angle);
				int bullet_x2 = (currentBullet->radius + fireSize) * cos(currentBullet->angle) + tv.hres() / 2;
				int bullet_y2 = tv.vres() - (currentBullet->radius + fireSize) * sin(currentBullet->angle);
				tv.drawLine(bullet_x1, bullet_y1, bullet_x2, bullet_y2, WHITE);
				break;
			}
			case Bomb: {
				int bombSize = 1;
				int bullet_x1 = (currentBullet->radius + bombSize) * cos(currentBullet->angle) + tv.hres() / 2;
				int bullet_y1 = tv.vres() - (currentBullet->radius + bombSize) * sin(currentBullet->angle);
				drawCircle(tv, bullet_x1, bullet_y1, bombSize);
				break;
			}
		}
		currentBullet = currentBullet->next;
	}

	// Земля.
	tv.drawLine(0, tv.vres() - 1, tv.hres() - 1, tv.vres() - 1, WHITE);
}