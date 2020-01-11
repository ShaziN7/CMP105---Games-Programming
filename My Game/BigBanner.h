#pragma once

#include "Prop.h"


class BigBanner: public Prop
{

public:

	BigBanner();
	~BigBanner();

	void update(float dt); // Animates Big Banner


private:

	Animation flash; // The animation for Big Banner
};