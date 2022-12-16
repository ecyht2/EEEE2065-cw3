#include "generics.h"

#include <string>
#include <iostream>
#include <algorithm>

////////////////
// GenericEntity
/** Constructor function for GenericEntity.
 *
 * @param max_health The maximum health of the entity.
 * @param damage The damage the entity deals.
 * */
GenericEntity::GenericEntity(int max_health, int damage):
    m_max_health(max_health), m_damage(damage), m_current_health(max_health) {

}

//////////
// Setters
/** Deal damage to the entity.
 *
 * @param damage The damage to deal to the entity.
 * @param inventory The inventory of the damaging entity.
 * @return The amount of damage dealt.
 * */
int GenericEntity::takeDamage(int damage, Inventory *inventory) {
    this->m_current_health -= damage;

    // Calling onDeath() callback
    if (this->isDead()) {
        this->onDeath();
    }

    return damage;
}

/** Sets the damage the entity deals.
 *
 * @param damage The damage the entity deals.
 * */
void GenericEntity::setDamage(int damage) {
    this->m_damage = damage;
}

/** Heals the entity.
 *
 * @param health The amount of health to heal.
 * */
void GenericEntity::healEntity(int health) {
    this->m_current_health += health;

    if (this->getCurrentHealth() > this->m_max_health) {
        this->m_current_health = this->m_max_health;
    }
}

/** Gets the damage the entity currently deals.
 *
 * @return The damage the entity deals.
 * */
int GenericEntity::getDamage(void) const {
    return this->m_damage;
}

//////////
// Getters
/** Gets the current health of the entity.
 *
 * @return The current health of the entity.
 * */
int GenericEntity::getCurrentHealth(void) const {
    return m_current_health;
}

/** Gets the max health of the entity.
 *
 * @return The max health of the entity.
 * */
int GenericEntity::getMaxHealth(void) const {
    return this->m_max_health;
}

/** Gets the alive status of the entity.
 *
 * @return The status of the entity. true if
 * it is alive, false if it is dead.
 * */
bool GenericEntity::isDead(void) const {
    if (m_current_health <= 0) {
        return true;
    } else {
        return false;
    }
}

/////////
// Others
/** Deal damage to another entity.
 *
 * @param other The other entity to deal damage to.
 * @return The amount of damage dealt.
 * */
int GenericEntity::dealDamage(GenericEntity *other) {
    return other->takeDamage(this->m_damage, nullptr);
}

////////////////////
// Callbacks "slots"
void GenericEntity::onDeath(void) {

}

////////////////
// GenericItem
/** Constructor for GenericItem.
 *
 * @param name The name of the item.
 * */
GenericItem::GenericItem(std::string name): m_name(name) {

}

//////////
// Getters
/** Gets the name of the item.
 *
 * @return The name of the item.
 * */
std::string GenericItem::getName(void) const {
    return this->m_name;
}

/** Checks if the item can be picked up.
 *
 * @return If the item is pickupable or not.
 * */
bool GenericItem::canPickup(void) {
    return this->m_canPickup;
}

//////////
// Setters
/** Make the item unable to pickup. */
void GenericItem::disallowPickup(void) {
    this->m_canPickup = false;
}

/** Make the item able to pickup. */
void GenericItem::allowPickup(void) {
    this->m_canPickup = true;
}

/** Toggles the item ablity to be pickuped. */
void GenericItem::togglePickup(void) {
    this->m_canPickup = !this->m_canPickup;
}

////////////
// Operators
/** Checks if the items are the same.
 *
 * @param other The other item to compare to.
 *
 * @note This operation copares the name of the items and it is not case
 * sensitive.
 * */
bool GenericItem::operator == (GenericItem other) const {
    return *this == other.getName();
}

/** Checks if the items are the same.
 *
 * @overload
 *
 * @param other The other item to compare to.
 *
 * @note This operation copares the name of the items and it is not case
 * sensitive.
 * */
bool GenericItem::operator == (std::string other) const {
    std::string this_lower = this->getName();
    std::string other_lower = other;

    std::transform(this_lower.begin(), this_lower.end(),
                   this_lower.begin(), ::tolower);
    std::transform(other.begin(), other.end(),
                   other_lower.begin(), ::tolower);

    if (this_lower == other_lower) {
        return true;
    } else {
        return false;
    }
}

/** Overloaded operator to print the item.
*
* @param out The output stream.
* @param cls The class iteself.
*
* @return The new output stream.
* */
std::ostream& operator << (std::ostream &out, const GenericItem &cls) {
    out << cls.getName();
    return out;
}

////////////////////
// Callbacks "slots"
/** Callback function to call when the item is picked up.
 *
 * @param entity The entity that picked up the item.
 * */
void GenericItem::onPickup(Player &entity) {

}

/** Callback function to call when the item is dropped.
 *
 * @param entity The entity that dropped the item.
 * */
void GenericItem::onDropped(Player &entity) {

}

/** Callback function to call when the item is used.
 *
 * @param entity The entity that used the item.
 * */
void GenericItem::onUsed(Player &entity) {

}
