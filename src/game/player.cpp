#include "player.h"

#include <memory>
#include <string>

#include "generics.h"
#include "inventory.h"

//////////////////
// Player
/** Constructor for Player class.
 *
 * @param health The max health of the player.
 * @param damage The base damage of the player.
 * @param inventory_size The inventory size of the player.
 * */
Player::Player(int health, int damage, int inventory_size): GenericEntity(health, damage) {
    this->inventory = std::shared_ptr<Inventory>(new Inventory(inventory_size));
}

//////////
// Getters
/** Gets the inventory of the player.
 *
 * @return The inventory of the player.
 * */
Inventory* Player::getInventory(void) const {
    return this->inventory.get();
}

/** Gets the current XP of the player.
 *
 * @return The XP of the player.
 */
int Player::getXP(void) const {
    return this->m_xp;
}

//////////
// Setters
/** Adds an item in the inventory.
 *
 * @param item The item to add to the inventory.
 * @return The status of adding the item.
 * @see AddItemStatus
 * */
AddItemStatus Player::addItem(std::shared_ptr<GenericItem> item) {
    if (item != nullptr) {
        item->onPickup(*this);
    }
    return this->inventory->addItem(item);
};

/** Drops an item from the player's inventory.
 *
 * @param item The item to remove.
 * @return Pointer to the removed item.
 * */
std::shared_ptr<GenericItem> Player::dropItem(GenericItem *item) {
    if (item != nullptr) {
        item->onDropped(*this);
    }
    return this->inventory->removeItem(item);
}

/** Removes an item in the inventory.
 *
 * @overload
 * This method takes in the name of the item instead
 * of the item itself.
 *
 * @param item The item name to remove.
 * @return Pointer to the removed item.
 * */
std::shared_ptr<GenericItem> Player::dropItem(std::string item) {
    auto selected_item = this->inventory->removeItem(item);
    if (selected_item != nullptr) {
        selected_item->onDropped(*this);
    }
    return selected_item;
}

/** Removes an item in the inventory.
 *
 * @overload
 * This method takes in the index of the item
 * on the list instead.
 *
 * @param index The index of the item to remove.
 * @return Pointer to the removed item.
 * */
std::shared_ptr<GenericItem> Player::dropItem(int index) {
    auto selected_item = this->inventory->removeItem(index);
    if (selected_item != nullptr) {
        selected_item->onDropped(*this);
    }
    return selected_item;
}

/////////
// Others
/** Overridden dealDamage() to gain xp on damage.
 *
 * @param other The entity to deal damage to.
 * */
int Player::dealDamage(GenericEntity *other) {
    int damage = other->takeDamage(this->getDamage(), this->getInventory());
    this->m_xp += damage;
    return damage;
}

/** Use the item in the inventory.
 *
 * @param item The item to use.
 * @return true if successfully used false if failure
 * due to the item doesn't exist in inventory.
 * */
bool Player::useItem(GenericItem *item) {
    if (item == nullptr) {
        return false;
    } else {
        GenericItem *used_item = this->getInventory()->getItem(item->getName());
        used_item->onUsed(*this);
        return true;
    }
}

/** Overloaded operator to print the player information.
 *
 * @param out The output stream.
 * @param cls The class iteself.
 *
 * @return The new output stream.
 * */
std::ostream& operator << (std::ostream &out, const Player &cls) {
    out << "Player:" << std::endl;
    out << "HP: " << cls.getCurrentHealth()
        << "/" << cls.getMaxHealth() << std::endl;
    out << "Damage: " << cls.getDamage() << std::endl;
    out << "XP: " << cls.getXP() << std::endl;
    out << *cls.getInventory();
    return out;
}
