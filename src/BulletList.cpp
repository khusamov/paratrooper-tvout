#include "BulletList.h"

BulletList::BulletList() {}

Bullet *BulletList::newBullet(BulletType type, float angle, float radius) {
	return new Bullet(type, angle, radius);
}

Bullet *BulletList::addBullet(Bullet *newBullet) {
	if (this->firstBullet == nullptr) {
		this->firstBullet = newBullet;
		this->lastBullet = newBullet;
	} else {
		newBullet->prev = this->lastBullet;
		this->lastBullet->next = newBullet;
		this->lastBullet = newBullet;
	}
	return newBullet;
}

void BulletList::deleteBullet(Bullet *bullet) {
	if (this->firstBullet == this->lastBullet) {
		delete this->firstBullet;
		this->firstBullet = nullptr;
		this->lastBullet = nullptr;
	} else {
		if (bullet == this->firstBullet) {
			this->firstBullet = bullet->next;
		} else {
			bullet->prev->next = bullet->next;
		}
		delete bullet;
	}
}