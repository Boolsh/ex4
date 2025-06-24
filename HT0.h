//#pragma once
//#include <iostream>
//#include <fstream>
//#include <string>
//#include <vector>
//#include <list>
//#include <Windows.h>
//#include <functional>
//using Pair = std::pair<std::string, std::string>;
//std::string to_string(const Pair& pair)
//{
//	return pair.first + ' ' + pair.second;
//}
//using List = std::list<Pair>;
//using Vector = std::vector<List>;
////0
////list
//class Hash_Table_0
//{
//private:
//	Vector table;
//	size_t max_size;
//public:
//	Vector get_table() { return table; };
//	//void set_table(std::string key, ) { table; };
//
//	Hash_Table_0(size_t max_size) : max_size(max_size)
//	{
//		table.resize(max_size);
//	}
//	size_t hash(std::string key)
//	{
//		size_t res{};
//		for (char c : key)
//			res += c;
//		return res % max_size;
//	}
//	void fill(std::ifstream& file)
//	{
//		Pair elem;
//		while (file >> elem.first >> elem.second)
//			add(elem);
//	}
//	//bool find(std::string key, Pair& pair);
//	bool add(const Pair& pair)
//	{
//		bool result{ false };
//		size_t index{ hash(pair.first) };
//		List::iterator it = std::find_if(table[index].begin(), table[index].end(), [pair](Pair temp) {return temp.first == pair.first; });
//		if (it == table[index].end())
//		{
//			result = true;
//			table[index].push_back(pair);
//		}
//		return result;
//	}
//
//	//bool remove(std::string key)
//	//{
//	//	bool result{ false };
//	//	size_t index{ hash(key) };
//	//	//Pair temp{pair.first, ""};
//	//	List::iterator it = std::find_if(table[index].begin(), table[index].end(), [key](Pair temp) {return temp.first == key; });
//	//	if (it != table[index].end())
//	//	{
//	//		result = true;
//	//		table[index].erase(it);
//	//	}
//	//	return result;
//	//}
//
//	void print()
//	{
//		size_t index{};
//		for (auto lst : table)
//		{
//			if (!lst.empty())
//				for (auto pair : lst)
//					std::cout << index << ": " << to_string(pair) << '\n';
//			++index;
//		}
//	}
//};