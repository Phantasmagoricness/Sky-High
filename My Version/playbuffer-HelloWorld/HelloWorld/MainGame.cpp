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

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( gState.DISPLAY_WIDTH, gState.DISPLAY_HEIGHT, gState.DISPLAY_SCALE );
	Play::CentreAllSpriteOrigins();
	Play::LoadBackground("Data\\Backgrounds\\background.png");
	// just testing the player spawning
	Player* p = new Player({ 320,180 }, { 0,0 });
	p->SetSpeed(3);
	gState.player.push_back(p);
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::DrawBackground();
	//Play::ClearDrawingBuffer( Play::cOrange );
	Player::Update(gState);

	//level update
	LevelUpdater();
	Meteor::Update(gState);
	Asteroid::Update(gState);
	//level update

	// text
	Play::DrawFontText("64px", "Level = " + std::to_string(gState.level), { gState.DISPLAY_WIDTH / 10, 25 }, Play::CENTRE);
	Play::DrawFontText("64px", "Goal = " + std::to_string(gState.level), { gState.DISPLAY_WIDTH / 10, 75 }, Play::CENTRE);
	// text
	Play::PresentDrawingBuffer();
	return Play::KeyDown( VK_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
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