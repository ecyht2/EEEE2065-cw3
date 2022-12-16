#ifndef ITEMS_H_
#define ITEMS_H_

#include <string>

#include "generics.h"
#include "player.h"

/** A class representing a weapon. */
class Weapon: public GenericItem {
    public:
        /** Constructor class for a Weapon item.
         *
         * @param name The name of the weapon.
         * @param damage The damage increase of the item.
         * */
        Weapon(std::string name = "", int damage = 3);
        /** Overriden pickup behavior from GenericItem.
         *
         * This is used to add the damage to the entity.
         *
         * @param entity The entity that pickedup the weapon.
         * */
        virtual void onPickup(Player &entity) override;
        /** Overriden drop behavior from GenericItem.
         *
         * This is used to rduce the damage to the entity.
         *
         * @param entity The entity that dropped the weapon.
         * */
        virtual void onDropped(Player &entity) override;
    private:
        int m_damage = 3;
};

/** A class representing a consumable item. */
class Consumable: public GenericItem {
    public:
        /** Constructor class for a Consumable item.
         *
         * @param name The name of the consumable.
         * @param healing The health healed by the item when
         * used.
         * */
        Consumable(std::string name = "", int healing = 5);
        /** Overriden use behavior from GenericItem.
         *
         * This is use to heal the entity.
         *
         * @param entity The entity that dropped the weapon.
         * */
        virtual void onUsed(Player &entity) override;
    private:
        int m_healing = 5;
};

#endif // ITEMS_H_
