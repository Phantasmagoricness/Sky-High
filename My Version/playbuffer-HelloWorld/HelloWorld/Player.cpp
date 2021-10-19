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
	for (Player* p : gState.player)
	{
		switch (Player::PlayerState())
		{
		case STATE_FLYING:
		{
			if (Play::KeyDown(VK_LEFT))
			{
				p->SetRotation(p->GetRotation() - p->GetRotationSpeed());
			}
			if (Play::KeyDown(VK_RIGHT))
			{
				p->SetRotation(p->GetRotation() + p->GetRotationSpeed());
			}
			double x = p->GetSpeed() * sin(p->GetRotation());
			double y = p->GetSpeed() * -cos(p->GetRotation());
			p->SetVelocity({ float(x), float(y) });
			break;
		}
		case STATE_ATTACHED:
		{
			break;
		}
		case STATE_DEAD:
		{
			double x = p->GetSpeed() * sin(p->GetRotation());
			double y = p->GetSpeed() * -cos(p->GetRotation());
			p->SetVelocity({ float(x), float(y) });
			break;
		}
		break;
		}

		p->SetPosition(p->GetPosition() + p->GetVelocity());

		if (InGameScreen(gState, p->GetPosition(), p->GetVelocity()) != 0)
		{
			if (InGameScreen(gState, p->GetPosition(), p->GetVelocity()) == 1)
				p->SetPosition({ p->GetPosition().x + gState.DISPLAY_WIDTH, p->GetPosition().y });
			if (InGameScreen(gState, p->GetPosition(), p->GetVelocity()) == 2)
				p->SetPosition({ p->GetPosition().x - gState.DISPLAY_WIDTH, p->GetPosition().y });
			if (InGameScreen(gState, p->GetPosition(), p->GetVelocity()) == 3)
				p->SetPosition({ p->GetPosition().x, p->GetPosition().y + gState.DISPLAY_HEIGHT });
			if (InGameScreen(gState, p->GetPosition(), p->GetVelocity()) == 4)
				p->SetPosition({ p->GetPosition().x, p->GetPosition().y - gState.DISPLAY_HEIGHT });
		}

		Play::DrawSpriteRotated("agent8_fly", p->GetPosition(), 1, p->GetRotation(), 1, 1.0f);
	}
}