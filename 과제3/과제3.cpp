#include <string>
#include <iostream>
#include <algorithm>

class Item
{
public:
	Item() : name_(""), price_(0) {	}
	Item(const std::string& name, int price = 0) 
	: name_(name), price_(price){ }

	const std::string& GetName() const
	{
		return name_;
	}
	int GetPrice() const
	{
		return price_;
	}
	void Clear()
	{
		name_ = "";
		price_ = 0;
	}

	void printInfo() const
	{
		std::cout << "Name: " << name_ << ", price: " << price_ << "g\n";
	}

private:
	std::string name_;
	int price_;
};

bool compareItemByPrice(const Item& a, const Item& b)
{
	return a.GetPrice() < b.GetPrice();
}


template<typename T>
class Inventory
{
public:
	Inventory(int capacity = 10)
		: capacity_(capacity), size_(0)
	{
		if (capacity_ <= 0)
		{
			capacity_ = 1;
		}

		pItems_ = new T[capacity_];
	}

	~Inventory()
	{
		delete[] pItems_;
		pItems_ = nullptr;
	}

	void AddItem(const T& item)
	{
		if (size_ >= capacity_)
		{
			Resize(capacity_ * 2);
		}
		pItems_[size_] = item;
		++size_;
	}

	void RemoveLastItem()
	{
		if (size_ <= 0)
		{
			std::cout << "Inventory is empty\n";
			return;
		}

		std::string deleteName = pItems_[size_ - 1].GetName();

		--size_;
		pItems_[size_].Clear();

		std::cout << deleteName << " was gone...\n";
	}
	int GetSize() const
	{
		return size_;
	}
	int GetCapacity() const
	{
		return capacity_;
	}
	void PrintAllItems() const
	{
		if (size_ == 0)
		{
			std::cout << "empty\n";
			return;
		}

		for (int i = 0; i < size_; ++i)
		{
			std::cout << "["<< i + 1 <<"]";
			pItems_[i].printInfo();
		}
	}

	Inventory(const Inventory<T>& other) 
	{
		capacity_ = other.capacity_;
		size_ = other.size_;
		pItems_ = new T[capacity_];
		for (int i = 0; i < size_; ++i) 
		{
			pItems_[i] = other.pItems_[i];
		}
		std::cout << "copy complete!" << std::endl;
	}

	void Assign(const Inventory<T>& other)
	{
		if (this == &other)
		{
			return;
		}

		delete[] pItems_;

		capacity_ = other.capacity_;
		size_ = other.size_;

		pItems_ = new T[capacity_];

		for (int i = 0; i < size_; ++i)
		{
			pItems_[i] = other.pItems_[i];
		}
	}

	void Resize(int newCapacity)
	{
		if (newCapacity <= capacity_)
		{
			return;
		}

		T* newItems = new T[newCapacity];

		for (int i = 0; i < size_; ++i)
		{
			newItems[i] = pItems_[i];
		}

		delete[] pItems_;
		pItems_ = newItems;
		capacity_ = newCapacity;

	}

	void SortItems()
	{
		std::sort(pItems_, pItems_ + size_, compareItemByPrice);
	}


private:
	T* pItems_;
	int capacity_;
	int size_;
};

	int main()
	{
		Inventory<Item> itemInventory;
		int menu;

		  while (true)
    {
        std::cout << "\n===== MENU =====\n";
        std::cout << "1. Inventory\n";
        std::cout << "2. Add Item\n";
        std::cout << "3. Delete Item\n";
		std::cout << "4. sort by price\n";
        std::cout << "5. Exit\n";
        std::cout << "Choice: ";
        std::cin >> menu;
		std::cout << std::endl;


        if (menu == 1)
        {
            itemInventory.PrintAllItems();
        }
        else if (menu == 2)
        {
            std::string name;
            int price;

            std::cout << "Item name: ";
            std::cin >> name;

            std::cout << "Item price: ";
            std::cin >> price;

            itemInventory.AddItem(Item(name, price));
        }
        else if (menu == 3)
        {
            itemInventory.RemoveLastItem();
        }
		else if (menu == 4)
		{
			itemInventory.SortItems();
			std::cout << "Compare By price!\n";
		}
        else if (menu == 5)
        {
            std::cout << "BYE BYE~~\n";
            break;
        }
        else
        {
            std::cout << "It's a wrong number.\n";
        }
    }

    return 0;
}