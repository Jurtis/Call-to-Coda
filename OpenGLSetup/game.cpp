#include "game.h"
#include "resource_manager.h"
#include "player.h"
#include "text_renderer.h"
#include "player_projectile.h"
#include "player.h"
#include "fmod.hpp"


#include <iostream>

SpriteRenderer* Renderer;

SpriteRenderer* AnimatedRenderer;

TextRenderer* Text;

const glm::vec2 PLAYER_SIZE(100.0f, 100.0f);

const glm::vec2 CENTERER_SIZE(1.1f, 1.1f);

const glm::vec2 ENEMY_SIZE(100.0f, 100.0f);

const glm::vec2 PROJECTILE_SIZE(50.0f, 50.0f);

const glm::vec2 WIDE_PROJECTILE_SIZE(238.636363636f, 75.0f);

const glm::vec2 EXPLOSION_SIZE(100.0f);

//const glm::vec2 WIDE_PROJECTILE_SIZE(159.09090909f, 50.0f);

//const glm::vec2 PROJECTILE_SIZE(20.0f, 20.0f);

//const float PLAYER_VELOCITY(500.0f);

//const float ENEMY_VELOCITY(500.0f);

//const glm::vec2 PROJECTILE_VELOCITY(0.0f, -5000.0f);

//const glm::vec2 LEFT_PROJECTILE_VELOCITY(-2867.31321f, -4096.15856f);

//const glm::vec2 RIGHT_PROJECTILE_VELOCITY(2867.31321f, -4096.15856f);

const glm::vec2 PROJECTILE_VELOCITY(0.0f, -10000.0f);

const glm::vec2 LEFT_PROJECTILE_VELOCITY(-5734.6565f, -8192.31713f);

const glm::vec2 RIGHT_PROJECTILE_VELOCITY(5734.6565f, -8192.31713f);

const glm::vec2 ENEMY_PROJECTILE_VELOCITY(0.0f, 10000.0f);

//const glm::vec2 ENEMY_PROJECTILE_VELOCITY(0.0f, 5000.0f);



const unsigned int ENTITY_INDEX_PLAYER_PROJECTILE_LIMIT = 5;
const unsigned int ENTITY_INDEX_ENEMY_PROJECTILE_LIMIT = 2;
//const glm::vec2 PROJECTILE_VELOCITY(0.0f, -2500.0f);
//const glm::vec2 PROJECTILE_VELOCITY(0.0f, -500.0f);

//bool keyStates[GLFW_KEY_LAST] = { false };

FMOD::System* pSystem;

FMOD::Sound* dodgeSound;

PlayerObject* Player;
GameObject* Enemy;
GameObject* Explosion;

GameObject* CentererObject;
GameObject* EnemyProjectile;

std::vector<PlayerProjectileObject> PlayerProjectileEntities;
std::vector<PlayerProjectileObject> LeftDiagonalPlayerProjectileEntities;
std::vector<PlayerProjectileObject> RightDiagonalPlayerProjectileEntities;
//std::vector<PlayerProjectileObject> LeftEnemyProjectileEntities;					
//std::vector<PlayerProjectileObject> RightEnemyProjectileEntities;			
std::vector<GameObject> LeftEnemyProjectileEntities;
std::vector<GameObject> RightEnemyProjectileEntities;
std::vector<GameObject*> OnScreenEnemyProjectileEntities;
std::vector<PlayerProjectileObject*> OnScreenPlayerProjectileEntities;
//std::vector<PlayerProjectileObject*> OnScreenEnemyProjectileEntities;
unsigned int EntityIndexPlayerProjectile = 0;
unsigned int EntityIndexDiagonalPlayerProjectile = 0;
unsigned int EntityIndexLeftEnemyProjectile = 0;
unsigned int EntityIndexRightEnemyProjectile = 0;


glm::vec2 PlayerProjectileResetPosition = glm::vec2(0.0f);
//glm::vec2 LeftEnemyProjectileResetPosition = glm::vec2(0.0f);
//glm::vec2 RightEnemyProjectileResetPosition = glm::vec2(0.0f);

int mapState = 0;

FMOD::Channel* pChannel = nullptr;

float ExplosionAnimationTime = 1.0f;
int ExplosionFrameAmount = 10;

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height)
{

}

Game::~Game()
{
	delete Renderer;
	delete AnimatedRenderer;
}

void Game::Init()
{
	this->Start();
}


