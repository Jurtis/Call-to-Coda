#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "sprite_renderer.h"
#include "game_object.h"
#include "game_map.h"

// Represents the current state of the game
enum GameState {
	GAME_ACTIVE,
	GAME_MENU,
	GAME_WIN
};



class Game
{
public:
	// Game State
	GameState		State;
	bool			Keys[1024];
	unsigned int	Width, Height;
	// Constructor Destructor
	Game(unsigned int width, unsigned int height);
	~Game();
	// Intialize Game State (loading all shaders/textures/levels)
	void Init();
	// Game Loop
	void ProcessInput(float deltaTime);
	void Update(float deltaTime);
	void Render();
	void DoCollisions();
	bool CheckCollision(GameObject& one, GameObject& two);
	void PlayerShoot();
	void PlayerShootDiagonal();
	void PlayerDodgeLeft();
	void PlayerDodgeRight();
	std::vector<GameMap> Maps;
	unsigned int Map;
	void StartMusic();
	void Start();
	void EnemyShootRight();
	void EnemyShootLeft();
};

#endif