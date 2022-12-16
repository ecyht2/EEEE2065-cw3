#include "room.h"

#include <vector>
#include <memory>
#include <algorithm>
#include <exception>
#include <iostream>
#include <sstream>

#include "generics.h"
#include "enemies.h"

/** Constructor for Room class.
 *
 * @param name The name of the room.
 * */
Room::Room(std::string name): m_name(name) {
}

//////////
// Setters
/** Adds an item to the item room.
 *
 * @param item The item to add.
 * */
void Room::addItem(std::shared_ptr<GenericItem> item) {
    this->m_items.push_back(item);
}

/** Adds an enemy to the room.
 *
 * @param enemy The enemy to add.
 * */
void Room::addEnemey(std::shared_ptr<GenericEnemy> enemy) {
    this->m_enemies.push_back(enemy);
}

/** Removes an the first item with the same name from the room.
 *
 * @param item The item name to remove.
 * @return The item removed.
 * */
std::shared_ptr<GenericItem> Room::removeItem(std::string item) {
    std::shared_ptr<GenericItem> ret = nullptr;

    // Looping over all item
    for (size_t i = 0; i < this->m_items.size(); i++) {
        // Checking if the name is the same
        if (*(this->m_items.at(i)) == item) {
            ret = this->removeItem(i);
            return ret;
        }
    }
    return ret;
}

/** Removes an the first enemy with the same name from the room.
 *
 * @param enemy The enemy name to remove.
 * @return The enemy removed.
 * */
std::shared_ptr<GenericEnemy> Room::removeEnemey(std::string enemy) {
    std::shared_ptr<GenericEnemy> ret = nullptr;

    // Looping over all item
    for (size_t i = 0; i < this->m_enemies.size(); i++) {
        // Checking if the name is the same
        if (*(this->m_items.at(i)) == enemy) {
            ret = this->removeEnemey(i);
            return ret;
        }
    }
    return ret;
}

/** Removes an item to the item room.
 *
 * @param index The index of the item to remove. -1 to remove
 * last item on the list. (nullptr will be returned if index is out of range).
 * @return item The item removed.
 * */
std::shared_ptr<GenericItem> Room::removeItem(size_t index) {
    std::shared_ptr<GenericItem> ret = nullptr;

    // index < 0 (-1)
    if (index < 0) {
        ret = this->m_items.at(this->m_items.size() - 1);
        this->m_items.pop_back();
    } else if (index < this->m_items.size()) { // Positive index
        ret = this->m_items.at(index);
        this->m_items.erase(this->m_items.begin() + index);
    } else { // Out of range
        ret = nullptr;
    }
    return ret;
}

/** Removes an enemy to the room.
 *
 * @param index The index of the enemy to remove -1 to remove
 * last item on the list. (nullptr will be returned if index is out of range).
 * @return enemy The enemy removed.
 * */
std::shared_ptr<GenericEnemy> Room::removeEnemey(size_t index) {
    std::shared_ptr<GenericEnemy> ret = nullptr;

    // index < 0 (-1)
    if (index < 0) {
        ret = *(this->m_enemies.end() - 1);
        this->m_items.pop_back();
    } else if (index < this->m_items.size()) { // Positive index
        ret = this->m_enemies.at(index);
        this->m_items.erase(this->m_items.begin() + index);
    } else { // Out of range
        ret = nullptr;
    }
    return ret;
}

/** Sets the name of the room.
 *
 * @param name The name of the room.
 * */
void Room::setName(std::string name) {
    this->m_name = name;
}

/** Unlocks the room. */
void Room::unlockRoom(void) {
    this->m_locked = false;
}

/** Locks the room. */
void Room::lockRoom(void) {
    this->m_locked = true;
}

/** Dynmaically add a new room to the north.
 *
 * @param name The name of the room.
 * @return The new room that is created. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setNorth(std::string name) {
    return this->setRoom(name, NORTH);
}

/** Dynmaically add a new room to the south.
 *
 * @param name The name of the room.
 * @return The new room that is created. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setSouth(std::string name) {
    return this->setRoom(name, SOUTH);
}

/** Dynmaically add a new room to the east.
 *
 * @param name The name of the room.
 * @return The new room that is created. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setEast(std::string name) {
    return this->setRoom(name, EAST);
}

/** Dynmaically add a new room to the west.
 *
 * @param name The name of the room.
 * @return The new room that is created. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setWest(std::string name) {
    return this->setRoom(name, WEST);
}

/** Sets the room north of this to room.
 *
 * @param room The room set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setNorth(Room *room) {
    return this->setRoom(room, NORTH);
}

/** Sets the room south of this to room.
 *
 * @param room The room set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setSouth(Room *room) {
    return this->setRoom(room, SOUTH);
}

/** Sets the room east of this to room.
 *
 * @param room The room set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setEast(Room *room) {
    return this->setRoom(room, EAST);
}

/** Sets the room west of this to room.
 *
 * @param room The room set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room.
 * */
