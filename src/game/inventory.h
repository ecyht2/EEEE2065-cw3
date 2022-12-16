#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <string>
#include <memory>

#include "generics.h"

enum AddItemStatus {
NO_SPACE, /**<There is no space in the inventory. */
INDEX_OUT_OF_RANGE, /**<The slot index is too big for the inventory. */
INVALID_INDEX, /**<The inventory slot already has an item. */
CANNOT_PICKUP, /**<The item can't be pickedup. */
INVALID_ITEM, /**<If the item is invalid (nullptr is given). */
SUCCESS /**<Succesfully added the item. */
};

/** Class representing the inventory of the player. */
class Inventory {
        public:
                /** Constructor for Inventory class.
                 *
                 * @param size The size of the inventory.
                 * */
                Inventory(unsigned int size = 3);
                /** Destructor of Inventory.
                 *
                 * Used to deallocate the inventory list array.
                 * */
                ~Inventory(void);

                //////////
                // Setters
                /** Adds an item in the inventory.
                 *
                 * @param item The item to add to the inventory.
                 * @param index The inventory slot to add to (value < 0 to add item to
                 * the nearest avaiable space).
                 * @return The status of adding the item.
                 * @see AddItemStatus
                 * */
                AddItemStatus addItem(std::shared_ptr<GenericItem> item, int index = -1);
                /** Removes an item in the inventory.
                 *
                 * @param item The item to remove.
                 * @return Pointer to the removed item (nullptr is returned
                 * if the item is not in inventory).
                 * */
                std::shared_ptr<GenericItem> removeItem(GenericItem *item);
                /** Removes an item in the inventory.
                 *
                 * @overload
                 * This method takes in the name of the item instead
                 * of the item itself. This function will remove the first
                 * item found in the inventory.
                 *
                 * @param item The item name to remove.
                 * @return Pointer to the removed item (nullptr is returned
                 * if the item is not in inventory).
                 * */
                std::shared_ptr<GenericItem> removeItem(std::string item);
                /** Removes an item in the inventory.
                 *
                 * @overload
                 * This method takes in the index of the item
                 * on the list instead.
                 *
                 * @param index The index of the item to remove.
                 * @return Pointer to the removed item (nullptr is returned
                 * if the index is not valid ie index too big or item slot is
                 * empty).
                 * */
                std::shared_ptr<GenericItem> removeItem(unsigned int index);

                //////////
                // Getters
                /** Gets the item in the inventory.
                 *
                 * @param item The item name to get.
                 * @return The item in the inventory (nullptr would be returned
                 * if the item isn't in the inventory).
                 * */
                GenericItem* getItem(std::string item) const;
                /** Gets the item in the inventory.
                 *
                 * @overload
                 * Takes in the index of the item in the inventory
                 * instead.
                 *
                 * @param index The index of the item to get.
                 * @return The item in the inventory (nullptr would be returned
                 * if the item isn't in the inventory).
                 * */
                GenericItem* getItem(unsigned int index) const;
                /** Gets the list of items in the inventory. */
                std::shared_ptr<GenericItem>* getItems() const;
                /** Gets the max size of the inventory.
                 *
                 * @return Max size of the inventory.
                 * */
                unsigned int maxSize(void) const;
                /** Gets the amount of free spaces available in the inventory.
                 *
                 * @return The amount of free spaces left.
                 */
                 int getAvaiableSpaces(void) const;

                ////////////
                // Operators
                /** Overloaded operator to print the inventory.
                 *
                 * @param out The output stream.
                 * @param cls The class iteself.
                 *
                 * @return The new output stream.
                 * */
                friend std::ostream& operator << (std::ostream &out, const Inventory &cls);
        private:
                unsigned int m_max_size = 3; /**<The maximum amount of items the inventory
                                              * can store. */
                /** The list of items current stored in the inventory. */
                std::shared_ptr<GenericItem> *inventory_list;
};

#endif // INVENTORY_H_
