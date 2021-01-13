#pragma once
#include "Scene.h"
class Camera2D;

static class Game
{
public:
    Game();
    /// <summary>
    /// Returns the Scene at the index given.
    /// Returns an empty Scene if the index is out of bounds
    /// </summary>
    /// <param name="index">The index of the desired Scene</param>
    /// <returns></returns>
    static Scene* getScene(int index);


    /// <summary>
    /// Returns the Scene that's at the index of the current Scene index
    /// </summary>
    /// <returns></returns>
    static Scene* getCurrentScene();

    /// <returns>The current index of m_scenes.</returns>
    static int getCurrentSceneIndex();

    /// <summary>
    /// Adds the given scene to the array of Scenes.
    /// </summary>
    /// <param name="scene">The Scene that will be added to m_scenes</param>
    /// <returns>The index the Scene was placed at. Returns -1 if the Scene is null</returns>
    static int addScene(Scene* scene);

    /// <summary>
    /// Finds the instance of the Scene given that inside of the array
    /// and removes it
    /// </summary>
    /// <param name="scene">The Scene that will be removed</param>
    /// <returns>If the Scene was successfully removed</returns>
    static bool removeScene(Scene* scene);


    /// <summary>
    /// Sets the current Scene in the game to be the Scene at the given index
    /// </summary>
    /// <param name="index">The index of the Scene to switch to</param>
    static void setCurrentScene(int index);


    /// <summary>
    /// Returns true while a key is being pressed
    /// </summary>
    /// <param name="key">The ascii value of the key to check</param>
    /// <returns></returns>
    static bool getKeyDown(int key);

    /// <summary>
    /// Returns true while if key was pressed once
    /// </summary>
    /// <param name="key">The ascii value of the key to check</param>
    /// <returns></returns>
    static bool getKeyPressed(int key);

    /// <summary>
    /// Removes the Actor from the Scene, removes it from its parent, calls its end function, and deletes the Actor.
    /// </summary>
    /// <param name="actor">The Actor that will be deleted.</param>
    static void destroy(Actor* actor);

    /// <summary>
    /// Sets the Game state to be the given value. If true, the Game will end.
    /// </summary>
    /// <param name="value">The value to set m_gameOver.</param>
    static void setGameOver(bool value);

    /// <returns>The world Matrix of the current Scene.</returns>
    static MathLibrary::Matrix3* getWorld();
    void run();

private:
	void start();
	void update(float delaTime);
	void draw();
	void end();

private:
    Camera2D* m_camera;
    static bool m_gameOver;
	static Scene** m_scenes;
    static int m_sceneCount;
    static int m_currentSceneIndex;
};