Room* Room::setWest(Room *room) {
    return this->setRoom(room, WEST);
}

/** Sets the room in the direction given.
 *
 * @param room The room set.
 * @param direction The direction of the room to set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room.
 *
 * @see Direction
 * */
Room* Room::setRoom(Room *room, Direction direction) {
    Room **ptr;

    // Getting current pointer at the direction
    switch (direction) {
        case NORTH:
            ptr = &this->north;
            break;
        case SOUTH:
            ptr = &this->south;
            break;
        case EAST:
            ptr = &this->east;
            break;
        case WEST:
            ptr = &this->west;
            break;
    }

    // Return nullptr if it is already set
    if (*ptr != nullptr) {
        return nullptr;
    } else {
        *ptr = room;

        // Setting this to the opposite direction of the new room
        switch (direction) {
            case NORTH:
                (*ptr)->south = this;
                break;
            case SOUTH:
                (*ptr)->north = this;
                break;
            case EAST:
                (*ptr)->west = this;
                break;
            case WEST:
                (*ptr)->east = this;
                break;
        }

        // Returning pointer
        return *ptr;
    }
}

/** Dynmaically add a new room in the direction given.
 *
 * @param name The name of the room.
 * @param direction The direction of the room to set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room.
 *
 * @see Direction
 * */
Room* Room::setRoom(std::string name, Direction direction) {
    // Creating new room
    Room *room = new Room(name);

    Room* ret = this->setRoom(room, direction);

    // If failed to set room delete the pointer
    if (ret == nullptr) {
        delete room;
    }
    return ret;
}

/** Sets the room in the direction given.
 *
 * @param room The room set.
 * @param direction The direction of the room to set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room or the direction
 * is invalid.
 * */
Room* Room::setRoom(Room *room, std::string direction) {
    // Converting to lower case
    std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower);
    if (direction == "north") {
        return this->setRoom(room, NORTH);
    } else if (direction == "south") {
        return this->setRoom(room, SOUTH);
    } else if (direction == "east") {
        return this->setRoom(room, EAST);
    } else if (direction == "west") {
        return this->setRoom(room, WEST);
    } else {
        return nullptr;
    }
}

/** Dynmaically add a new room in the direction given.
 *
 * @param name The name of the room.
 * @param direction The direction of the room to set.
 * @return The new room that is set. nullptr is returned
 * if the direction already has a room or the direction
 * is invalid.
 * */
Room* Room::setRoom(std::string name, std::string direction) {
    // Creating new room
    Room *room = new Room(name);

    Room* ret = this->setRoom(room, direction);

    // If failed to set room delete the pointer
    if (ret == nullptr) {
        delete room;
    }
    return ret;
}

//////////
// Getters
/** Gets the name of the room.
 *
 * @return The name of the room.
 * */
std::string Room::getName(void) const {
    return this->m_name;
}

/** Gets the enemies in the room.
 *
 * @return A vector of all the enemies.
 * */
std::vector<GenericEnemy *> Room::getEnemies(void) const {
    std::vector<GenericEnemy *> ret_vector;

    for (std::size_t i = 0; i < this->m_enemies.size(); i++) {
        ret_vector.push_back(this->m_enemies.at(i).get());
    }

    return ret_vector;
}

/** Gets the items in the room.
 *
 * @return A vector of all the items.
 * */
std::vector<GenericItem *> Room::getItems(void) const {
    std::vector<GenericItem *> ret_vector;

    for (std::size_t i = 0; i < this->m_items.size(); i++) {
        ret_vector.push_back(this->m_items.at(i).get());
    }

    return ret_vector;
}

/** Gets if the room is locked or not.
 *
 * @return If the room is locked or not.
 */
bool Room::isLocked(void) const {
    return this->m_locked;
}

/** Gets the room of the given direction.
 *
 * @param direction The direction of the room to get.
 * @return The room at the direction. nullptr would be returned
 * if the room doesn't exist.
 *
 * @see Direction
 * */
