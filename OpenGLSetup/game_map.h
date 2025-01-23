#ifndef GAME_MAP_H
#define GAME_MAP_H
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

//#include "game_object.h"
#include "player_projectile.h"
#include "sprite_renderer.h"
#include "resource_manager.h"

// GameMap holds all the data for the enemies as well as
// functionality to load/render levels from files
class GameMap
{
public:
	// map state
	std::vector<GameObject> Enemies;
	// constructor
	GameMap() { }
	// loads map from file
	void Load(const char* file, unsigned int mapWidth, unsigned int mapHeight);
	// render level
	void Draw(SpriteRenderer& renderer);
	// check if the map is completed (all enemies are destroyed)
	bool IsCompleted();
	int Update(float deltaTime);
private:
	// initialize map from tile data
	void init(std::vector<std::vector<unsigned int>> mapData, unsigned int mapWidth, unsigned int mapHeight);
	unsigned int currentRow = 0; // Tracks the current row being processed
	float elapsedTime = 0.0f;    // Time accumulator
	//float delay = 5.0f;          // Delay in seconds
	//float delay = 1.41176f;		 // Delay in seconds
	//float delay = 2.0f
	float delay = 0.25f;
	std::vector<std::vector<unsigned int>> mapData;
	unsigned int mapWidth;
	unsigned int mapHeight;
	bool gameComplete = false;
};

#endif