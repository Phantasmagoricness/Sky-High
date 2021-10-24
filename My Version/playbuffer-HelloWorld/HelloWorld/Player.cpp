#include"Play.h"
#include "MainGame.h"
#include "GameObjects.h"
#include "Player.h"

Player::Player(Point2f pos, Vector2f velocity)
{
	m_pos = pos;
	m_velocity = velocity;
}

void Player::Update(GameState& gState)
{
	switch (m_playerState)
	{
	case STATE_FLYING:
	{
		if (Play::KeyDown(VK_LEFT))
		{
			SetRotation(GetRotation() - GetRotationSpeed());
		}
		if (Play::KeyDown(VK_RIGHT))
		{
			SetRotation(GetRotation() + GetRotationSpeed());
		}
		SetVelocity();
		SetPosition(GetPosition() + GetVelocity());
		Play::DrawSpriteRotated("agent8_fly", GetPosition(), 1, GetRotation(), 1, 1.0f);
		break;
	}
	case STATE_ATTACHED:
	{
		// follow the asteroid through gState.attachedAsteroid->blablabla
		SetPosition(gState.attachedAsteroid->GetPosition());
		SetPosition(gState.attachedAsteroid->GetPosition() + gState.attachedAsteroid->GetVelocity());
		if (Play::KeyDown(VK_LEFT))
		{
			SetRotation(GetRotation() - GetRotationSpeed());
		}
		if (Play::KeyDown(VK_RIGHT))
		{
			SetRotation(GetRotation() + GetRotationSpeed());
		}
		if (Play::KeyDown(VK_SPACE))
		{
			Gem* g = new Gem(gState.attachedAsteroid->GetPosition());
			AsteroidPieces* up = new AsteroidPieces(gState.attachedAsteroid->GetPosition(), 0, 0);
			up->SetVelocity();
			AsteroidPieces* dLeft = new AsteroidPieces(gState.attachedAsteroid->GetPosition(), 2, 2);
			dLeft->SetVelocity();
			AsteroidPieces* dRight = new AsteroidPieces(gState.attachedAsteroid->GetPosition(), -1, 1);
			dRight->SetVelocity();
			gState.attachedAsteroid->SetDelete(true);
			gState.attachedAsteroid = NULL;
			SetState(0);
			SetState(STATE_FLYING);
		}
		SetPosition(GetPosition() + GetVelocity());
		Play::DrawSpriteRotated("agent8_right_7", GetPosition(), 1, -GetRotation(), 1, 1.0f);
		break;
	}
	case STATE_DEAD:
	{
		SetVelocity();
		if (InGameScreen(gState, GetPosition(), GetVelocity()) != 0)
			ResetAll();
		SetPosition(GetPosition() + GetVelocity());
		gState.attachedAsteroid = NULL;
		Play::DrawSpriteRotated("agent8_dead_2", GetPosition(), 1, GetRotation(), 1, 1.0f);
		break;
	}
	break;
	}
	if (m_playerState != STATE_DEAD)
	{
		if (InGameScreen(gState, GetPosition(), GetVelocity()) != 0)
		{
			if (InGameScreen(gState, GetPosition(), GetVelocity()) == 1)
				SetPosition({ GetPosition().x + gState.DISPLAY_WIDTH, GetPosition().y });
			if (InGameScreen(gState, GetPosition(), GetVelocity()) == 2)
				SetPosition({ GetPosition().x - gState.DISPLAY_WIDTH, GetPosition().y });
			if (InGameScreen(gState, GetPosition(), GetVelocity()) == 3)
				SetPosition({ GetPosition().x, GetPosition().y + gState.DISPLAY_HEIGHT });
			if (InGameScreen(gState, GetPosition(), GetVelocity()) == 4)
				SetPosition({ GetPosition().x, GetPosition().y - gState.DISPLAY_HEIGHT });
		}
	}


}