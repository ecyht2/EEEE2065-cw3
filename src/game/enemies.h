#ifndef MONSTERS_H_
#define MONSTERS_H_

#include <string>
#include <memory>

#include "generics.h"
#include "player.h"

/** A class representing an enemy the player have to fight. */
class GenericEnemy: public GenericEntity {
        public:
                /** Constructor for the GenericEnemy class.
                 *
                 * @param health The health of the monster.
                 * @param damage The damage of the monster.
                 * @param name The name of the enemy.
                 * @param item The item the monster is protecting.
                 * */
                GenericEnemy(int health = 5, int damage = 1, std::string name = "",
                             std::shared_ptr<GenericItem> item = nullptr);

                //////////
                // Getters
                /** Gets the name of the enemy.
                 *
                 * @return The name of the enemy.
                 * */
                std::string getName(void) const;

                ////////////////////
                // Callbacks "slots"
                /** Callback function to call when the entity died.
                 *
                 * Overriden to allow the protected item to be pickedup.
                 * */
                virtual void onDeath(void) override;

                ////////////
                // Operators
                /** Overloaded operator to print the item.
                 *
                 * @param out The output stream.
                 * @param cls The class iteself.
                 *
                 * @return The new output stream.
                 * */
                friend std::ostream& operator << (std::ostream &out,
                                                  const GenericEnemy &cls);
                /** Checks if the enemies are the same.
                 *
                 * @param other The other enemy to compare to.
                 * @return If the name of the enemy are the same.
                 *
                 * @note This operator compares the name of the enemy and
                 * it is not case sensitive.
                 * */
                virtual bool operator == (GenericEnemy other) const;
                /** Checks if the enemies are the same.
                 *
                 * @overload
                 *
                 * @param other The other enemy to compare to.
                 * @return If the name of enemy is the same as other.
                 *
                 * @note This operator compares the name of the enemy and
                 * it is not case sensitive.
                 * */
                virtual bool operator == (std::string other) const;
        private:
                /**The item the monster is protecting. */
                std::shared_ptr<GenericItem> m_prot_item = nullptr;
                std::string m_name = ""; /**<The name of the enemy. */
};

/** Class representing a werewolf enemy.
 *
 * Werewolfs takes more damage if there is a silver spear
 * in the attacker's inventory.
 * */
class Werewolf: public GenericEnemy {
        public:
                /** Constructor for the Werewolf class.
                 *
                 * @param health The health of the monster.
                 * @param damage The damage of the monster.
                 * @param name The name of the enemy.
                 * @param item The item the monster is protecting.
                 * */
                Werewolf(int health = 12, int damage = 2, std::string name = "",
                         std::shared_ptr<GenericItem> item = nullptr);
                /** Deal damage to the entity.
                 *
                 * Overriden to take damage according to the monster.
                 *
                 * @param damage The damage to deal to the entity.
                 * @param inventory The inventory of the damaging entity.
                 * */
                virtual int takeDamage(int damage, Inventory *inventory) override;
};

/** Class representing a vampire enemy.
 *
 * Vampires takes more damage if there is a diamon cross
 * in the attacker's inventory. The vampire also takes
 * less damage from a sword.
 * */
class Vampire: public GenericEnemy {
    public:
        /** Constructor for the Vampire class.
         *
         * @param health The health of the monster.
         * @param damage The damage of the monster.
         * @param name The name of the enemy.
         * @param item The item the monster is protecting.
         * */
        Vampire(int health = 12, int damage = 3, std::string name = "",
                std::shared_ptr<GenericItem> item = nullptr);
        /** Deal damage to the entity.
         *
         * Overriden to take damage according to the monster.
         *
         * @param damage The damage to deal to the entity.
         * @param inventory The inventory of the damaging entity.
         * */
        virtual int takeDamage(int damage, Inventory *inventory) override;
};

#endif // MONSTERS_H_
