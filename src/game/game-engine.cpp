#include "game-engine.h"

#include <iostream>
#include <exception>
#include <algorithm>
#include <memory>

/** Deafult constructor for HKGE. */
HKGE::HKGE(void) {
}

/** Starts the adventure game.
 *
 * @return The exit status of the game.
 */
int HKGE::start(void) {
    while (this->getCommand() > 0) {
        GameStatus status = this->processCommand();
        if (status != GameStatus::CONTINUE) {
            this->endGame(status);
            break;
        }
    }
    return 0;
}

//////////
// Setters
/** Adds a new command the game can handle.
 *
 * @param name The command name.
 * @param description The description of what the command does.
 */
void HKGE::addCommand(std::string name, std::string description) {
    this->m_commands.emplace(name, description);
}

/** Adds new commands the game can handle.
 *
 * The method adds elements using an initializer list.
 *
 * @code
 * this->addCommands({{"foo", "bar"}, {"bar", "foo"}})
 * @endcode
 *
 * Will add command foo with description bar and command bar
 * with the description foo.
 *
 * @param list The initializer list to insert.
 */
void HKGE::addCommands(std::initializer_list<std::map<std::string,
                       std::string>::value_type> list) {
    this->m_commands.insert(list);
}

 /** Adds new commands with the same description.
  *
  * @code
  * this->addMultipleCommands({"foo", "f"}, "bar");
  * @endcode
  *
  * Will add commands foo and f with description bar.
  *
  * @param commands The list of commands to add.
  * @param description The description of the commands.
  */
 void HKGE::addMultipleCommands(std::initializer_list<std::string> commands,
                                std::string description) {
     for (std::string command: commands) {
         this->addCommand(command, description);
     }
 }

 /** Adds new commands with the same description.
  *
  * @overload
  *
  * @code
  * std::list<std::string> list = {"foo", "f"};
  * this->addMultipleCommands(list, "bar");
  * @endcode
  *
  * Will add commands foo and f with description bar.
  *
  * @param commands The list of commands to add.
  * @param description The description of the commands.
  */
void HKGE::addMultipleCommands(std::list<std::string> commands,
                               std::string description) {
    for (std::string command: commands) {
        this->addCommand(command, description);
    }
}

/** Sets the Player class of the game.
 *
 * @param player The Player class.
 * */
void HKGE::setPlayer(Player *player) {
    this->m_player = std::shared_ptr<Player>(player);
}

/** Sets the player is in Room.
 *
 * @param room The sets Room the player is in.
 * */
void HKGE::setRoom(Room *room) {
    this->m_current_room = room;
}

//////////
// Getters
/** Gets the Player class of the game.
 *
 * @return The Player class.
 * */
Player* HKGE::getPlayer(void) {
    return this->m_player.get();
}

/** Gets the Room the player is in.
 *
 * @return The current Room the player is in.
 * */
Room* HKGE::getRoom(void) {
    return this->m_current_room;
}

/** Gets the current command the game is storing.
 *
 * @return The current command.
 * */
std::string HKGE::getCurrentCommand(void) {
    return this->m_command;
}

////////////
// protected
/** Gets the command from standard input.
 *
 * @return Always 1 indicating success.
 *  */
int HKGE::getCommand(void) {
    std::cout << "Enter Command (help for help): ";
    std::getline(std::cin, this->m_command);
    std::transform(this->m_command.begin(), this->m_command.end(),
                   this->m_command.begin(), ::tolower);
    return 1;
}

/** Process the inputted command.
 *
 * Some defaults commands are handled by this function.
 * help: Prints the help message.
 * exit: Exits the game.
 *
 * It also handles if the command is valid or not.
 *
 * @return The status of the game
 *
 * @see GameStatus
 * */
GameStatus HKGE::processCommand(void) {
    // Handling Help Command
    if (this->m_command == "help") {
        for (auto command: this->m_commands) {
            std::cout << command.first << ": " << command.second << std::endl;
        }
        return GameStatus::CONTINUE;
    } else if (this->m_command == "exit") { // Exit
        return GameStatus::EXIT;
    }

    // Handling Invalid Command
    std::cout << "Invalid Command." << std::endl;
    return GameStatus::CONTINUE;
}

/** Called when the game ended.
 *
 * @param status The status of the game.
 *
 * @see GameStatus
 * */
void HKGE::endGame(GameStatus status) {
    exit(0);
}

/** Sets the current command of the game.
 *
 * @param command The command to set to.
 * */
void HKGE::setCurrentCommand(std::string command) {
    this->m_command = command;
}
