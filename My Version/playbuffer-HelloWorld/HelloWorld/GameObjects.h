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
	void SetVelocity()
	{
		double x = m_speed * sin(m_rotation);
		double y = m_speed * -cos(m_rotation);
		m_velocity = {float(x), float(y)};
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
	void SetDelete(bool y_n)
	{
		m_delete = y_n;
	}
	bool GetDelete()
	{
		return m_delete;
	}
protected:
	Point2f m_pos{ 0,0 };
	Vector2f m_velocity{ 0,0 };
	float m_rotation{ 0 };
	int m_speed{ 8 };
	int m_hight{ 50 };
	int m_width{ 50 };
	int m_center{ 0 };
	bool m_delete{ false };
};

class Meteor : public GameObjects
{
public:
	Meteor(Point2f pos, int rotation)
	{
		m_pos = pos;
		m_rotation = rotation;
		vMeteors.push_back(this);
	}
	~Meteor()
	{
		vMeteors.erase(std::find(vMeteors.begin(), vMeteors.end(), this));
	}
	static void UpdateAll(GameState& gState);
	static std::vector< Meteor* > vMeteors;
	static void CleanUpAll(bool reset = false)
	{
		for (int i = 0; i < vMeteors.size(); i++)
		{
			if (vMeteors[i]->GetDelete() == true || reset == true)
			{
				delete(vMeteors[i]);
				i--;
			}
		}
	}
private:
};

class Asteroid : public GameObjects
{
public:
	Asteroid(Point2f pos, int rotation)
	{
		m_pos = pos;
		m_rotation = rotation;
		vAsteroids.push_back(this);
	}
	~Asteroid()
	{
		vAsteroids.erase(std::find(vAsteroids.begin(), vAsteroids.end(), this));
	}
	static void Update(GameState& gState);
	static std::vector< Asteroid* > vAsteroids;
	static void CleanUpAll(bool reset = false)
	{
		for (int i = 0; i < vAsteroids.size(); i++)
		{
			if (vAsteroids[i]->GetDelete() == true || reset == true)
			{
				delete(vAsteroids[i]);
				i--;
			}
		}
	}
private:
};

class Gem : public GameObjects
{
public:
	Gem(Point2f pos)
	{
		m_pos = pos;
		vGems.push_back(this);
	}
	~Gem()
	{
		vGems.erase(std::find(vGems.begin(), vGems.end(), this));
	}
	static void Update(GameState& gState);
	static std::vector< Gem* > vGems;
	static void CleanUpAll(bool reset = false)
	{
		for (int i = 0; i < vGems.size(); i++)
		{
			if (vGems[i]->GetDelete() == true || reset == true)
			{
				delete(vGems[i]);
				i--;
			}
		}
	}
private:
};

class AsteroidPieces : public GameObjects
{
public:
	AsteroidPieces(Point2f pos, float rotation, int frame)
	{
		m_pos = pos;
		vAsteroidPieces.push_back(this);
		m_frame = frame;
		m_rotation = rotation;
	}
	~AsteroidPieces()
	{
		vAsteroidPieces.erase(std::find(vAsteroidPieces.begin(), vAsteroidPieces.end(), this));
	}
	static void Update(GameState& gState);
	static std::vector< AsteroidPieces* > vAsteroidPieces;
	static void CleanUpAll(bool reset = false)
	{
		for (int i = 0; i < vAsteroidPieces.size(); i++)
		{
			if (vAsteroidPieces[i]->GetDelete() == true || reset == true)
			{
				delete(vAsteroidPieces[i]);
				i--;
			}
		}
	}
	int GetFrame()
	{
		return m_frame;
	}
private:
	int m_frame = 1;
};

