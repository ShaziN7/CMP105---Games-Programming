#pragma once

// Player states based on what player is doing
enum class PlayerState {IDLE = 1, RUNNING, CROUCHING, CLIMBING, SHOOTING, JUMPING, DODGING, RUNSHOOTING, HURT, FALLING};

// Which direction player is moving
enum class PlayerDirection {LEFT, RIGHT};

// What type of collider for collision responses
enum class ColliderType {NONE, BULLET, ENEMY, PLATFORM, LADDER, COIN};

// Which side is colliding
enum class CollisionSide {NONE, TOP, BOTTOM, LEFT, RIGHT};

// Controller buttons numbered for bitwise operations so multiple can be active at once
enum ControllerState {NONE = 0, A = 1, B = 2, X = 4, Y = 8, UP = 16, DOWN = 32, LEFT = 64, RIGHT = 128, START = 256, BACK = 512};

// Game difficulties
enum class GameDifficulty {HARD, MEDIUM, EASY};