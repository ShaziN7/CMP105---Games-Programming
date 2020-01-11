#pragma once

#include "Prop.h"


class SideBanner : public Prop
{

public:

	SideBanner();
	~SideBanner();

	void update(float dt); // Animates Side Banner


private:

	Animation flash; // The animation for Side Banner
};