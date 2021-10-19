#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MainGame.h"
#include "GameObjects.h"
#include "Player.h"

//int InGameScreen(GameState& gState, Point2f pos, Vector2f velocity)
//{
//	 horizontally out of the screen
//	if (pos.x < 0)
//		return 1;
//	else if (pos.x > gState.DISPLAY_WIDTH)
//		return 2;
//	vertically out of the screen
//	if (pos.y < 0)
//		return 3;
//	else if (pos.y > gState.DISPLAY_HEIGHT)
//		return 4;
//	else
//		return 0;
//}

void Meteor::Update(GameState& gState)
{
	for (Meteor* m : gState.meteor)
	{
		m->SetPosition(m->GetPosition() + m->GetVelocity());

		if (InGameScreen(gState, m->GetPosition(), m->GetVelocity()) != 0)
		{
			if (InGameScreen(gState, m->GetPosition(), m->GetVelocity()) == 1)
				m->SetPosition({ m->GetPosition().x + gState.DISPLAY_WIDTH, m->GetPosition().y });
			if (InGameScreen(gState, m->GetPosition(), m->GetVelocity()) == 2)
				m->SetPosition({ m->GetPosition().x - gState.DISPLAY_WIDTH, m->GetPosition().y });
			if (InGameScreen(gState, m->GetPosition(), m->GetVelocity()) == 3)
				m->SetPosition({ m->GetPosition().x, m->GetPosition().y + gState.DISPLAY_HEIGHT });
			if (InGameScreen(gState, m->GetPosition(), m->GetVelocity()) == 4)
				m->SetPosition({ m->GetPosition().x, m->GetPosition().y - gState.DISPLAY_HEIGHT });
		}

		if (HasCollidedMeteor(gState.player, m) == true)
		{
			gState.player->SetState({ 2 });
		}
		Play::DrawSpriteRotated("meteor_2", m->GetPosition(), 1, m->GetRotation(), 1, 1.0f);
	}
}

void Asteroid::Update(GameState& gState)
{
	for (Asteroid* a : gState.asteroid)
	{
		a->SetPosition(a->GetPosition() + a->GetVelocity());

		if (InGameScreen(gState, a->GetPosition(), a->GetVelocity()) != 0)
		{
			if (InGameScreen(gState, a->GetPosition(), a->GetVelocity()) == 1)
				a->SetPosition({ a->GetPosition().x + gState.DISPLAY_WIDTH, a->GetPosition().y });
			if (InGameScreen(gState, a->GetPosition(), a->GetVelocity()) == 2)
				a->SetPosition({ a->GetPosition().x - gState.DISPLAY_WIDTH, a->GetPosition().y });
			if (InGameScreen(gState, a->GetPosition(), a->GetVelocity()) == 3)
				a->SetPosition({ a->GetPosition().x, a->GetPosition().y + gState.DISPLAY_HEIGHT });
			if (InGameScreen(gState, a->GetPosition(), a->GetVelocity()) == 4)
				a->SetPosition({ a->GetPosition().x, a->GetPosition().y - gState.DISPLAY_HEIGHT });
		}

		if (HasCollidedAsteroid(gState.player, a) == true)
		{
			gState.attachedAsteroid = a;
			gState.player->SetRotationSpeed(0.04f);
		}
		Play::DrawSpriteRotated("asteroid_2", a->GetPosition(), 1, a->GetRotation(), 1, 1.0f);
	}
}

// spawning objects

void spawnObjects(GameState& gState)
{
	for (int i = 0; i < gState.numberOfAsteroids * gState.level; i++)
	{
		if (Play::RandomRollRange(1, 2) == 1)
		{
			Asteroid* a = new Asteroid({ Play::RandomRollRange(0, gState.DISPLAY_WIDTH), 0 }, { Play::RandomRollRange(0,360) });
			double x = a->GetSpeed() * sin(a->GetRotation());
			double y = a->GetSpeed() * -cos(a->GetRotation());
			a->SetVelocity({ float(x), float(y) });
			gState.asteroid.push_back(a);
		}
		else if (Play::RandomRollRange(1, 2) == 2)
		{
			Asteroid* a = new Asteroid({ 0, Play::RandomRollRange(0, gState.DISPLAY_HEIGHT) }, { Play::RandomRollRange(0,360) });
			double x = a->GetSpeed() * sin(a->GetRotation());
			double y = a->GetSpeed() * -cos(a->GetRotation());
			a->SetVelocity({ float(x), float(y) });
			gState.asteroid.push_back(a);
		}
	}

	for (int b = 0; b < gState.numberOfMeteors * gState.level; b++)
	{
		if (Play::RandomRollRange(1, 2) == 1)
		{
			Meteor* m = new Meteor({ 0, Play::RandomRollRange(0, gState.DISPLAY_HEIGHT) }, { Play::RandomRollRange(0,360) });
			double x = m->GetSpeed() * sin(m->GetRotation());
			double y = m->GetSpeed() * -cos(m->GetRotation());
			m->SetVelocity({ float(x), float(y) });
			gState.meteor.push_back(m);
		}
		else if (Play::RandomRollRange(0, 2) == 2)
		{
			Meteor* m = new Meteor({ Play::RandomRollRange(0, gState.DISPLAY_WIDTH), 0 }, { Play::RandomRollRange(0,360) });
			double x = m->GetSpeed() * sin(m->GetRotation());
			double y = m->GetSpeed() * -cos(m->GetRotation());
			m->SetVelocity({ float(x), float(y) });
			gState.meteor.push_back(m);
		}
	}
}