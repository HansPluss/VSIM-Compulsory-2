#ifndef ITEMDATA_H
#define ITEMDATA_H

#include <memory>
#include <string>
#include "BaseItem.h"

class ItemData {
public:
    ItemData(std::shared_ptr<BaseItem> itemReference, int numItems)
        : itemReference(itemReference), numItems(numItems) {
        if (itemReference) {
            itemID = itemReference->GetItemID();
            isStackable = itemReference->GetIsStackable();
            stackSize = itemReference->GetStackSize();
            ItemName = itemReference->GetItemName();
        }
        else {
            // Handle null reference scenario
        }
    }

    std::shared_ptr<BaseItem> GetItemReference() { return itemReference; }
    int GetItemID() const { return itemID; }
    bool GetIsStackable() const { return isStackable; }
    int GetStackSize() const { return stackSize; }
    int GetNumItems() const { return numItems; }
    std::string GetItemName() { return ItemName; }

    int numItems; // Amount of current item

private:
    std::shared_ptr<BaseItem> itemReference; // Smart pointer for automatic memory management
    int itemID;
    bool isStackable;
    int stackSize;
    std::string ItemName;
};

#endif // ITEMDATA_H