Room* Room::getRoom(Direction direction) const {
    switch (direction) {
        case NORTH:
            return this->north;
            break;
        case SOUTH:
            return this->south;
            break;
        case EAST:
            return this->east;
            break;
        case WEST:
            return this->west;
            break;
        default:
            return nullptr;
            break;
    }
}

/** Gets the room of the given direction.
 *
 * @param direction The direction of the room to get.
 * @return The room at the direction. nullptr would be returned
 * if the room doesn't exist or the direction is invalid.
 * */
Room* Room::getRoom(std::string direction) const {
    std::transform(direction.begin(), direction.end(), direction.begin(), ::tolower);

    if (direction == "north") {
        return this->getRoom(NORTH);
    } else if (direction == "south") {
        return this->getRoom(SOUTH);
    } else if (direction == "east") {
        return this->getRoom(EAST);
    } else if (direction == "west") {
        return this->getRoom(WEST);
    } else {
        return nullptr;
    }
}

/** Gets the room to the north of the room.
 *
 * @return The room to the north of the room. nullptr would be
 * returned if the room doesn't exist.
 * */
Room* Room::getNorth(void) const {
    return this->getRoom(NORTH);
}

/** Gets the room to the south of the room.
 *
 * @return The room to the south of the room. nullptr would be
 * returned if the room doesn't exist.
 * */
Room* Room::getSouth(void) const {
    return this->getRoom(SOUTH);
}

/** Gets the room to the east of the room.
 *
 * @return The room to the east of the room. nullptr would be
 * returned if the room doesn't exist.
 * */
Room* Room::getEast(void) const {
    return this->getRoom(EAST);
}

/** Gets the room to the west of the room.
 *
 * @return The room to the west of the room. nullptr would be
 * returned if the room doesn't exist.
 * */
Room* Room::getWest(void) const {
    return this->getRoom(WEST);
}

/** Gets the description of the room.
 *
 * @return The description of the room.
 * */
std::string Room::getDescription(void) const {
    std::ostringstream description;

    description << "You are in a " << this->getName() << ". ";

    for (GenericEnemy *i: this->getEnemies()) {
        if (i->isDead()) {
            description << "There is a dead " << *i << " here. ";
        } else {
            description << "There is a " << *i << " here. ";
        }
    }

    for (GenericItem *i: this->getItems()) {
        description << "You see a " << *i << " here. ";
    }

    for (std::string i: {"north", "south", "east", "west"}) {
        Room *room = this->getRoom(i);
        if (room != nullptr) {
            description << "There is a " << room->getName()
                        << " to the " << i << ". ";
        }
    }

    return description.str();
}

/////////
// Others
/** Kills the first enemy in the list with the same name.
 *
 * @param name The name of the enemy.
 * @param killer The entity that is killing the enemy.
 * @return The kill status.
 *
 * @see KillStatus
 * */
KillStatus Room::killEnemy(std::string name, GenericEntity *killer) {
    // Looping over all enemies
    for (size_t i = 0; i < this->getEnemies().size(); i++) {
        if (*(this->getEnemies().at(i)) == name) {
            return this->killEnemy(i, killer);
        }
    }
    return KillStatus::NO_ENEMY;
}

/** Kills the first enemy in the list with the same name.
 *
 * @param index The index of the enemy in the list.
 * @param killer The entity that is killing the enemy.
 * @return The kill status.
 *
 * @see KillStatus
 * */
KillStatus Room::killEnemy(size_t index, GenericEntity *killer) {
    GenericEnemy* enemy = nullptr;

    // Checking if it is a valid enemy
    try {
        enemy = this->getEnemies().at(index);
    } catch (std::out_of_range const &err) {
        return KillStatus::NO_ENEMY;
    }

    // If enemy is dead
    if (enemy->isDead()) {
        return KillStatus::DEAD_ENEMY;
    }

    // Deal Damage until either dies
    while (!killer->isDead() && !enemy->isDead()) {
        killer->dealDamage(enemy);
        if (!(enemy->isDead())) {
            enemy->dealDamage(killer);
        }
    }

    // If killer died
    if (killer->isDead()) {
        return KillStatus::KILL_FAILURE;
    } else { // Successful kill
        return KillStatus::KILL_SUCCESS;
    }
}

////////////
// Operators
/** Overloaded operator to print the description of the room.
 *
 * @param out The output stream.
 * @param cls The class iteself.
 *
 * @return The new output stream.
 * */
std::ostream& operator << (std::ostream &out, const Room &cls) {
    out << cls.getDescription() << std::endl;
    return out;
}
