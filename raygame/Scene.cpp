#include "Scene.h"

Scene::Scene()
{
    m_actorCount = 0;
    m_actors = new Actor*[0];
    m_world = new MathLibrary::Matrix3();
}

MathLibrary::Matrix3* Scene::getWorld()
{
    return m_world;
}

void Scene::addActor(Actor* actor)
{
    Actor** appendedArray = new Actor * [m_actorCount + 1];
    for (int i = 0; i < m_actorCount; i++)
        appendedArray[i] = m_actors[i];

    appendedArray[m_actorCount] = actor;
    m_actors = appendedArray;
    m_actorCount++;

    for (int i = 0; i < actor->getChildCount(); i++)
        addActor(actor->getChildren()[i]);

    m_numActors++;
}

bool Scene::removeActor(int index)
{
    if (index < 0 || index >= m_actorCount)
        return false;

    bool actorRemoved = false;

    //Create a new array with a size one less than the old array 
    Actor** newArray = new Actor * [m_actorCount - 1];
    int j = 0;
    for (int i = 0; i < m_actorCount; i++)
    {
        if (i != index)
        {
            newArray[j] = m_actors[i];
            j++;
        }
        else
        {
            delete m_actors[i];
            actorRemoved = true;
        }
    }

    m_actors = newArray;
    m_actorCount--;
    return actorRemoved;
}

bool Scene::removeActor(Actor* actor)
{
    if (!actor)
        return false;

    bool actorRemoved = false;
    //Create a new array with a size one less than the old array
    Actor** newArray = new Actor * [m_actorCount - 1];
    int j = 0;
    for (int i = 0; i < m_actorCount; i++)
    {
        if (actor != m_actors[i])
        {
            newArray[j] = m_actors[i];
            j++;
        }
        else
            actorRemoved = true;
    }
    m_actors = newArray;
    m_actorCount--;
    return actorRemoved;
}

void Scene::start()
{
    m_started = true;
}

void Scene::checkCollision()
{
    for (int i = 0; i < m_actorCount; i++)
    {
        for (int j = 0; j < m_actorCount; j++)
        {
            if (i >= m_actorCount)
                break;

            if (m_actors[i]->checkCollision(m_actors[j]) && i != j)
                m_actors[i]->onCollision(m_actors[j]);
        }
    }
}

void Scene::update(float deltaTime)
{
    for (int i = 0; i < m_actorCount; i++)
    {
        if (!m_actors[i]->getStarted())
            m_actors[i]->start();

        m_actors[i]->update(deltaTime);
    }
    checkCollision();
}

void Scene::draw()
{
    for (int i = 0; i < m_actorCount; i++)
        m_actors[i]->draw();
}

void Scene::debug()
{
    for (int i = 0; i < m_actorCount; i++)
    {
        if (m_actors[i]->getStarted())
            m_actors[i]->debug();
    }
}

void Scene::end()
{
    for (int i = 0; i < m_actorCount; i++)
        if (m_actors[i]->getStarted())
            m_actors[i]->end();

    m_started = false;
}