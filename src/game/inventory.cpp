#include "inventory.h"

#include <iostream>
#include <memory>
#include <algorithm>

#include "generics.h"

/////////////////////
// Inventory
/** Constructor for Inventory class.
 *
 * @param size The size of the inventory.
 * */
Inventory::Inventory(unsigned int size): m_max_size(size) {
    this->inventory_list = new std::shared_ptr<GenericItem>[this->m_max_size];
}

/** Destructor of Inventory.
 *
 * Used to deallocate the inventory list array.
 * */
Inventory::~Inventory(void) {
    delete [] inventory_list;
}

/** Adds an item in the inventory.
 *
 * @param item The item to add to the inventory.
 * @param index The inventory slot to add to (value < 0 to add item to
 * the nearest avaiable space).
 * @return The status of adding the item.
 * @see AddItemStatus
 * */
AddItemStatus Inventory::addItem(std::shared_ptr<GenericItem> item, int index) {
    if (item == nullptr) {
        return AddItemStatus::INVALID_ITEM;
    }

    if (this->getAvaiableSpaces() <= 0) {
        return AddItemStatus::NO_SPACE;
    } else if (!item->canPickup()) {
        return AddItemStatus::CANNOT_PICKUP;
    } else {
        if (index < 0) { // Adding to nearest avaiable slot
            for (unsigned int i = 0; i < this->maxSize(); i++) {
                if (this->inventory_list[i] == nullptr) {
                    this->inventory_list[i] = std::shared_ptr<GenericItem>(item);
                    break;
                }
            }
            return SUCCESS;
        } else { // Adding to specific index
            if (index > (int) (this->maxSize() - 1)) {
                // index too big
                return AddItemStatus::INDEX_OUT_OF_RANGE;
            } else if(this->inventory_list[index] != nullptr) {
                // Index already has an item
                return AddItemStatus::INVALID_INDEX;
            } else {
                // Adding item to index
                this->inventory_list[index] = std::shared_ptr<GenericItem>(item);
                return AddItemStatus::SUCCESS;
            }
        }
    }
}

/** Removes an item in the inventory.
 *
 * @param item The item to remove.
 * @return Pointer to the removed item (nullptr is returned
 * if the item is not in inventory).
 * */
std::shared_ptr<GenericItem> Inventory::removeItem(GenericItem *item) {
    std::shared_ptr<GenericItem> current_item = nullptr;
    // Looping over all items
    for (unsigned int i = 0; i < this->m_max_size; i++) {
        // Checking if they are the same
        if(this->inventory_list[i].get() == item) {
            current_item = this->inventory_list[i];
            this->inventory_list[i] = nullptr;
            return current_item;
        }
    }
    return current_item;
}

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
std::shared_ptr<GenericItem> Inventory::removeItem(std::string item) {
    std::shared_ptr<GenericItem> current_item = nullptr;
    // Looping over all items
    for (unsigned int i = 0; i < this->maxSize(); i++) {
        // Checking if it is a valid item
        if (this->inventory_list[i] == nullptr) {
            continue;
        }

        // Checking if it they are the same
        if(*(this->inventory_list[i]) == item) {
            current_item = this->inventory_list[i];
            this->inventory_list[i] = nullptr;
            return current_item;
        }
    }
    return current_item;
}

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
std::shared_ptr<GenericItem> Inventory::removeItem(unsigned int index) {
    std::shared_ptr<GenericItem> current_item = nullptr;
    // Checking if index is within the inventory
    if (index > (this->maxSize() - 1)) {
        return current_item;
    }

    current_item = this->inventory_list[index];
    this->inventory_list[index] = nullptr;
    return current_item;
}

/** Gets the item in the inventory.
 *
 * @param item The item name to get.
 * @return The item in the inventory (nullptr would be returned if the item
 * isn't in the inventory).
 * */
GenericItem* Inventory::getItem(std::string item) const {
    // Looping over all items
    for (unsigned int i = 0; i < this->m_max_size; i++) {
        // Checking if it is holding an item
        if (this->inventory_list[i] == nullptr) {
            continue;
        }
        // Checking if the item name is the same
        if(*(this->inventory_list[i]) == item) {
            return this->inventory_list[i].get();
        }
    }
    return nullptr;
}

/** Gets the item in the inventory.
 *
 * @overload
 * Takes in the index of the item in the inventory
 * instead.
 *
 * @param index The index of the item to get.
 * @return The item in the inventory (nullptr would be returned if the item
 * isn't in the inventory).
 * */
GenericItem* Inventory::getItem(unsigned int index) const {
    if (index > (this->maxSize() - 1)) {
        return nullptr;
    } else {
        return this->inventory_list[index].get();
    }
}

/** Gets the list of items in the inventory. */
std::shared_ptr<GenericItem>* Inventory::getItems() const {
    return this->inventory_list;
}

/** Gets the max size of the inventory.
 *
 * @return Max size of the inventory.
 * */
unsigned int Inventory::maxSize(void) const {
    return this->m_max_size;
}

/** Gets the amount of free spaces available in the inventory.
 *
 * @return The amount of free spaces left.
 */
int Inventory::getAvaiableSpaces(void) const {
    int count = 0;
    // Looping over all items
    for (unsigned int i = 0; i < this->maxSize(); i++) {
        // Incrementing count by 1 if it isn't a nullptr
        if (this->inventory_list[i] == nullptr) {
            count++;
        }
    }
    return count;
}

/** Overloaded operator to print the inventory.
 *
 * @param out The output stream.
 * @param cls The class iteself.
 *
 * @return The new output stream.
 * */
std::ostream& operator << (std::ostream &out, const Inventory &cls) {
    out << "Inventory Items:" << std::endl;
    // Looping over all items
    for (unsigned int i = 0; i < cls.maxSize(); i++) {
        out << i << " ";
        // Printing the name if there is an item
        if (cls.inventory_list[i] != nullptr) {
            out << *(cls.inventory_list[i]);
        }
        out << std::endl;
    }
    return out;
}
