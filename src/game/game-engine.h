#ifndef GAME_ENGINE_H_
#define GAME_ENGINE_H_

#include <map>
#include <string>
#include <memory>
#include <list>

#include "player.h"
#include "room.h"

/** Status of the game. */
enum GameStatus {
VICTORY, /**<The user won the game. */
DEFEAT, /**<The user lost the game. */
EXIT, /**<The user exited the game. */
CONTINUE /**<Continue the game. */
};

/** Hong Kai Game Engine used to make adventure games. */
class HKGE {
        public:
                /** Deafult constructor for HKGE. */
                HKGE(void);
                /** Starts the adventure game.
                 *
                 * @return The exit status of the game.
                 */
                int start(void);

                //////////
                // Setters
                /** Adds a new command the game can handle.
                 *
                 * @param name The command name.
                 * @param description The description of what the command does.
                 */
                void addCommand(std::string name, std::string description);
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
                void addCommands(std::initializer_list<std::map<std::string,
                                 std::string>::value_type> list);
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
                void addMultipleCommands(std::initializer_list<std::string> commands,
                                 std::string description);
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
                void addMultipleCommands(std::list<std::string> commands,
                                         std::string description);
                /** Sets the Player class of the game.
                 *
                 * @param player The Player class.
                 * */
                void setPlayer(Player *player);
                /** Sets the player is in Room.
                 *
                 * @param room The sets Room the player is in.
                 * */
                void setRoom(Room *room);

                //////////
                // Getters
                /** Gets the Player class of the game.
                 *
                 * @return The Player class.
                 * */
                Player* getPlayer(void);
                /** Gets the Room the player is in.
                 *
                 * @return The current Room the player is in.
                 * */
                Room* getRoom(void);
                /** Gets the current command the game is storing.
                 *
                 * @return The current command.
                 * */
                std::string getCurrentCommand(void);
        protected:
                /** Gets the command from standard input.
                 *
                 * @return Always 1 indicating success.
                 *  */
                virtual int getCommand(void);
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
                virtual GameStatus processCommand(void);
                /** Called when the game ended.
                 *
                 * @param status The status of the game.
                 *
                 * @see GameStatus
                 * */
                virtual void endGame(GameStatus status);
                /** Sets the current command of the game.
                 *
                 * @param command The command to set to.
                 * */
                void setCurrentCommand(std::string command);
        private:
                std::string m_command = ""; /**<The current command to the game. */
                /** A list of avaiable command. */
                std::map<std::string, std::string> m_commands = {
                {"help", "Shows the available commands"},
                {"exit", "Exits the game"}};
                Room *m_current_room = nullptr; /**<Current room the player is in. */
                std::shared_ptr<Player> m_player = nullptr; /**<The player being controlled. */
};


#endif // GAME_ENGINE_H_
