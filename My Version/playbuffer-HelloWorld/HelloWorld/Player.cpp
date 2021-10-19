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
	case 0: // state flying
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
		break;
	}
	case 1: // state attached
	{
		break;
	}
	case 2: // state dead
	{
		SetSpeed(5);
		double x = GetSpeed() * sin(GetRotation());
		double y = GetSpeed() * -cos(GetRotation());
		SetVelocity({ float(x), float(y) });
		if (InGameScreen(gState, GetPosition(), GetVelocity()) != 0)
			ResetAll();
		Play::DrawSpriteRotated("agent8_dead_2", GetPosition(), 1, GetRotation(), 1, 1.0f);
		break;
	}
	break;
	}

	SetPosition(GetPosition() + GetVelocity());

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
		Play::DrawSpriteRotated("agent8_fly", GetPosition(), 1, GetRotation(), 1, 1.0f);
	}


}