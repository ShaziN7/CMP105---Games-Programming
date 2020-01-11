#pragma once

#include "Prop.h"


class ScrollBanner: public Prop
{

public:

	ScrollBanner();
	~ScrollBanner();

	void update(float dt); // Animates Scroll Banner


private:

	Animation scroll; // The animation for Scroll Banner
};