#pragma once

enum BulletType {Fire, Bomb};

class Bullet {
	public:
		Bullet(BulletType type, float angle = 0, float radius = 0);
		float angle;
		float radius;
		BulletType type;
		Bullet *prev = nullptr;
		Bullet *next = nullptr;
	private:
};