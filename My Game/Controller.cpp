#include "Controller.h"


Controller::Controller()
{
}

Controller::~Controller()
{
}


// Updates button presses using the Controller State enum
// Uses bitwise operations so that several states can happen at once
void Controller::updateState()
{
	controller = ControllerState::NONE; // Defaults the state to none

	// If button A is pressed
	if (sf::Joystick::isButtonPressed(0, 0))
	{
		controller |= ControllerState::A;
	}

	// If button B is pressed
	if (sf::Joystick::isButtonPressed(0, 1))
	{
		controller |= ControllerState::B;
	}

	// If button X is pressed
	if (sf::Joystick::isButtonPressed(0, 2))
	{
		controller |= ControllerState::X;
	}

	// If button Y is pressed
	if (sf::Joystick::isButtonPressed(0, 3))
	{
		controller |= ControllerState::Y;
	}

	// If button Back is pressed
	if (sf::Joystick::isButtonPressed(0, 6))
	{
		controller |= ControllerState::BACK;
	}

	// If button Start is pressed
	if (sf::Joystick::isButtonPressed(0, 7))
	{
		controller |= ControllerState::START;
	}

	// If button Left is pressed
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == -100)
	{
		controller |= ControllerState::LEFT;
	}

	// If button Right is pressed
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovX) == 100)
	{
		controller |= ControllerState::RIGHT;
	}

	// If button Up is pressed
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == 100)
	{
		controller |= ControllerState::UP;
	}

	// If button Down is pressed
	if (sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::PovY) == -100)
	{
		controller |= ControllerState::DOWN;
	}
}

// Returns controller state
ControllerState Controller::getControllerState()
{
	return (ControllerState) controller;
}

// Sets controller state
void Controller::setControllerState(ControllerState s)
{
	controller = s;
}