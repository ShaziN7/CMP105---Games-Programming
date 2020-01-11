#pragma once

#include <SFML/Graphics.hpp>
#include "States.h"


class Controller
{

public:

	Controller();
	~Controller();

	void updateState(); // Updates button presses using enums and bitwise operations
	ControllerState getControllerState(); // Returns what buttons are being pressed
	void setControllerState(ControllerState s); // Sets a state


private:

	int controller; // Holds the controller state
};