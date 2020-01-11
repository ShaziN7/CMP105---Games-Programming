#pragma once

#include "Prop.h"


class SushiBanner: public Prop
{

public:

	SushiBanner();
	~SushiBanner();

	void update(float dt); // Animates Sushi Banner


private:

	Animation flash; // The animation for Sushi Banner
};