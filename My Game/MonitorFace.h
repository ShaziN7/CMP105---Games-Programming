#pragma once

#include "Prop.h"

  
class MonitorFace: public Prop
{

public:

	MonitorFace();
	~MonitorFace();

	void update(float dt); // Animates Monitor Face


private:

	Animation flash; // The animation for Monitor Face
};