#ifndef GAME_H_
#define GAME_H_

#include <string>

#include "game-engine.h"
#include "room.h"

/** The game that is specified by the coursework. */
class AdventureGame: public HKGE {
    public:
        /** Constructor class for coursework game. */
        AdventureGame(void);
        /** Destuctor function to delete dynamically allocated room. */
        ~AdventureGame(void);
    protected:
        /** Overriden to add new commands.
         *
         * @return The game status.
         * */
        virtual GameStatus processCommand(void) override;
        /** Overriden endGame() to display XP.
         *
         * @param status The status of the game.
         * */
        virtual void endGame(GameStatus status) override;
        /** Overriden getCommand() to keep track of previous command.
         *
         * @return Always 1 indicating success.
         * */
        virtual int getCommand(void) override;
    private:
        Room *m_initial_room = nullptr; /**<The initial room the player spawns in. */
        Room *rooms[9] = {}; /**<All the rooms of the game. */
        std::string previous_command = ""; /**<Previous typed command. */
};

#endif // GAME_H_
