#pragma once
#include "Actor.h"

class Scene
{
public:
    Scene();

    /// <returns>If this Scene is the current active Scene in the game.</returns>
    bool getStarted() { return m_started; }

    /// <returns>The Scenes matrix that represents the world transform.</returns>
    MathLibrary::Matrix3* getWorld();

    /// <summary>
    /// Adds the given Actor to the array of Actors so that the Scene may call its update and draw functions.
    /// </summary>
    /// <param name="actor">The Actor to add to the Scene.</param>
    void addActor(Actor* actor);

    /// <summary>
    /// Removes the Actor at the given index. DOES NOT DELETE THE ACTOR!!!
    /// </summary>
    /// <param name="index">The index the Actor is in the Scene's array.</param>
    /// <returns>False if the index given is out of bounds.</returns>
    bool removeActor(int index);

    /// <summary>
    /// Removes the Actor given if it's in the array. DOES NOT DELETE THE ACTOR!!!
    /// </summary>
    /// <param name="actor">The Actor to look for in the Scene's array.</param>
    /// <returns>False if the Actor is a nullptr or isn't in the array.</returns>
    bool removeActor(Actor* actor);

    virtual void start();

    /// <summary>
    /// Checks if any Actor has collided in Scene. Calls the Actors onCollision function if so.
    /// </summary>
    virtual void checkCollision();

    virtual void update(float deltaTime);

    virtual void draw();

    virtual void debug();

    virtual void end();

private:
    Actor** m_actors;
    MathLibrary::Matrix3* m_world;
    bool m_started;
    int m_actorCount;
};