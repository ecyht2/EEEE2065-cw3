#ifndef GENERICCLASSES_H_
#define GENERICCLASSES_H_

/** @file generics.h
 *
 * Header file containin generic classes for an
 * entity (GenericEntity) and an item (GenericItem).
 * */

#include <string>

class Inventory;
class Player;

/** A generic entity class in the adventure game.
 *
 * This is used by Player and GenericEnemy class and it's
 * respective subclasses as a base.
 * */
class GenericEntity {
        public:
                /** Constructor function for GenericEntity.
                 *
                 * @param max_health The maximum health of the entity.
                 * @param damage The damage the entity deals.
                 * */
                GenericEntity(int max_health, int damage);

                //////////
                // Setters
                /** Deal damage to the entity.
                 *
                 * @param damage The damage to deal to the entity.
                 * @param inventory The inventory of the damaging entity.
                 * @return The amount of damage dealt.
                 * */
                virtual int takeDamage(int damage, Inventory *inventory);
                /** Sets the damage the entity deals.
                 *
                 * @param damage The damage the entity deals.
                 * */
                void setDamage(int damage);
                /** Heals the entity.
                 *
                 * @param health The amount of health to heal.
                 * */
                void healEntity(int health);

                //////////
                // Getters
                /** Gets the current health of the entity.
                 *
                 * @return The current health of the entity.
                 * */
                int getCurrentHealth(void) const;
                /** Gets the max health of the entity.
                 *
                 * @return The max health of the entity.
                 * */
                int getMaxHealth(void) const;
                /** Gets the damage the entity currently deals.
                 *
                 * @return The damage the entity deals.
                 * */
                int getDamage(void) const;
                /** Gets the alive status of the entity.
                 *
                 * @return The status of the entity. true if
                 * it is alive, false if it is dead.
                 * */
                bool isDead(void) const;

                /////////
                // Others
                /** Deal damage to another entity.
                 *
                 * @param other The other entity to deal damage to.
                 * @return The amount of damage dealt.
                 * */
                virtual int dealDamage(GenericEntity *other);

                ////////////////////
                // Callbacks "slots"
                /** Callback function to call when the entity died. */
                virtual void onDeath(void);
        private:
                int m_max_health = 20; /**<The maximum health of the entity. */
                int m_damage = 1; /**<The damage the entity deals. */
                int m_current_health = m_max_health; /**<The entity's current health. */
};

/** A generic item class in the adventure game.
 *
 * This is used by the various item subclasses as a base.
 * */
class GenericItem {
        public:
                /** Constructor for GenericItem.
                 *
                 * @param name The name of the item.
                 * */
                GenericItem(std::string name = "");

                //////////
                // Getters
                /** Gets the name of the item.
                 *
                 * @return The name of the item.
                 * */
                std::string getName(void) const;
                /** Checks if the item can be picked up.
                 *
                 * @return If the item is pickupable or not.
                 * */
                bool canPickup(void);

                //////////
                // Setters
                /** Make the item unable to pickup. */
                void disallowPickup(void);
                /** Make the item able to pickup. */
                void allowPickup(void);
                /** Toggles the item ablity to be pickuped. */
                void togglePickup(void);

                ////////////
                // Operators
                /** Checks if the items are the same.
                 *
                 * @param other The other item to compare to.
                 *
                 * @note This operation copares the name of the items and it is
                 * not case sensitive.
                 * */
                virtual bool operator == (GenericItem other) const;
                /** Checks if the items are the same.
                 *
                 * @overload
                 *
                 * @param other The other item to compare to.
                 *
                 * @note This operation copares the name of the items and it is
                 * not case sensitive.
                 * */
                virtual bool operator == (std::string other) const;
                /** Overloaded operator to print the item.
                 *
                 * @param out The output stream.
                 * @param cls The class iteself.
                 *
                 * @return The new output stream.
                 * */
                friend std::ostream& operator << (std::ostream &out, const GenericItem &cls);

                ////////////////////
                // Callbacks "slots"
                /** Callback function to call when the item is picked up.
                 *
                 * @param entity The entity that picked up the item.
                 * */
                virtual void onPickup(Player &entity);
                /** Callback function to call when the item is dropped.
                 *
                 * @param entity The entity that dropped the item.
                 * */
                virtual void onDropped(Player &entity);
                /** Callback function to call when the item is used.
                 *
                 * @param entity The entity that used the item.
                 * */
                virtual void onUsed(Player &entity);
        private:
                std::string m_name = ""; /**<Name of the item. */
                /** Marks if the item can be picked up or not. */
                bool m_canPickup = true;
};

#endif // GENERICCLASSES_H_
