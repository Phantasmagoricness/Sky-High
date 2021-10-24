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

std::vector< Meteor* > Meteor::vMeteors;
std::vector< Asteroid* > Asteroid::vAsteroids;
std::vector< AsteroidPieces* > AsteroidPieces::vAsteroidPieces;
std::vector< Gem* > Gem::vGems;

void Meteor::UpdateAll(GameState& gState)
{
	for (Meteor* m : vMeteors)
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
			Play::PlayAudio("combust");
			gState.player->SetState({ Player::STATE_DEAD });
		}
		Play::DrawSpriteRotated("meteor_2", m->GetPosition(), 1, m->GetRotation(), 1, 1.0f);
	}
}

void Asteroid::Update(GameState& gState)
{
	for (Asteroid* a : vAsteroids)
	{
		int i = 0;
		i++;
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

		if (HasCollidedAsteroid(gState.player, a) == true && gState.attachedAsteroid == NULL && gState.player->GetState() == Player::STATE_FLYING && a->GetDelete() != true)
		{
			gState.attachedAsteroid = a;
			gState.player->SetRotationSpeed(0.04f);
			//gState.player->SetRotation(gState.player->GetRotation() * -1);
			gState.player->SetState(Player::STATE_ATTACHED);
		}

		//if (a->GetDelete() == true)
		//{
		//	gState.asteroid.erase(gState.asteroid.begin() + i);
		//}
		Play::DrawSpriteRotated("asteroid_2", a->GetPosition(), 1, a->GetRotation(), 1, 1.0f);
	}
}

void Gem::Update(GameState& gState)
{
	for (Gem* g : vGems)
	{
		if (HasCollidedGem(gState.player, g) == true && gState.player->GetState() == Player::STATE_FLYING && g->GetDelayTime() < gState.totalTime)
		{
			gState.goal -= 1;
			Play::PlayAudio("reward");
			g->SetDelete(true);
		}
		Play::DrawSpriteRotated("gem", g->GetPosition(), 1, g->GetRotation(), 1, 1.0f);
	}

}

// notes for the asteroid pieces
// the Asteroid Pieces should spawn with a different rotation to each other and use the x = sin and y = -cos but NOT the DrawSpriteRotated

void AsteroidPieces::Update(GameState& gState)
{
	for (AsteroidPieces* ap : vAsteroidPieces)
	{
		ap->SetPosition(ap->GetPosition() + ap->GetVelocity());
		Play::DrawSprite("asteroid_pieces_3", ap->GetPosition(), ap->GetFrame());
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
			a->SetVelocity();
			a->SetHight(75);
			a->SetWidth(75);
			//gState.asteroid.push_back(a);
		}
		else if (Play::RandomRollRange(1, 2) == 2)
		{
			Asteroid* a = new Asteroid({ 0, Play::RandomRollRange(0, gState.DISPLAY_HEIGHT) }, { Play::RandomRollRange(0,360) });
			a->SetVelocity();
			a->SetHight(75);
			a->SetWidth(75);
			//gState.asteroid.push_back(a);
		}
	}

	for (int b = 0; b < gState.numberOfMeteors * gState.level; b++)
	{
		if (Play::RandomRollRange(1, 2) == 1)
		{
			Meteor* m = new Meteor({ 0, Play::RandomRollRange(0, gState.DISPLAY_HEIGHT) }, { Play::RandomRollRange(0,360) });
			m->SetVelocity();
			//gState.meteor.push_back(m);
		}
			else if (Play::RandomRollRange(0, 2) == 2)
			{
				Meteor* m = new Meteor({ Play::RandomRollRange(0, gState.DISPLAY_WIDTH), 0 }, { Play::RandomRollRange(0,360) });
				m->SetVelocity();
			}
	}
}