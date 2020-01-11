#pragma once

#include "Framework/Animation.h"
#include "Framework/GameObject.h"

class Prop: public GameObject
{

public:

	Prop();
	~Prop();

	void setBuilding(int b); // Sets which building the prop is on

protected:

	int building; // Which building the prop is on
};