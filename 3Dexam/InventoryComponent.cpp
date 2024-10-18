#pragma once
#include "InventoryComponent.h"
#include "BaseItem.h"
#include <iostream>
#include "ImGuiManager.h"

void InventoryComponent::AddItem(std::shared_ptr<BaseItem> item, int quantity)
{
    // Creating an ItemData object with the shared pointer and quantity
    ItemData newItem(item, quantity);

    // Checking for stackable items
    for (auto& i : items) {
        if (i.GetItemID() == newItem.GetItemID() &&
            (i.GetNumItems() + newItem.GetNumItems() <= i.GetStackSize())) {
            i.numItems += newItem.GetNumItems();
            return;
        }
    }

    // If not stackable, add as a new item
    items.push_back(newItem);
}

void InventoryComponent::RemoveItem(int itemID)
{
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->GetItemID() == itemID) {
            items.erase(it);
            break;
        }
    }
}

void InventoryComponent::UseItem(int itemslot)
{
    // Checking if itemslot is valid
    if (itemslot >= 0 && itemslot < items.size()) {
        auto& item = items[itemslot];

        if (item.GetIsStackable() && item.GetNumItems() > 0 && item.GetItemReference() != nullptr) {
            item.GetItemReference()->Use(); // Using the item
            item.numItems--;                // Decreasing the count

            // If no items left, remove it completely
            if (item.GetNumItems() == 0) {
                RemoveItem(item.GetItemID());
            }
        }
        else if (!item.GetIsStackable() && item.GetItemReference() != nullptr) {
            item.GetItemReference()->Use(); // Using the item
            RemoveItem(item.GetItemID());   // Removing it since it's not stackable
        }
    }
}

std::vector<ItemData> InventoryComponent::listItems()
{
    /*for (auto& item : items) {
        std::cout << "Item Name: " << item.GetItemName() << " Num Items: " << item.GetNumItems() << std::endl;
    }*/
    return items;
}

std::vector<ItemData> InventoryComponent::GetItems()
{
    return items;
}