void Game::Start()
{
	// load shaders
	ResourceManager::LoadShader("Shader Files/vertex.sprite.texture.shader.glsl", "Shader Files/fragment.sprite.texture.shader.glsl", "sprite");
	ResourceManager::LoadShader("Shader Files/vertex.animated.sprite.texture.shader.glsl", "Shader Files/fragment.animated.sprite.texture.shader.glsl", "animatedSprite");
	// configure shaders
	glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width), static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
	ResourceManager::GetShader("sprite").Use().setInt("image", 0);
	ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

	ResourceManager::GetShader("animatedSprite").Use().setInt("image", 0);
	ResourceManager::GetShader("animatedSprite").SetMatrix4("projection", projection);

	// set render-specific controls
	//Shader myShader = ResourceManager::GetShader("sprite");
	//Renderer = new SpriteRenderer(myShader);
	Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

	AnimatedRenderer = new SpriteRenderer(ResourceManager::GetShader("animatedSprite"));
	// load textures
	ResourceManager::LoadTexture("Textures/PlayerShip2.png", true, "player");
	//ResourceManager::LoadTexture("Te+xtures/PlayerShipAnimationTest.png", true, "player");
	ResourceManager::LoadTexture("Textures/EnemyShip1.png", true, "enemy");
	ResourceManager::LoadTexture("Textures/Projectile.png", true, "projectile");
	//ResourceManager::LoadTexture("Textures/AlternateProjectile3.png", true, "EnemyProjectile");
	ResourceManager::LoadTexture("Textures/Explosion.png", true, "Explosion");
	glm::vec2 playerPositon = glm::vec2(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
	std::cout << playerPositon.x;
	glm::vec2 centererPosition = glm::vec2(this->Width / 2.0f - CENTERER_SIZE.x / 2.0f, this->Height - CENTERER_SIZE.y);
	glm::vec2 enemyPosition = glm::vec2(this->Width / 2.0f - ENEMY_SIZE.x / 2.0f, 0.0f);
	glm::vec2 explosionPosition = glm::vec2(playerPositon.x - 100.0f, playerPositon.y);
	glm::vec2 leftExplosionPosition = glm::vec2(playerPositon.x - 100.0f, playerPositon.y);
	glm::vec2 rightExplosionPosition = glm::vec2(playerPositon.x + 100.0f, playerPositon.y);

	//glm::vec2 enemyProjectilePosition = glm::vec2(411.363636363f, 100.0f);

	glm::vec2 playerProjectilePosition = glm::vec2(1000.0f);

	Player = new PlayerObject(playerPositon, PLAYER_SIZE, ResourceManager::GetTexture("player"));
	CentererObject = new GameObject(centererPosition, CENTERER_SIZE, ResourceManager::GetTexture("enemy"));
	//EnemyProjectile = new GameObject(enemyProjectilePosition, WIDE_PROJECTILE_SIZE, ResourceManager::GetTexture("EnemyProjectile"));
	Explosion = new GameObject(explosionPosition, EXPLOSION_SIZE, ResourceManager::GetTexture("Explosion"), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f), 0, ExplosionFrameAmount);
	Text = new TextRenderer(this->Width, this->Height);
	Text->Load("Fonts/arial.ttf", 24);

	GameMap one; one.Load("Maps/four.map", this->Width, this->Height / 2);

	this->Maps.push_back(one);
	this->Map = 0;


	for (int i = 0; i <= ENTITY_INDEX_PLAYER_PROJECTILE_LIMIT; i++)
	{
		PlayerProjectileEntities.push_back(PlayerProjectileObject(playerProjectilePosition, PROJECTILE_SIZE, PROJECTILE_VELOCITY, ResourceManager::GetTexture("projectile")));
		LeftDiagonalPlayerProjectileEntities.push_back(PlayerProjectileObject(playerProjectilePosition, PROJECTILE_SIZE, LEFT_PROJECTILE_VELOCITY, ResourceManager::GetTexture("projectile")));
		RightDiagonalPlayerProjectileEntities.push_back(PlayerProjectileObject(playerProjectilePosition, PROJECTILE_SIZE, RIGHT_PROJECTILE_VELOCITY, ResourceManager::GetTexture("projectile")));
	};

	
	for (int i = 0; i <= ENTITY_INDEX_ENEMY_PROJECTILE_LIMIT; i++)
	{
		LeftEnemyProjectileEntities.push_back(GameObject(leftExplosionPosition, EXPLOSION_SIZE, ResourceManager::GetTexture("Explosion"), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f), 0, ExplosionFrameAmount));
		RightEnemyProjectileEntities.push_back(GameObject(rightExplosionPosition, EXPLOSION_SIZE, ResourceManager::GetTexture("Explosion"), glm::vec3(1.0f), glm::vec2(0.0f, 0.0f), 0, ExplosionFrameAmount));
	};
	

	PlayerProjectileResetPosition = Player->Position + glm::vec2(PLAYER_SIZE.x / 2.0f - PROJECTILE_SIZE.x / 2.0f, -PROJECTILE_SIZE.y * 2.0f);

}


