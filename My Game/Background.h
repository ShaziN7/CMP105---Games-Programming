#pragma once

#include "Framework/GameObject.h"

class Background: public GameObject
{

public:

	Background();
	~Background();

	void update(float dt);
};