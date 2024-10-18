#pragma once
#include <string>
class BaseItem
{
public:
    virtual ~BaseItem() {}					// Virtual destructor for proper cleanup
    virtual void Use() = 0;					
	virtual int GetItemID() = 0;
	virtual std::string GetItemName() = 0;
	virtual bool GetIsStackable() = 0;
	virtual int GetStackSize() = 0;
};

