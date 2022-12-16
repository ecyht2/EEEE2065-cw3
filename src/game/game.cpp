#include "game.h"

#include <iostream>

#include "player.h"
#include "items.h"
#include "enemies.h"

/** Setup Room2
 *
 * @param room Pointer to Room1
 * */
static Room* setupRoom2(Room *room) {
    Room *room2 = room->setEast("Castle Hall");
    room2->addItem(std::shared_ptr<Consumable> (new Consumable("Food", 5)));
    return room2;
}

/** Setup Room3
 *
 * @param room Pointer to Room2
 * */
static Room* setupRoom3(Room *room) {
    Room *room3 = room->setEast("Armory");

    std::shared_ptr<Weapon> spear(new Weapon("Silver Spear", 1));
    room3->addItem(spear);
    room3->addEnemey(std::shared_ptr<GenericEnemy>(
                         new GenericEnemy(6, 1, "Zombie", spear)));

    return room3;
}

/** Setup Room5
 *
 * @param room Pointer to Room2
 * */
static Room* setupRoom5(Room *room) {
    Room *room5 = room->setSouth("Castle Center");

    room5->addItem(std::shared_ptr<Weapon>(new Weapon("Sword", 2)));
    room5->addEnemey(std::shared_ptr<GenericEnemy>(
                         new GenericEnemy(5, 1, "Lizard-man")));

    return room5;
}

/** Setup Room8
 *
 * @param room Pointer to Room5
 * */
static Room* setupRoom8(Room *room) {
    Room *room8 = room->setSouth("Religious Room");

    std::shared_ptr<GenericItem> cross(new GenericItem("Diamond Cross"));
    room8->addItem(cross);
    room8->addEnemey(std::shared_ptr<Werewolf>(
                         new Werewolf(12, 3, "Werewolf", cross)));

    return room8;
}

/** Setup Room4
 *
 * @param room Pointer to Room5
 * */
static Room* setupRoom4(Room *room) {
    Room *room4 = room->setWest("Medical Room");

    room4->addItem(std::shared_ptr<Consumable>(new Consumable("Medpack", 10)));

    return room4;
}

/** Setup Room7
 *
 * @param room Pointer to Room4
 * */
static Room* setupRoom7(Room *room) {
    Room *room7 = room->setSouth("Storage Room");

    std::shared_ptr<GenericItem> key(new GenericItem("Copper Key"));
    room7->addItem(key);
    room7->addEnemey(std::shared_ptr<Vampire>(new Vampire(12, 3, "Dracula", key)));

    return room7;
}

/** Setup Room6
 *
 * @param room Pointer to Room5
 * */
static Room* setupRoom6(Room *room) {
    Room *room6 = room->setEast("Magic Room");

    room6->addItem(std::shared_ptr<Consumable>(new Consumable("Elixir", 10)));
    room6->addEnemey(std::shared_ptr<GenericEnemy>(
                         new GenericEnemy(4, 3, "Monster")));

    return room6;
}

/** Setup Room9
 *
 * @param room Pointer to Room6
 * */
static Room* setupRoom9(Room *room) {
    Room *room9 = room->setSouth("Boss Room");

    auto ptr = std::shared_ptr<GenericItem>(new GenericItem("Golden Chalice"));
    room9->addItem(ptr);
    room9->addEnemey(std::shared_ptr<GenericEnemy>(
                         new GenericEnemy(12, 4, "Dragon", ptr)));
    room9->lockRoom();

    return room9;
}

