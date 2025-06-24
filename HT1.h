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
std::string to_string(const Pair& pair)
{
	return pair.first + ' ' + pair.second;
}

struct Cell
{
	Pair info;
	int used = 0;
};

using Vector = std::vector<Cell>;

class HashTableInt
{
private:
	Vector table;
	size_t max_size;
	size_t size;
public:
	HashTableInt(size_t max_size) : max_size(max_size)
	{
		table.resize(max_size);
	}

	Vector get_table() { return table; }
	void set_table(int ind, int n) { table[ind].used = n; }
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

	int find(std::string key, Pair& elem)
	{
		int result = -1;
		int index = hash(key);
		while (!(table[index].used == 0 || table[index].used == 1 && table[index].info.first == key))
			index = (index + 1) % max_size;
		if (table[index].used == 1)
		{
			result = index;
			elem = table[index].info;
		}
		return result;
	}

	bool add(const Pair& elem)
	{
		bool result = false;
		int index = hash(elem.first);

		while (table[index].used == 1 && table[index].info.first != elem.first)
			index = (index + 1) % max_size;
		if (table[index].used != 1)
		{
			table[index].used = 1;
			table[index].info = elem;
			result = true;
		}
		return result;
	}

	//bool erase(std::string key)
	//{
	//	bool result = false;
	//	int index = hash(key);
	//	while (!(table[index].used == 0 || table[index].used == 1 && table[index].info.first == key))
	//		index = (index + 1) % max_size;
	//	if (table[index].used == 1)
	//	{
	//		result = true;
	//		table[index].used = -1;
	//	}
	//	return result;
	//}

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