void Game::PlayerShoot()
{
	if (this->State == GAME_ACTIVE)
	{ 
		if (EntityIndexPlayerProjectile >= ENTITY_INDEX_PLAYER_PROJECTILE_LIMIT)
			EntityIndexPlayerProjectile = 0;
		PlayerProjectileEntities[EntityIndexPlayerProjectile].Reset(PlayerProjectileResetPosition);
		OnScreenPlayerProjectileEntities.push_back(&PlayerProjectileEntities[EntityIndexPlayerProjectile]);
		EntityIndexPlayerProjectile++;
	}
}

void Game::PlayerShootDiagonal()
{
	if (this->State == GAME_ACTIVE)
	{
		if (EntityIndexDiagonalPlayerProjectile >= ENTITY_INDEX_PLAYER_PROJECTILE_LIMIT)
			EntityIndexDiagonalPlayerProjectile = 0;
		LeftDiagonalPlayerProjectileEntities[EntityIndexDiagonalPlayerProjectile].Reset(PlayerProjectileResetPosition);
		RightDiagonalPlayerProjectileEntities[EntityIndexDiagonalPlayerProjectile].Reset(PlayerProjectileResetPosition);
		OnScreenPlayerProjectileEntities.push_back(&LeftDiagonalPlayerProjectileEntities[EntityIndexDiagonalPlayerProjectile]);
		OnScreenPlayerProjectileEntities.push_back(&RightDiagonalPlayerProjectileEntities[EntityIndexDiagonalPlayerProjectile]);
		EntityIndexDiagonalPlayerProjectile++;
	}
}

void Game::EnemyShootLeft()
{
	if (this->State == GAME_ACTIVE)
	{
		if (EntityIndexLeftEnemyProjectile >= ENTITY_INDEX_ENEMY_PROJECTILE_LIMIT)
			EntityIndexLeftEnemyProjectile = 0;
		OnScreenEnemyProjectileEntities.push_back(&LeftEnemyProjectileEntities[EntityIndexLeftEnemyProjectile]);
		EntityIndexLeftEnemyProjectile++;
	}
}

void Game::EnemyShootRight()
{
	if (this->State == GAME_ACTIVE)
	{
		if (EntityIndexRightEnemyProjectile >= ENTITY_INDEX_ENEMY_PROJECTILE_LIMIT)
			EntityIndexRightEnemyProjectile = 0;
		OnScreenEnemyProjectileEntities.push_back(&RightEnemyProjectileEntities[EntityIndexRightEnemyProjectile]);
		EntityIndexRightEnemyProjectile++;
	}
}


void Game::PlayerDodgeLeft()
{
	if (this->State == GAME_ACTIVE)
	{
		if (CheckCollision(*Player, *CentererObject))
		{
			Player->Position.x = this->Width / 2.0f - PLAYER_SIZE.x / 2.0f - 200.0f;
			Player->SetLeftDodgeVars();
			pSystem->playSound(dodgeSound, nullptr, false, nullptr);
		}
	}
}

void Game::PlayerDodgeRight()
{
	if (this->State == GAME_ACTIVE)
	{
		if (CheckCollision(*Player, *CentererObject))
		{
			Player->Position.x = this->Width / 2.0f - PLAYER_SIZE.x / 2.0f + 200.0f;
			Player->SetRightDodgeVars();
			pSystem->playSound(dodgeSound, nullptr, false, nullptr);
		}
	}
}

void Game::Update(float deltaTime)
{
	if (this->State == GAME_ACTIVE)
	{	
		Player->Move(deltaTime, this->Width);

		//ExplosionAnimationTime += deltaTime;

		//Explosion->AddTime(deltaTime);

		// Remove projectiles only after they are completely off-screen
		OnScreenPlayerProjectileEntities.erase(
			std::remove_if(OnScreenPlayerProjectileEntities.begin(), OnScreenPlayerProjectileEntities.end(),
				[this, deltaTime](PlayerProjectileObject* projectile) {
					// Check if the projectile is beyond the screen limits
					if (projectile->Position.x + PROJECTILE_SIZE.x < 0.0f || projectile->Position.x > this->Width ||
					projectile->Position.y + PROJECTILE_SIZE.y < 0.0f || projectile->Position.y > this->Height)
					{
						return true; // Mark for removal if entirely off-screen
					}
		// Move the projectile if it is within bounds
		projectile->Move(deltaTime, this->Width);
		return false; // Keep in the vector
				}),
			OnScreenPlayerProjectileEntities.end()
					);


		// Remove projectiles only after they are done with animation
		OnScreenEnemyProjectileEntities.erase(
			std::remove_if(OnScreenEnemyProjectileEntities.begin(), OnScreenEnemyProjectileEntities.end(),
				[this, deltaTime](GameObject* enemyProjectile) {
					// Check if the projectile is on its final frame of animation
					if (enemyProjectile->AnimationIndex >= (ExplosionFrameAmount - 1))
					{
						enemyProjectile->SetTime(0.0f);
						return true; // Mark for removal
					}
		enemyProjectile->AddTime(deltaTime);
		return false; // Keep in the vector
				}),
			OnScreenEnemyProjectileEntities.end()
					);

		mapState = this->Maps[this->Map].Update(deltaTime);
		
		switch (mapState) {
		case 1:
			EnemyShootLeft();
			break;
		case 2:
			EnemyShootRight();
			break;
		}

		this->DoCollisions();
	}
}

