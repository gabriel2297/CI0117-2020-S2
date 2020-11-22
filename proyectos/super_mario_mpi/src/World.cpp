#include "../include/World.h"

using namespace std;

World::World()
{
    initWorld();
}

World::~World()
{
    delete this;
}

/**
 * Initiates a new array, which will represent the world
 * Pushes a queue to each index of the array, elements will be pushed to here
*/
void World::initWorld()
{
    for (int i = 0; i < WORLD_SLOTS; ++i)
    {
        this->world.push_back(cola());
    }
    cout << "Successfully created an array of queues of size " << WORLD_SLOTS << endl;
}

/**
 * @param element - the element we want to push, must be an enum
 * @param index - the position in the array where we want to push that element
*/
void World::pushElement(Element element, int index)
{
    this->world[index].push(element);
}

/**
 * @param index - the position in the array
 * @return the total elements in this position
 */
int World::getTotalElementsInPosition(int index)
{
    return this->world[index].size();
}

/**
 * @param index - the position in the array
 * @return The next element in the queue, None if empty, or any other Element
*/
Element World::getNextElementInPosition(int index)
{
    if (this->world[index].empty())
        return None;
    switch (this->world[index].front())
    {
    case Coin:
        this->world[index].pop();
        return Coin;
    case Hole:
        this->world[index].pop();
        return Hole;
    case LittleGoomba:
        this->world[index].pop();
        return LittleGoomba;
    case KoopaTroopa:
        this->world[index].pop();
        return KoopaTroopa;
    default:
        this->world[index].pop();
        return None;
    }
}