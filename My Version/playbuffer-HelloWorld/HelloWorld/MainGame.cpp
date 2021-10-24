#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
#include "MainGame.h"
#include "GameObjects.h"
#include "Player.h"

//int DISPLAY_WIDTH = 1280;
//int DISPLAY_HEIGHT = 720;
//int DISPLAY_SCALE = 1;

GameState gState;

void LevelUpdater();
void CleanUpAll();

// The entry point for a PlayBuffer program
void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
	Play::CreateManager(gState.DISPLAY_WIDTH, gState.DISPLAY_HEIGHT, gState.DISPLAY_SCALE);
	Play::CentreAllSpriteOrigins();

	// sprites that for landing on the asteroids
	Play::SetSpriteOrigin("agent8_right_7", 60, 115);
	Play::SetSpriteOrigin("agent8_left_7", 60, 115);
	Play::SetSpriteOrigin("asteroid_2", 85, 85);
	Play::SetSpriteOrigin("agent8_fly", 70, 45);

	Play::LoadBackground("Data\\Backgrounds\\background.png");
	// just testing the player spawning
	gState.player = new Player({ 320,180 }, { 0,0 });
	gState.player->SetSpeed(5);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate(float elapsedTime)
{
	Play::DrawBackground();
	//Play::ClearDrawingBuffer( Play::cOrange );
	gState.player->Update(gState);

	//level update
	LevelUpdater();
	Meteor::UpdateAll(gState);
	Asteroid::Update(gState);
	AsteroidPieces::Update(gState);
	Gem::Update(gState);
	//level update

	// text
	Play::DrawFontText("64px", "Level = " + std::to_string(gState.level), { gState.DISPLAY_WIDTH / 10, 25 }, Play::CENTRE);
	Play::DrawFontText("64px", "Goal = " + std::to_string(gState.level), { gState.DISPLAY_WIDTH / 10, 75 }, Play::CENTRE);
	// text

	//testing
	Play::DrawSpriteRotated("asteroid_pieces_3", { gState.DISPLAY_WIDTH / 2, gState.DISPLAY_HEIGHT / 2 }, 1, 0, 1, 1.0f);
	Play::DrawSpriteRotated("asteroid_pieces_3", { gState.DISPLAY_WIDTH / 2, gState.DISPLAY_HEIGHT / 2 }, 2, 0, 1, 1.0f);
	Play::DrawSpriteRotated("asteroid_pieces_3", { gState.DISPLAY_WIDTH / 2, gState.DISPLAY_HEIGHT / 2 }, 3, 0, 1, 1.0f);
	Play::DrawFontText("64px", "+", { gState.DISPLAY_WIDTH / 2, gState.DISPLAY_HEIGHT / 2 }, Play::CENTRE);

	CleanUpAll();
	Play::PresentDrawingBuffer();
	return Play::KeyDown(VK_ESCAPE);

}

// Gets called once when the player quits the game 
int MainGameExit(void)
{
	Play::DestroyManager();
	return PLAY_OK;
}

void LevelUpdater()
{
	if (gState.goal <= 0)
	{
		gState.level += 1;
		gState.goal = Play::RandomRollRange(gState.level, gState.level * 2);
		spawnObjects(gState);
	}
}

int InGameScreen(GameState& gState, Point2f pos, Vector2f velocity)
{
	// horizontally out of the screen
	if (pos.x < 0)
		return 1;
	else if (pos.x > gState.DISPLAY_WIDTH)
		return 2;
	//vertically out of the screen
	if (pos.y < 0)
		return 3;
	else if (pos.y > gState.DISPLAY_HEIGHT)
		return 4;
	else
		return 0;
}

bool HasCollidedMeteor(Player* p, Meteor* m)
{
	if (p->GetPosition().x < m->GetPosition().x + m->GetWidth() && p->GetPosition().x + p->GetWidth() > m->GetPosition().x &&
		p->GetPosition().y < m->GetPosition().y + m->GetHight() && p->GetPosition().y + p->GetHight() > m->GetPosition().y)
		return true;
}

bool HasCollidedAsteroid(Player* p, Asteroid* a)
{
	if (p->GetPosition().x < a->GetPosition().x + a->GetWidth() && p->GetPosition().x + a->GetWidth() > a->GetPosition().x &&
		p->GetPosition().y < a->GetPosition().y + a->GetHight() && p->GetPosition().y + a->GetHight() > a->GetPosition().y)
		return true;
}

bool HasCollidedGem(Player* p, Gem* g)
{
	if (p->GetPosition().x < g->GetPosition().x + g->GetWidth() && p->GetPosition().x + g->GetWidth() > g->GetPosition().x &&
		p->GetPosition().y < g->GetPosition().y + g->GetHight() && p->GetPosition().y + g->GetHight() > g->GetPosition().y)
		return true;
}


void ResetAll()
{
	Player* p = gState.player;
	gState.level = 0;
	gState.goal = 0;
	p->SetState(0);
	p->SetPosition({ (Play::RandomRollRange(0, gState.DISPLAY_WIDTH) + 30), gState.DISPLAY_HEIGHT });
	p->SetRotation({ 0 });

	Meteor::CleanUpAll(true);
	Asteroid::CleanUpAll(true);
	AsteroidPieces::CleanUpAll(true);
	Gem::CleanUpAll(true);
}

void CleanUpAll()
{
	Meteor::CleanUpAll();
	Asteroid::CleanUpAll();
	AsteroidPieces::CleanUpAll();
	Gem::CleanUpAll();
}