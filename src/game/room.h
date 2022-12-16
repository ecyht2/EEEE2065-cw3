#ifndef ROOM_H_
#define ROOM_H_

#include <vector>
#include <string>
#include <memory>

#include "generics.h"
#include "enemies.h"

/** Enumeration of Direction of the room. */
enum Direction {
NORTH, /**<The north direction. */
SOUTH, /**<The south direction. */
EAST, /**<The east direction. */
WEST /**<The west direction. */
};

/** Enumeration of kill statuses. */
enum KillStatus {
KILL_SUCCESS, /**<Sucessfully killed enemy. */
KILL_FAILURE, /**<Failed to kill enemy. */
NO_ENEMY, /**<The enemy given isn't valid. */
DEAD_ENEMY /**<The enemy is already dead. */
};

/** A class representing a room in the adventure game. */
class Room {
        public:
                /** Constructor for Room class.
                 *
                 * @param name The name of the room.
                 * */
                Room(std::string name = "Room");

                //////////
                // Setters
                /** Adds an item to the room.
                 *
                 * @param item The item to add.
                 * */
                void addItem(std::shared_ptr<GenericItem> item);
                /** Adds an enemy to the room.
                 *
                 * @param enemy The enemy to add.
                 * */
                void addEnemey(std::shared_ptr<GenericEnemy> enemy);
                /** Removes an the first item with the same name from the room.
                 *
                 * @param item The item name to remove.
                 * @return The item removed.
                 * */
                std::shared_ptr<GenericItem> removeItem(std::string item);
                /** Removes an the first enemy with the same name from the room.
                 *
                 * @param enemy The enemy name to remove.
                 * @return The enemy removed.
                 * */
                std::shared_ptr<GenericEnemy> removeEnemey(std::string enemy);
                /** Removes an item to the item room.
                 *
                 * @param index The index of the item to remove. -1 to remove
                 * last item on the list. (nullptr will be returned if index is
                 * out of range).
                 * @return item The item removed.
                 * */
                std::shared_ptr<GenericItem> removeItem(size_t index = -1);
                /** Removes an enemy to the room.
                 *
                 * @param index The index of the enemy to remove -1 to remove
                 * last item on the list. (nullptr will be returned if index is
                 * out of range).
                 * @return enemy The enemy removed.
                 * */
                std::shared_ptr<GenericEnemy> removeEnemey(size_t index = -1);
                /** Sets the name of the room.
                 *
                 * @param name The name of the room.
                 * */
                void setName(std::string name);
                /** Unlocks the room. */
                void unlockRoom(void);
                /** Locks the room. */
                void lockRoom(void);

                // Room setting
                /** Dynmaically add a new room to the north.
                 *
                 * @param name The name of the room.
                 * @return The new room that is created. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setNorth(std::string name);
                /** Dynmaically add a new room to the south.
                 *
                 * @param name The name of the room.
                 * @return The new room that is created. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setSouth(std::string name);
                /** Dynmaically add a new room to the east.
                 *
                 * @param name The name of the room.
                 * @return The new room that is created. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setEast(std::string name);
                /** Dynmaically add a new room to the west.
                 *
                 * @param name The name of the room.
                 * @return The new room that is created. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setWest(std::string name);
                /** Sets the room north of this to room.
                 *
                 * @param room The room set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setNorth(Room *room);
                /** Sets the room south of this to room.
                 *
                 * @param room The room set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setSouth(Room *room);
                /** Sets the room east of this to room.
                 *
                 * @param room The room set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setEast(Room *room);
                /** Sets the room west of this to room.
                 *
                 * @param room The room set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room.
                 * */
                Room* setWest(Room *room);
                /** Sets the room in the direction given.
                 *
                 * @param room The room set.
                 * @param direction The direction of the room to set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room.
                 *
                 * @see Direction
                 * */
                Room* setRoom(Room *room, Direction direction);
                /** Dynmaically add a new room in the direction given.
                 *
                 * @param name The name of the room.
                 * @param direction The direction of the room to set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room.
                 *
                 * @see Direction
                 * */
                Room* setRoom(std::string name, Direction direction);
                /** Sets the room in the direction given.
                 *
                 * @param room The room set.
                 * @param direction The direction of the room to set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room or the direction
                 * is invalid.
                 * */
                Room* setRoom(Room *room, std::string direction);
                /** Dynmaically add a new room in the direction given.
                 *
                 * @param name The name of the room.
                 * @param direction The direction of the room to set.
                 * @return The new room that is set. nullptr is returned
                 * if the direction already has a room or the direction
                 * is invalid.
                 * */
                Room* setRoom(std::string name, std::string direction);

                //////////
                // Getters
                /** Gets the name of the room.
                 *
                 * @return The name of the room.
                 * */
                std::string getName(void) const;
                /** Gets the enemies in the room.
                 *
                 * @return A vector of all the enemies.
                 * */
                std::vector<GenericEnemy *> getEnemies(void) const;
                /** Gets the items in the room.
                 *
                 * @return A vector of all the items.
                 * */
                std::vector<GenericItem *> getItems(void) const;
                /** Gets if the room is locked or not.
                 *
                 * @return If the room is locked or not.
                 */
                bool isLocked(void) const;
                /** Gets the room of the given direction.
                 *
                 * @param direction The direction of the room to get.
                 * @return The room at the direction. nullptr would be returned
                 * if the room doesn't exist.
                 *
                 * @see Direction
                 * */
                Room* getRoom(Direction direction) const;
                /** Gets the room of the given direction.
                 *
                 * @param direction The direction of the room to get.
                 * @return The room at the direction. nullptr would be returned
                 * if the room doesn't exist or the direction is invalid.
                 * */
                Room* getRoom(std::string direction) const;
                /** Gets the room to the north of the room.
                 *
                 * @return The room to the north of the room. nullptr would be
                 * returned if the room doesn't exist.
                 * */
                Room* getNorth(void) const;
                /** Gets the room to the south of the room.
                 *
                 * @return The room to the south of the room. nullptr would be
                 * returned if the room doesn't exist.
                 * */
                Room* getSouth(void) const;
                /** Gets the room to the east of the room.
                 *
                 * @return The room to the east of the room. nullptr would be
                 * returned if the room doesn't exist.
                 * */
                Room* getEast(void) const;
                /** Gets the room to the west of the room.
                 *
                 * @return The room to the west of the room. nullptr would be
                 * returned if the room doesn't exist.
                 * */
                Room* getWest(void) const;
                /** Gets the description of the room.
                 *
                 * @return The description of the room.
                 * */
                std::string getDescription(void) const;

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
                KillStatus killEnemy(std::string name, GenericEntity *killer);
                /** Kills the first enemy in the list with the same name.
                 *
                 * @param index The index of the enemy in the list.
                 * @param killer The entity that is killing the enemy.
                 * @return The kill status.
                 *
                 * @see KillStatus
                 * */
                KillStatus killEnemy(size_t index, GenericEntity *killer);

                ////////////
                // Operators
                /** Overloaded operator to print the description of the room.
                 *
                 * @param out The output stream.
                 * @param cls The class iteself.
                 *
                 * @return The new output stream.
                 * */
                friend std::ostream& operator << (std::ostream &out, const Room &cls);
        private:
                bool m_locked = false;
                std::vector<std::shared_ptr<GenericItem>> m_items;
                std::vector<std::shared_ptr<GenericEnemy>> m_enemies;
                Room *north = nullptr;
                Room *south = nullptr;
                Room *east = nullptr;
                Room *west = nullptr;
                std::string m_name = "Room";
};

#endif // ROOM_H_
