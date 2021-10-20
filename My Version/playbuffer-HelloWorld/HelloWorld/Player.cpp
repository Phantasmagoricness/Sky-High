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
		double x = GetSpeed() * sin(GetRotation());
		double y = GetSpeed() * -cos(GetRotation());
		SetVelocity({ float(x), float(y) });
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
			gState.gem.push_back(g);
			gState.attachedAsteroid = NULL;
			SetState(0);
		}
		SetPosition(GetPosition() + GetVelocity());
		Play::DrawSpriteRotated("agent8_right_7", GetPosition(), 1, -GetRotation(), 1, 1.0f);
		break;
	}
	case STATE_DEAD:
	{
		double x = GetSpeed() * sin(GetRotation());
		double y = GetSpeed() * -cos(GetRotation());
		SetVelocity({ float(x), float(y) });
		if (InGameScreen(gState, GetPosition(), GetVelocity()) != 0)
			ResetAll();
		SetPosition(GetPosition() + GetVelocity());
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