/** Constructor class for coursework game. */
AdventureGame::AdventureGame(void) {
    Player *player = new Player();
    this->setPlayer(player);

    // Room 1
    rooms[0] = new Room("Castle Entrance");
    this->m_initial_room = rooms[0];
    this->setRoom(rooms[0]);
    // Room 2
    rooms[1] = setupRoom2(rooms[0]);
    // Room 3
    rooms[2] = setupRoom3(rooms[1]);
    // Room 5
    rooms[4] = setupRoom5(rooms[1]);
    // Room 8
    rooms[7] = setupRoom8(rooms[4]);
    // Room 4
    rooms[3] = setupRoom4(rooms[4]);
    // Room 7
    rooms[6] = setupRoom7(rooms[3]);
    // Room 6
    rooms[5] = setupRoom6(rooms[4]);
    // Room 9
    rooms[8] = setupRoom9(rooms[5]);

    // Adding Commands
    this->addMultipleCommands({"north", "n"}, "Go to the room north.");
    this->addMultipleCommands({"south", "s"}, "Go to the room south.");
    this->addMultipleCommands({"east", "e"}, "Go to the room east.");
    this->addMultipleCommands({"west", "w"}, "Go to the room west.");
    this->addMultipleCommands({"look", "l"}, "Shows what is in the room.");
    this->addMultipleCommands({"killMonster", "km"}, "Kills the monster in the room.");
    this->addMultipleCommands({"inventory", "i"}, "Shows the player's inventory.");
    this->addCommands({
        {"kill {monster}", "Kills the monster with the name {monster}."},
        {"get {item}", "Gets the item with the name {item}."},
        {"drop {item}", "Drops the item with the name {item}."},
        {"eat food", "Eat the food in the inventory."},
        {"drink elixir", "Drink the elixir in the inventory."},
        {"use medpack", "Use the medpack in the inventory."},
        {"unlock door", "Unlocks the locked rooms."}
    });
}

/** Destuctor function to delete dynamically allocated room. */
AdventureGame::~AdventureGame(void) {
    for (int i = 0; i < 9; i++) {
        if (rooms[i] != nullptr) {
            delete rooms[i];
        }
    }
}

