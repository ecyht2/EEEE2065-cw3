#include "items.h"

#include <string>

#include "player.h"

/////////
// Weapon
/** Constructor class for a Weapon item.
 *
 * @param name The name of the weapon.
 * @param damage The damage increase of the item.
 * */
Weapon::Weapon(std::string name, int damage): GenericItem(name), m_damage(damage) {

}

/** Overriden pickup behavior from GenericItem.
 *
 * This is used to add the damage to the entity.
 *
 * @param entity The entity that pickedup the weapon.
 * */
void Weapon::onPickup(Player &entity) {
    int damage = entity.getDamage() + this->m_damage;
    entity.setDamage(damage);
}

/** Overriden drop behavior from GenericItem.
 *
 * This is used to rduce the damage to the entity.
 *
 * @param entity The entity that dropped the weapon.
 * */
void Weapon::onDropped(Player &entity) {
    int damage = entity.getDamage() - this->m_damage;
    entity.setDamage(damage);
}

/////////////
// Consumable
/** Constructor class for a Consumable item.
 *
 * @param name The name of the consumable.
 * @param healing The health healed by the item when
 * used.
 * */
Consumable::Consumable(std::string name, int healing):
    GenericItem(name), m_healing(healing) {

}

/** Overriden use behavior from GenericItem.
 *
 * This is use to heal the entity.
 *
 * @param entity The entity that dropped the weapon.
 * */
void Consumable::onUsed(Player &entity) {
    entity.healEntity(this->m_healing);
    entity.dropItem(this);
}
