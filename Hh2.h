#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <functional>
#include <sstream>
#include <list>
#include <Windows.h>
#include <vector>

using Pair = std::pair<std::string, std::string>;
std::string to_string(const Pair& elem)
{
	return elem.first + ' ' + elem.second;
}
struct Cell
{
	Pair info;
	bool used = false;
};

using Vector = std::vector<Cell>;

class HashTableBool
{
private:
	Vector table;
	size_t max_size;
	size_t size;
public:
	HashTableBool(size_t max_size) : max_size(max_size)
	{
		table.resize(max_size);
	}
	
	Vector get_table() { return table; }
	size_t get_max_size() { return max_size; }
	size_t get_size() { return size; }
	void set_size(size_t s) { size = s; }

	int hash(std::string key)
	{
		int result = 0;
		for (char c : key)
			result += c;
		return result % max_size;
	}

	/*int find(std::string key)
	{
		int result = -1;
		int index = hash(key);
		while (table[index].used && table[index].info.first != key)
			index = (index + 1) % max_size;
		if (table[index].used)
			result = index;
		return result;
	}*/

	bool add(const Pair& elem)
	{
		bool result = false;
		int index = hash(elem.first);
		while (table[index].used && table[index].info.first != elem.first)
			index = (index + 1) % max_size;
		if (!table[index].used)
		{
			result = true;
			table[index].info = elem;
			table[index].used = true;
		}
		return result;
	}

	/*bool erase(std::string key)
	{
		bool result = false;
		int index = find(key);
		if (index != -1)
		{
			auto dist = [this](int a, int b)
				{
					return (b - a + max_size) % max_size;
				};
			table[index].used = false;
			int window = index;
			++index;
			result = true;
			while (table[index].used)
			{
				if (dist(hash(table[index].info.first), index) >= dist(window, index))
				{
					table[window] = table[index];
					table[index].used = false;
					window = index;
				}
				index = (index + 1) % max_size;
			}
		}
		return result;
	}*/

	void fill(std::ifstream& file)
	{
		Pair elem;
		while (file >> elem.first >> elem.second)
			add(elem);
	}

	void print()
	{
		int index = -1;
		for (auto elem : table)
		{
			++index;
			if (table[index].used == 1)
			{
				std::cout << index << ": (" << hash(elem.info.first) << ") " << to_string(elem.info) << '\n';
			}
		}
	}
};