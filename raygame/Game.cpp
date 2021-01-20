#include "Game.h"
#include "raylib.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

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

	// Init new scene
	Scene* scene1 = new Scene();
	addScene(scene1);

	Player* player = new Player(100, 100, 0);
	scene1->addActor(player);

	Enemy* enemy = new Enemy(100, 100, 1, "/Images/Player.png", 50, 1, 1);
	scene1->addActor(enemy);
	enemy->setTarget(player);
}

void Game::update(float deltaTime)
{
	for (int i = 0; i < m_sceneCount; i++)
		m_scenes[i]->update(deltaTime);
}

void Game::draw()
{
	BeginDrawing();

	BeginMode2D(*m_camera);
	ClearBackground(RAYWHITE);

	for (int i = 0; i < m_sceneCount; i++)
		m_scenes[i]->draw();

	EndMode2D();
	EndDrawing();
}

void Game::end()
{
	CloseWindow();
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