void Game::Render()
{
	if (this->State == GAME_ACTIVE)
	{ 
		Player->Draw(*Renderer);
		
		for (PlayerProjectileObject* projectile : OnScreenPlayerProjectileEntities)
		{
			projectile->Draw(*Renderer);
		}

		/*
		for (PlayerProjectileObject* projectile : OnScreenEnemyProjectileEntities)
		{
			projectile->Draw(*Renderer);
		}
		*/

		for (GameObject* projectile : OnScreenEnemyProjectileEntities)
		{
			projectile->Animate(ExplosionAnimationTime, ExplosionFrameAmount, 0.25f);
			//projectile->Animate(ExplosionAnimationTime, ExplosionFrameAmount, 0.1);
			projectile->DrawAnimated(*AnimatedRenderer, 1, ExplosionFrameAmount);
		}

		this->Maps[this->Map].Draw(*Renderer);

		//Explosion->Draw(*Renderer);

		//int animationIndex = Explosion->Animate(&ExplosionAnimationTime, 10, 0.6f);
		//int animationIndex = Explosion->Animate(ExplosionAnimationTime, ExplosionFrameAmount, 0.25f);
		//std::cout << animationIndex << std::endl;
		// 
		//Explosion->Animate(ExplosionAnimationTime, ExplosionFrameAmount, 0.25f);
		//Explosion->DrawAnimated(*AnimatedRenderer, 1, ExplosionFrameAmount);
	}
	else
	{
		Text->DrawText("Press Enter to Play", 250.0f, Height / 2, 1.0f);
	}
}

void Game::DoCollisions()
{
	for (GameObject& enemy : this->Maps[this->Map].Enemies)
	{
		if (!enemy.Destroyed)
		{
			for (PlayerProjectileObject* projectile : OnScreenPlayerProjectileEntities)
			{
				if (CheckCollision(*projectile, enemy) == true)
				{
					if (enemy.HasHitbox)
					{
						//std::cout << "enemy destoryed" << std::endl;
						enemy.Destroyed = true;
					}
				}
			}
		}
	}

	for (GameObject* enemyProjectile : OnScreenEnemyProjectileEntities)
	{
		if (enemyProjectile->AnimationIndex < 1 && (CheckCollision(*enemyProjectile, *Player) == true))
		{
			std::cout << "You've been hit!" << std::endl;
		}
	}
	/*
	for (PlayerProjectileObject* enemyProjectile : OnScreenEnemyProjectileEntities)
	{
		if (CheckCollision(*enemyProjectile, *Player) == true)
		{
			std::cout << "bruh" << std::endl;
		}
	}
	*/
}

bool Game::CheckCollision(GameObject& one, GameObject& two) // AABB - AABB collision
{
	// collision x-axis
	bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
		two.Position.x + two.Size.x >= one.Position.x;
	// collision y-axis
	bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
		two.Position.y + two.Size.y >= one.Position.y;
	// collision only if on both axes
	return collisionX && collisionY;
}

void Game::StartMusic()
{
	FMOD_RESULT result;
	//FMOD::System* pSystem = nullptr;
	pSystem = nullptr;


	result = FMOD::System_Create(&pSystem);

	pSystem->init(32, FMOD_INIT_NORMAL, nullptr);

	FMOD::Sound* pSound = nullptr;

	pSystem->createSound("Sound/CallToCodaDemoSong.wav", FMOD_DEFAULT, nullptr, &pSound);

	//FMOD::Channel* pChannel = nullptr;
	

	if (result == FMOD_OK)
	{
		std::cout << "Sound is Playing" << std::endl;
	}

	pSystem->createSound("Sound/SFX/DodgeSound1.wav", FMOD_LOOP_OFF, nullptr, &dodgeSound);

	int systemSampleRate = 32;
	pSystem->getSoftwareFormat(&systemSampleRate, nullptr, nullptr);

	uint64_t dspClock = 0;

	pChannel->getDSPClock(&dspClock, nullptr);
	uint64_t delay = dspClock + (uint64_t)(0.1 * systemSampleRate);

	pChannel->setDelay(dspClock, delay, false);
	result = pSystem->playSound(pSound, nullptr, false, &pChannel);
}

