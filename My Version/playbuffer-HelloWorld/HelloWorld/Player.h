#pragma once
#include "Play.h"
//class Player
//{
//public:
//	Player(Point2f position, Vector2f velocity);
//	enum PlayerState
//	{
//		STATE_FLYING = 0,
//		STATE_ATTACHED,
//		STATE_DEAD,
//	};
//	static void Update(GameState& gState);
//	Point2f GetPosition() const
//	{
//		return m_pos;
//	}
//	void SetPosition(Point2f pos)
//	{
//		m_pos = pos;
//	}
//	Vector2f GetVelocity() const
//	{
//		return m_velocity;
//	}
//	void SetVelocity(Vector2f velocity)
//	{
//		m_velocity = velocity;
//	}
//	int GetSpeed()
//	{
//		return m_speed;
//	}
//	void SetSpeed(float speed)
//	{
//		m_speed = speed;
//	}
//	float GetRotation()
//	{
//		return m_rotation;
//	}
//	void SetRotation(float rotation)
//	{
//		m_rotation = rotation;
//	}
//	float GetRotationSpeed()
//	{
//		return m_rotationSpeed;
//	}
//	void SetState(PlayerState playerState)
//	{
//		m_playerState = playerState;
//	}
//
//	/*char GetSprite()
//	{
//		return m_spriteName;
//	}*/
//private:
//	PlayerState m_playerState{ STATE_ATTACHED };
//	Point2f m_pos{ 0,0 };
//	Vector2f m_velocity{ 0,0 };
//	float m_speed{ 2 };
//	float m_rotation{0};
//	float m_rotationSpeed{0.02};
//	int m_hight{ 10 };
//	int m_width{ 10 };
//	//char m_spriteName;
//};

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
		m_playerState = PlayerState(playerState);
	}
	PlayerState GetState()
	{
		return m_playerState;
	}
	float GetRotationSpeed()
	{
		return m_rotationSpeed;
	}

	/*char GetSprite()
	{
		return m_spriteName;
	}*/
private:
	PlayerState m_playerState{ STATE_FLYING };
	float m_rotationSpeed{ 0.02f };
	//char m_spriteName;
};

