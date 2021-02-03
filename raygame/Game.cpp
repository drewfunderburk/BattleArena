#include "Game.h"
#include "raylib.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "TextBox.h"
#include <iostream>
#include <chrono>
#include "Button.h"

bool Game::m_gameOver = false;
Scene** Game::m_scenes = new Scene*;
int Game::m_sceneCount = 0;
int Game::m_currentSceneIndex = 0;

Game::Game()
{
	m_gameOver = false;
	m_scenes = new Scene*;
	m_camera = new Camera2D();
	m_currentSceneIndex = 0;
	m_sceneCount = 0;
}

Actor::~Actor()
{
	delete m_globalTransform;
	delete m_localTransform;
	delete m_rotation;
	delete m_translation;
	delete m_scale;
	delete[] m_children;
	delete m_sprite;
}

void Game::spawnEnemies()
{
	// Change m_enemySpawnDelay to increase or decrease how frequently enemies are spawned
	// Difficulty curve
	// 10log(x-4)
	if (RAYLIB_H::GetTime() > (double)m_enemySpawnDelay + (double)m_enemySpawnLast)
	{
		m_enemySpawnLast = RAYLIB_H::GetTime();
		// https://www.desmos.com/calculator/zqytdxxgmp
		// Vertical multiplier, how quickly it gets hard
		int multiplier = 5;
		// Horizontal offset, delay before it starts
		int offset = 0;
		int numSpawn = multiplier * log(RAYLIB_H::GetTime() - offset - 1);
		
		for (int i = 0; i < numSpawn; i++)
		{
			// Get a random X and Y outside of the screen bounds
			srand
			(
				std::chrono::duration_cast<std::chrono::milliseconds>
				(
					std::chrono::system_clock::now().time_since_epoch()
				).count()
			);

			float randomX, randomY;
			float random = rand() % 100 + 50;
			int toggle = rand() % 2;
			if (toggle)
				randomX = -random;
			else
				randomX = RAYLIB_H::GetScreenWidth() + random;

			random = rand() % 100 + 50;
			toggle = rand() % 2;
			if (toggle)
				randomY = -random;
			else
				randomY = RAYLIB_H::GetScreenHeight() + random;

			// Spawn enemy
			Enemy* enemy = new Enemy(randomX, randomY, 30, "Images/Enemy.png", 50, 1, 1);
			enemy->setTarget(m_player);
			getCurrentScene()->addActor(enemy);
		}
	}
}

void Game::start()
{
	// Init window
	int screenWidth = 1024;
	int screenHeight = 760;

	InitWindow(screenWidth, screenHeight, "Shield Bash");
	// Init Camera
	m_camera->offset = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->target = { (float)screenWidth / 2, (float)screenHeight / 2 };
	m_camera->zoom = 1;

	SetTargetFPS(60);

	// Init Start scene
	Scene* startScreen = new Scene();
	addScene(startScreen);

	// Set scene to start scene first
	setCurrentScene(0);

	Button* startButton = new Button("Press any key to continue...", 250, 300, 40, 1);
	startScreen->addActor(startButton);

	// Init main game scene
	Scene* scene1 = new Scene();
	addScene(scene1);

	m_player = new Player(100, 100, 0);
	scene1->addActor(m_player);

	// Init End scene
	Scene* endScreen = new Scene();
	addScene(endScreen);

	Button* endButton = new Button("Press any key to continue...", 250, 300, 40, -1);
	endScreen->addActor(endButton);
}

void Game::update(float deltaTime)
{
	getCurrentScene()->update(deltaTime);

	// Only spawn enemies in the main scene
	if (getCurrentSceneIndex() == 1)
		spawnEnemies();
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(RAYWHITE);

	getCurrentScene()->draw();

	if (getCurrentSceneIndex() > 0)
	{
		char scoreString[128];
		sprintf_s(scoreString, "Score: %d", m_player->getScore());
		DrawText(scoreString, 10, 10, 30, BLUE);
	}

	EndMode2D();
	EndDrawing();
}

void Game::end()
{

}

MathLibrary::Matrix3* Game::getWorld()
{
	return getCurrentScene()->getWorld();
}

void Game::run()
{
	start();

	while (!m_gameOver && !RAYLIB_H::WindowShouldClose())
	{
		float deltaTime = RAYLIB_H::GetFrameTime();
		update(deltaTime);
		draw();
	}

	end();
}

Scene* Game::getScene(int index)
{
	if (index < 0 || index >= m_sceneCount)
		return nullptr;

	return m_scenes[index];
}

Scene* Game::getCurrentScene()
{
	return m_scenes[m_currentSceneIndex];
}

int Game::getCurrentSceneIndex()
{
	return m_currentSceneIndex;
}

int Game::addScene(Scene* scene)
{
	if (!scene)
		return -1;

	Scene** tempArray = new Scene*[m_sceneCount + 1];

	for (int i = 0; i < m_sceneCount; i++)
		tempArray[i] = m_scenes[i];

	int index = m_sceneCount;

	tempArray[index] = scene;

	m_scenes = tempArray;
	m_sceneCount++;

	return index;
}

bool Game::removeScene(Scene* scene)
{
	if (!scene)
		return false;

	bool sceneRemoved = false;

	Scene** tempArray = new Scene*[m_sceneCount - 1];

	//Copy all Scenes except for the passed in Scene into tempArray
	int j = 0;
	for (int i = 0; i < m_sceneCount; i++)
	{
		if (tempArray[i] != scene)
		{
			tempArray[j] = m_scenes[i];
			j++;
		}
		else
			sceneRemoved = true;
	}

	if (sceneRemoved)
	{
		m_scenes = tempArray;
		m_sceneCount--;
	}
	return sceneRemoved;
}

void Game::setCurrentScene(int index)
{
	if (index < 0 || index >= m_sceneCount)
		return;

	if (m_scenes[m_currentSceneIndex]->getStarted())
		m_scenes[m_currentSceneIndex]->end();

	m_currentSceneIndex = index;
}

bool Game::getKeyDown(int key)
{
	return RAYLIB_H::IsKeyDown((KeyboardKey)key);
}

bool Game::getKeyPressed(int key)
{
	return RAYLIB_H::IsKeyPressed((KeyboardKey)key);
}

void Game::destroy(Actor* actor)
{
	getCurrentScene()->removeActor(actor);
	if (actor->getParent())
		actor->getParent()->removeChild(actor);
	actor->end();
	delete actor;
}

void Game::setGameOver(bool value)
{
	Game::m_gameOver = value;
}