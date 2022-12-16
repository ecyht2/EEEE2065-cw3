#ifndef PLAYER_H_
#define PLAYER_H_

#include <string>
#include <ostream>
#include <memory>

#include "generics.h"
#include "inventory.h"

/** Class representing the player. */
class Player: public GenericEntity {
        public:
                /** Constructor for Player class.
                 *
                 * @param health The max health of the player.
                 * @param damage The base damage of the player.
                 * @param inventory_size The inventory size of the player.
                 * */
                Player(int health = 12, int damage = 1, int inventory_size = 3);

                //////////
                // Getters
                /** Gets the inventory of the player.
                 *
                 * @return The inventory of the player.
                 * */
                Inventory* getInventory(void) const;
                /** Gets the current XP of the player.
                 *
                 * @return The XP of the player.
                 */
                int getXP(void) const;

                //////////
                // Setters
                /** Adds an item in the inventory.
                 *
                 * @param item The item to add to the inventory.
                 * @return The status of adding the item.
                 * @see AddItemStatus
                 * */
                AddItemStatus addItem(std::shared_ptr<GenericItem> item);
                /** Drops an item from the player's inventory.
                 *
                 * @param item The item to remove.
                 * @return Pointer to the removed item.
                 * */
                std::shared_ptr<GenericItem> dropItem(GenericItem *item);
                /** Removes an item in the inventory.
                 *
                 * @overload
                 * This method takes in the name of the item instead
                 * of the item itself.
                 *
                 * @param item The item name to remove.
                 * @return Pointer to the removed item.
                 * */
                std::shared_ptr<GenericItem> dropItem(std::string item);
                /** Removes an item in the inventory.
                 *
                 * @overload
                 * This method takes in the index of the item
                 * on the list instead.
                 *
                 * @param index The index of the item to remove.
                 * @return Pointer to the removed item.
                 * */
                std::shared_ptr<GenericItem> dropItem(int index);

                /////////
                // Others
                /** Overridden dealDamage() to gain xp on damage.
                 *
                 * @param other The entity to deal damage to.
                 * */
                virtual int dealDamage(GenericEntity *other) override;
                /** Use the item in the inventory.
                 *
                 * @param item The item to use.
                 * @return true if successfully used false if failure
                 * due to the item doesn't exist in inventory.
                 * */
                virtual bool useItem(GenericItem *item);
                /** Overloaded operator to print the player information.
                 *
                 * @param out The output stream.
                 * @param cls The class iteself.
                 *
                 * @return The new output stream.
                 * */
                friend std::ostream& operator << (std::ostream &out,
                                                  const Player &cls);
        private:
                int m_xp = 0; /**<The amount of xp the player current have. */
                std::shared_ptr<Inventory> inventory = nullptr; /**<The player's inventory. */
};

#endif // PLAYER_H_