/** Overriden to add new commands. */
GameStatus AdventureGame::processCommand(void) {
    std::string cmd = this->getCurrentCommand();

    // Movement Commands
    if (cmd == "north" || cmd == "n" ||
        cmd == "south" || cmd == "s" ||
        cmd == "east" || cmd == "e" ||
        cmd == "west" || cmd == "w") {

        // Setting short form to the long form
        if(cmd == "n") {
            cmd = "north";
        } else if(cmd == "s") {
            cmd = "south";
        } else if(cmd == "e") {
            cmd = "east";
        } else if(cmd == "w") {
            cmd = "west";
        }

        // Getting Room
        Room *room = this->getRoom()->getRoom(cmd);
        if (room != nullptr) {
            // Checking if the room is locked
            if (room->isLocked()) {
                std::cout << "The room is locked you must find a way to"
                          << " unlock it." << std::endl;
            } else {
                this->setRoom(room);
                std::cout << "You go " << cmd << " to "
                          << room->getName() << std::endl;
            }

            // Checking if the room is the intial room
            if (room == m_initial_room) {
                // Wins the game if player has golden chalice
                if (this->getPlayer()->getInventory()->
                    getItem("Golden Chalice") != nullptr) {
                    return GameStatus::VICTORY;
                }
            } else {
                return GameStatus::CONTINUE;
            }
        } else {
            std::cout << "There is no room to the "
                      << cmd << std::endl;
        }

        return GameStatus::CONTINUE;
    }

    // Look command
    if (cmd == "look" || cmd == "l") {
        Room *room = this->getRoom();
        std::cout << "You looked around. " << *room;
        return GameStatus::CONTINUE;
    }

    // Fight Commands
    if (cmd == "killmonster" || cmd == "km") {
        GenericEnemy *target = nullptr;
        // Getting the target enemy
        try {
            target = this->getRoom()->getEnemies().at(0);
        } catch (std::out_of_range const &e) {
            std::cout << "There is no enemies here. " << std::endl;
            return GameStatus::CONTINUE;
        }

        // Killing the first enemy
        int current_health = this->getPlayer()->getCurrentHealth();
        KillStatus status = this->getRoom()->killEnemy(0, this->getPlayer());
        int new_health = this->getPlayer()->getCurrentHealth();

        // Status handler
        switch (status) {
            case KILL_FAILURE:
                std::cout << "You died while trying to kill " << *target
                          << "." << std::endl;
                return GameStatus::DEFEAT;
                break;
            case NO_ENEMY:
                // Probabbly won't happen
                std::cout << "There is no enemies here. " << std::endl;
                break;
            case DEAD_ENEMY:
                std::cout << "The " << *target
                          << " is already dead." << std::endl;
                break;
            case KILL_SUCCESS:
                std::cout << "You killed the " << *target
                          << ". It dealt " << (current_health - new_health)
                          << " damage to you. " << std::endl;
                std::cout << *(this->getPlayer());
                break;
        }
        return GameStatus::CONTINUE;
    }

    // Alternate kill
    if (cmd.substr(0, 5) == "kill ") {
        // Getting the target
        std::string target = cmd.substr(5, cmd.size());

        // Killing the target
        int current_health = this->getPlayer()->getCurrentHealth();
        KillStatus status = this->getRoom()->killEnemy(target, this->getPlayer());
        int new_health = this->getPlayer()->getCurrentHealth();

        // Status handler
        switch (status) {
            case KILL_FAILURE:
                std::cout << "You died while trying to kill " << target
                          << "." << std::endl;
                return GameStatus::DEFEAT;
                break;
            case NO_ENEMY:
                std::cout << "There is no " << target
                          << " in the room." << std::endl;
                break;
            case DEAD_ENEMY:
                std::cout << "The " << target
                          << " is already dead." << std::endl;
                break;
            case KILL_SUCCESS:
                std::cout << "You killed the " << target
                          << ". It dealt " << (current_health - new_health)
                          << " damage to you. " << std::endl;
                std::cout << *(this->getPlayer());
                break;
        }
        return GameStatus::CONTINUE;
    }

    // Get
    if (cmd.substr(0, 4) == "get ") {
        std::string item = cmd.substr(4, cmd.size());
        auto removed_item = this->getRoom()->removeItem(item);

        // If item not in the room
        if (removed_item == nullptr) {
            std::cout << "There is no item " << item << " in the room."
                      << std::endl;
            return GameStatus::CONTINUE;
        } else {
            // Adding item into inventory
            AddItemStatus status = this->getPlayer()->addItem(removed_item);

            // Handling the status
            switch (status) {
                case AddItemStatus::CANNOT_PICKUP:
                    std::cout << item << " cannot be picked up." << std::endl;
                    break;
                case AddItemStatus::INDEX_OUT_OF_RANGE:
                    // Probabbly won't happen
                    std::cout << "Tried to insert item out size of inventory"
                              << std::endl;
                    break;
                case AddItemStatus::INVALID_INDEX:
                    // Probabbly won't happen
                    std::cout << "Inventory slot already filled" << std::endl;
                    break;
                case AddItemStatus::NO_SPACE:
                    std::cout << "There is no space in your inventory left"
                              << std::endl;
                    break;
                case AddItemStatus::SUCCESS:
                    std::cout << "You added " << item << " to your inventory."
                              << std::endl;
                    return GameStatus::CONTINUE;
                    break;
                case AddItemStatus::INVALID_ITEM:
                    // Probabbly won't happen
                    std::cout << "The item cannot be added." << std::endl;
                    break;
            }
            this->getRoom()->addItem(removed_item);
            return GameStatus::CONTINUE;
        }
        return GameStatus::CONTINUE;
    }

    // Drop
    if (cmd.substr(0, 5) == "drop ") {
        std::string item = cmd.substr(5, cmd.size());
        auto dropped_item = this->getPlayer()->dropItem(item);

        // Handling dropped item
        if (dropped_item == nullptr) {
            std::cout << "Item " << item << " not in inventory." << std::endl;
        } else {
            this->getRoom()->addItem(dropped_item);
            std::cout << "You dropped " << item << " on the floor." << std::endl;
        }
        return GameStatus::CONTINUE;
    }

    // Inventory
    if (cmd == "inventory" || cmd == "i") {
        std::cout << *(this->getPlayer()->getInventory());
        return GameStatus::CONTINUE;
    }

    // Healing
    if (cmd == "eat food") {
        GenericItem *food = this->getPlayer()->getInventory()->getItem("Food");
        if (food == nullptr) {
            std::cout << "You don't have any food in your inventory." << std::endl;
        } else {
            this->getPlayer()->useItem(food);
            std::cout << "You ate some food." << std::endl;
            std::cout << *(this->getPlayer());
        }
        return GameStatus::CONTINUE;
    } else if (cmd == "drink elixir") {
        GenericItem *elixir = this->getPlayer()->getInventory()->getItem("Elixir");
        if (elixir == nullptr) {
            std::cout << "You don't have an elixir in your inventory." << std::endl;
        } else {
            this->getPlayer()->useItem(elixir);
            std::cout << "You drank the elixir." << std::endl;
            std::cout << *(this->getPlayer());
        }
        return GameStatus::CONTINUE;
    } else if (cmd == "use medpack") {
        GenericItem *medpack = this->getPlayer()->getInventory()->getItem("Medpack");
        if (medpack == nullptr) {
            std::cout << "You don't have a medpack in your inventory." << std::endl;
        } else {
            this->getPlayer()->useItem(medpack);
            std::cout << "You used the medpack." << std::endl;
            std::cout << *(this->getPlayer());
        }
        return GameStatus::CONTINUE;
    }

    // Unlocking door
    if (cmd == "unlock door") {
        bool unlocked = false;

        // If player doesn't have copper key
        if (this->getPlayer()->getInventory()->getItem("Copper Key")
            == nullptr) {
            std::cout << "You don't have any keys to unlock doors."
                      << std::endl;
            return GameStatus::CONTINUE;
        }

        // Looping over all rooms
        for (Direction direction: {Direction::NORTH, Direction::SOUTH,
            Direction::EAST, Direction::WEST}) {
            Room *room = this->getRoom()->getRoom(direction);

            // Continue if there is no room there.
            if (room == nullptr) {
                continue;
            }
            // Unlocking locked rooms
            if (room->isLocked()) {
                room->unlockRoom();
                std::cout << "You unlocked " << room->getName() << " with your "
                          << "copper key" << std::endl;
                unlocked = true;
            }
        }

        // If no rooms were unlocked
        if (!unlocked) {
            std::cout << "There is no room to be unlocked." << std::endl;
        }
        return GameStatus::CONTINUE;
    }

    return HKGE::processCommand();
}

/** Overriden endGame() to display XP.
 *
 * @param status The status of the game.
 * */
void AdventureGame::endGame(GameStatus status) {
    if (status == GameStatus::DEFEAT) {
        // If lossed
        std::cout << "You Lost" << std::endl;
    } else if (status == GameStatus::EXIT) {
        // If exited
        std::cout << "Exitting..." << std::endl;
    } else if (status == GameStatus::VICTORY){
        // If won
        std::cout << "You Win" << std::endl;
    }
    // Printing score and thank you
    std::cout << "Score: " << this->getPlayer()->getXP() << std::endl;
    std::cout << "Thank You for playing Adventure Game!!" << std::endl;
}

/** Overriden getCommand() to keep track of previous command.
 *
 * @return Always 1 indicating success.
 * */
int AdventureGame::getCommand(void) {
    HKGE::getCommand();
    if (this->getCurrentCommand() == "") {
        this->setCurrentCommand(this->previous_command);
    } else {
        this->previous_command = this->getCurrentCommand();
    }
    return 1;
}
