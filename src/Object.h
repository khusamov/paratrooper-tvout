#pragma once
#include <TVout.h>

class Object {
	public:
		Object(TVout *tv);
		void update();
		void draw();
	protected:
		TVout *tv = nullptr;
};