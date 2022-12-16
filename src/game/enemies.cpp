#include "enemies.h"

#include <algorithm>
#include <memory>

#include "generics.h"

///////////////
// GenericEnemy
/** Constructor for the GenericEnemy class.
 *
 * @param health The health of the monster.
 * @param damage The damage of the monster.
 * @param name The name of the enemy.
 * @param item The item the monster is protecting.
 * */
GenericEnemy::GenericEnemy(int health, int damage, std::string name,
                           std::shared_ptr<GenericItem> item): GenericEntity(health, damage),
                                                               m_prot_item(item),
                                                               m_name(name) {
    if (item != nullptr) {
        this->m_prot_item->disallowPickup();
    }
}

//////////
// Getters
std::string GenericEnemy::getName(void) const {
    return this->m_name;
}

////////////////////
// Callbacks "slots"
/** Callback function to call when the entity died.
 *
 * Overriden to allow the protected item to be pickedup.
 * */
void GenericEnemy::onDeath(void) {
    if (this->m_prot_item != nullptr) {
        this->m_prot_item->allowPickup();
    }
}

////////////
// Operators
/** Overloaded operator to print the item.
 *
 * @param out The output stream.
 * @param cls The class iteself.
 *
 * @return The new output stream.
 * */
std::ostream& operator << (std::ostream &out, const GenericEnemy &cls) {
    out << cls.m_name;
    return out;
}

/** Checks if the enemies are the same.
 *
 * @param other The other enemy to compare to.
 * @return If the name of the enemy are the same.
 *
 * @note This operator compares the name of the enemy and it is not case
 * sensitive.
 * */
bool GenericEnemy::operator == (GenericEnemy other) const {
    return *this == other.getName();
}

/** Checks if the enemies are the same.
 *
 * @overload
 *
 * @param other The other enemy to compare to.
 * @return If the name of enemy is the same as other.
 *
 * @note This operator compares the name of the enemy and it is not case
 * sensitive.
 * */
bool GenericEnemy::operator == (std::string other) const {
    // Converting to lower case
    std::string this_lower = this->getName();
    std::string other_lower = other;

    std::transform(this_lower.begin(), this_lower.end(),
                   this_lower.begin(), ::tolower);
    std::transform(other.begin(), other.end(),
                   other_lower.begin(), ::tolower);

    // Doing check
    if (this_lower == other_lower) {
        return true;
    } else {
        return false;
    }
}

///////////
// Werewolf
/** Constructor for the Werewolf class.
 *
 * @param health The health of the monster.
 * @param damage The damage of the monster.
 * @param name The name of the enemy.
 * @param item The item the monster is protecting.
 * */
Werewolf::Werewolf(int health, int damage, std::string name,
                   std::shared_ptr<GenericItem> item):
    GenericEnemy(health, damage, name, item) {

}

/** Deal damage to the entity.
 *
 * Overriden to take damage according to the monster.
 *
 * @param damage The damage to deal to the entity.
 * @param inventory The inventory of the damaging entity.
 * */
int Werewolf::takeDamage(int damage, Inventory *inventory) {
    // Checking for silver spears
    for (unsigned int i = 0; i < inventory->maxSize(); i++) {
        GenericItem *item = inventory->getItem(i);
        // If there is nothing there
        if (item == nullptr) {
            continue;
        }
        // Adding damage if it is a silver spear
        if ((std::string) "Silver Spear" == item->getName()) {
            damage += 3;
        }
    }

    return GenericEnemy::takeDamage(damage, inventory);
}

//////////
// Vampire
/** Constructor for the Vampire class.
 *
 * @param health The health of the monster.
 * @param damage The damage of the monster.
 * @param name The name of the enemy.
 * @param item The item the monster is protecting.
 * */
Vampire::Vampire(int health, int damage, std::string name,
                 std::shared_ptr<GenericItem> item):
    GenericEnemy(health, damage, name, item) {

}

/** Deal damage to the entity.
 *
 * Overriden to take damage according to the monster.
 *
 * @param damage The damage to deal to the entity.
 * @param inventory The inventory of the damaging entity.
 * */
int Vampire::takeDamage(int damage, Inventory *inventory) {
    // Reducing damage from swords and checking for diamond cross
    for (unsigned int i = 0; i < inventory->maxSize(); i++) {
        GenericItem *item = inventory->getItem(i);
        // If there is nothing there
        if (item == nullptr) {
            continue;
        }
        // Reducing damage from sword
        if (item->getName() == "Sword") {
            damage -= 1;
        } else if ((std::string) "Diamond Cross" == item->getName()) {
            // Adding damage if there is a diamond cross
            damage += 4;
        }
    }

    return GenericEnemy::takeDamage(damage, inventory);
}
