#pragma once

#include "Prop.h"


class CokeBanner: public Prop
{

public:

	CokeBanner();
	~CokeBanner();

	void update(float dt); // Animates Coke Banner


private:

	Animation flash; // The animation for Coke Banner
};