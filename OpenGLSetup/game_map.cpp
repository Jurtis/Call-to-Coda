#include "game_map.h"

#include <fstream>
#include <sstream>

void GameMap::Load(const char* file, unsigned int mapWidth, unsigned int mapHeight)
{
	// clear old data
	this->Enemies.clear();
	// load from file
	unsigned int character;
	std::string line;
	std::ifstream fstream(file);
	std::vector<std::vector<unsigned int>> mapData;
	if (fstream)
	{
		while (std::getline(fstream, line)) // read each line from map file
		{
			std::istringstream sstream(line);
			std::vector<unsigned int> row;
			while (sstream >> character) // read each character seperated by spaces
				row.push_back(character);
			mapData.push_back(row);
		}
		if (mapData.size() > 0)
			this->init(mapData, mapWidth, mapHeight);
	}
}

void GameMap::Draw(SpriteRenderer& renderer)
{
	for (GameObject& enemy : this->Enemies)
		if (!enemy.Destroyed)
			enemy.Draw(renderer);
}

bool GameMap::IsCompleted()
{
	/*
	for (GameObject& enemy : this->Enemies)
		if (!enemy.HasHitbox && !enemy.Destroyed)
			return false;
	return true;
	*/
	return gameComplete;
}

void GameMap::init(std::vector<std::vector<unsigned int>> mapData, unsigned int mapWidth, unsigned int mapHeight)
{
	this->mapData = mapData;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	/*
	unsigned int height = mapData.size();
	unsigned int width = 2;					// 2 possible configurations, 1. left and right enemies, 2. center enemy
	float unitHeight = 100.0f;
	float unitWidth = 100.0f;
	for (unsigned int y = 0; y < height; y++)
	{
		if (mapData[y][0] == 1)
		{
			glm::vec2 position(0.0f, 100.0f);
			glm::vec2 size(unitWidth, unitHeight);
			GameObject enemyLeft(position, size, ResourceManager::GetTexture("enemy"), glm::vec3(1.0f, 1.0f, 1.0f));
			enemyLeft.HasHitbox = true;
			this->Enemies.push_back(enemyLeft);
			
			position = { 700.0f, 100.0f };
			GameObject enemyRight(position, size, ResourceManager::GetTexture("enemy"), glm::vec3(1.0f, 1.0f, 1.0f));
			enemyRight.HasHitbox = true;
			this->Enemies.push_back(enemyRight);
		}

		if (mapData[y][1] == 1)
		{
			glm::vec2 position(350.0f, 0.0f);
			glm::vec2 size(unitWidth, unitHeight);
			GameObject enemy(position, size, ResourceManager::GetTexture("enemy"), glm::vec3(1.0f, 1.0f, 1.0f));
			enemy.HasHitbox = true;
			this->Enemies.push_back(enemy);
		}
	}
	*/
	/*
	unsigned int height = mapData.size();
	unsigned int width = 2;					// 2 possible configurations, 1. left and right enemies, 2. center enemy
	//float unitHeight = 100.0f;
	//float unitWidth = 100.0f;
	float unitWidth = mapWidth / static_cast<float>(width), unitHeight = mapHeight / height;
	// initialize map enemies based on mapData
	for (unsigned int y = 0; y < height; y++)
	{
		for (unsigned int x = 0; x < width; x++)
		{
			// check enemy type from map data (2D map array) [NOT FUNCTIONAL YET]
			if (mapData[y][x] == 1) // solid
			{
				glm::vec2 pos(unitWidth * x, unitHeight * y);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject obj(pos, size, ResourceManager::GetTexture("enemy"), glm::vec3(1.0f, 1.0f, 1.0f));
				obj.HasHitbox = true;
				this->Enemies.push_back(obj);
			}
			
		}
	}
	*/
}

int GameMap::Update(float deltaTime)
{
	int returnValue = 0;
	unsigned int height = mapData.size();
	//unsigned int width = 4;					// 2 possible configurations, 1. left and right enemies, 2. center enemy

	elapsedTime += deltaTime;

	//if (elapsedTime >= delay && currentRow < mapData.size())
	//if (elapsedTime >= delay && currentRow < height)
	if (elapsedTime >= delay)
	{
		if (currentRow < height)
		{
			unsigned int y = currentRow;
			float unitHeight = 100.0f;
			float unitWidth = 100.0f;
			if (mapData[y][0] == 1)
			{
				glm::vec2 position(0.0f, 100.0f);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject enemyLeft(position, size, ResourceManager::GetTexture("enemy"), glm::vec3(1.0f, 1.0f, 1.0f));
				enemyLeft.HasHitbox = true;
				this->Enemies.push_back(enemyLeft);

				position = { 700.0f, 100.0f };
				GameObject enemyRight(position, size, ResourceManager::GetTexture("enemy"), glm::vec3(1.0f, 1.0f, 1.0f));
				enemyRight.HasHitbox = true;
				this->Enemies.push_back(enemyRight);

			}

			if (mapData[y][1] == 1)
			{
				glm::vec2 position(350.0f, 0.0f);
				glm::vec2 size(unitWidth, unitHeight);
				GameObject enemy(position, size, ResourceManager::GetTexture("enemy"), glm::vec3(1.0f, 1.0f, 1.0f));
				enemy.HasHitbox = true;
				this->Enemies.push_back(enemy);

			}

			if (mapData[y][2] == 1)
			{
				returnValue = 1;
			}

			if (mapData[y][3] == 1)
			{
				returnValue = 2;
			}

			elapsedTime = 0.0f;
			currentRow++;
		}
		else
		{
			gameComplete = true;
		}
	}

	return returnValue;
}