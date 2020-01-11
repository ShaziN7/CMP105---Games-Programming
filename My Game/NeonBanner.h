#pragma once

#include "Prop.h"


class NeonBanner : public Prop
{

public:

	NeonBanner();
	~NeonBanner();

	void update(float dt); // Animates Neon Banner


private:

	Animation flash; // The animation for Neon Banner
};