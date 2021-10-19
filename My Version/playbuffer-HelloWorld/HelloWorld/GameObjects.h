#pragma once
#include "Play.h"

void spawnObjects(GameState& gState);

class GameObjects
{
public:
	Point2f GetPosition() const
	{
		return m_pos;
	}
	void SetPosition(Point2f pos)
	{
		m_pos = pos;
	}
	Vector2f GetVelocity() const
	{
		return m_velocity;
	}
	void SetVelocity(Vector2f velocity)
	{
		m_velocity = velocity;
	}
	float GetRotation()
	{
		return m_rotation;
	}
	void SetRotation(float rotation)
	{
		m_rotation = rotation;
	}
	int GetSpeed()
	{
		return m_speed;
	}
	void SetSpeed(float speed)
	{
		m_speed = speed;
	}
	int GetHight()
	{
		return m_hight;
	}
	void SetHight(int h)
	{
		m_hight = h;
	}
	int GetWidth()
	{
		return m_width;
	}
	void SetWidth(int w)
	{
		m_width = w;
	}
protected:
	Point2f m_pos{ 0,0 };
	Vector2f m_velocity{ 0,0 };
	float m_rotation{ 0 };
	int m_speed{ 8 };
	int m_hight{ 50 };
	int m_width{ 50 };
};

class Meteor : public GameObjects
{
public:
	Meteor(Point2f pos,  int rotation)
	{
		m_pos = pos;
		m_rotation = rotation;
	}
	static void Update(GameState& gState);
private:
};

class Asteroid : public GameObjects
{
public:
	Asteroid(Point2f pos, int rotation)
	{
		m_pos = pos;
		m_rotation = rotation;
	}
	static void Update(GameState& gState);
private:
};

class Gem : public GameObjects
{
public:
	Gem(Point2f pos, int speed)
	{
		m_pos = pos;
		m_speed = speed;
	}
private:
};

