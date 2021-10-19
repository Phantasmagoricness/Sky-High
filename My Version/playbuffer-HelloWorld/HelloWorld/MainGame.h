#pragma once
#include "Play.h"


class Meteor;
class Asteroid;
class Gem;
class Player;
struct GameState
{
	// display stuff
	int DISPLAY_WIDTH = 1280;
	int DISPLAY_HEIGHT = 720;
	int DISPLAY_SCALE = 1;
	// gameobject stuff
	std::vector<Meteor*>meteor;
	std::vector<Asteroid*>asteroid;
	std::vector<Gem*>gem;
	std::vector<Player*>player;
	// level stuff
	int level = 0;
	int goal = 0;
	int numberOfAsteroids = 2;
	int numberOfMeteors = 2;
};

int InGameScreen(GameState& gState, Point2f pos, Vector2f velocity);
bool HasCollidedMeteor(Player* p, Meteor* m);