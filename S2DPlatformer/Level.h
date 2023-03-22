#pragma once


#include "Tile.h"
#include "Player.h"
#include "Gem.h"
#include "Enemy.h"

#include "S2D\S2D.h"

#include <vector>
#include <stdlib.h>

using namespace S2D;
using namespace std;

struct Tile;
class Gem;
class Enemy;
class Player;

class Level
{
private:
	vector<Texture2D*>* _layers; //A vector is a list of objects, in this case it contains textures
	vector<vector<Tile*>>* _tiles; //A vector of vectors

	static const int EntityLayer;
	Player* _player;

	vector<Gem*> _gems;
	vector<Enemy*> _enemies;

	Vector2 _start;
	Vector2 _exit;

	static const Vector2 InvalidPosition;
	static const int PointsPerSecond;

	int _score;
	bool _reachedExit;
	float _timeRemaining;

	SoundEffect* _exitReachedSound;

public:
	Level(int levelIndex);
	~Level(void);

	Player* GetPlayer();
	int GetScore();
	bool ReachedExit();
	float GetTimeRemaining();

	int GetWidth();
	int GetHeight();

	void LoadTiles(int levelIndex);
	Tile* LoadTile(const char tileType, int x, int y);
	Tile* LoadTile(const char* name, TileCollision collision);
	Tile* LoadVarietyTile(const char* baseName, int variationCount, TileCollision collision);
	Tile* LoadStartTile(int x, int y);
	Tile* LoadExitTile(int x, int y);
	Tile* LoadEnemyTile(int x, int y, char* spriteSet);
	Tile* LoadGemTile(int x, int y);
	TileCollision GetCollision(int x, int y);
	Rect GetBounds(int x, int y);

	void Update(int elapsedGameTime);
	void UpdateGems(int elapsedGameTime);
	void UpdateEnemies(int elapsedGameTime);
	void OnGemCollected(Gem* gem, Player* collectedBy);
	void OnPlayerKilled(Enemy* killedBy);
	void OnExitReached();
	void StartNewLife();

	void Draw(int elapsedGameTime);
	void DrawTiles();
};

