#pragma once
#include "Play.h"

class Player : public GameObjects
{
public:
	Player(Point2f position, Vector2f velocity);
	enum PlayerState
	{
		STATE_FLYING = 0,
		STATE_ATTACHED,
		STATE_DEAD,
	};
	void Update(GameState& gState);
	void SetState(int playerState)
	{
		if (playerState == STATE_ATTACHED)
			playerState = STATE_ATTACHED;
		m_playerState = PlayerState(playerState);
	}
	PlayerState GetState()
	{
		return m_playerState;
	}
	void SetRotationSpeed(float rotaionSpeed)
	{
		m_rotationSpeed = rotaionSpeed;
	}
	float GetRotationSpeed()
	{
		return m_rotationSpeed;
	}
private:
	PlayerState m_playerState{ STATE_FLYING };
	float m_rotationSpeed{ 0.02f };
};

