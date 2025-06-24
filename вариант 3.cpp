#include <iostream>
#include <Windows.h>
#include <fstream>
#include <map>
#include <set>
#include <functional>
#include <string>
#include <sstream>
#include "HashTable_1.h"
#include <thread>

// 1) Дан файл (Text_1.txt), состоящий из нескольких строк. Каждая строка содержит
// слова, разделенные любым количеством пробелов. Разработать функцию для поиска слов, которые есть
// во всех строках файла и обладают заданным свойством. Функция должна принимать лямбду для 
// проверки нужного слова. Привести пример вызова функции для свойства: оканчиваются заданной
// буквой.

int max_line(std::ifstream& file)
{
	file.clear();
	file.seekg(0);

	int cnt{};
	std::string line;
	while (getline(file, line))
		cnt++;
	return cnt;
}

std::set<std::string> task1(std::function<bool(const std::string&)> check, std::ifstream& file)
{
	std::set<std::string> res;

	std::string line{}, word;
	int num{};
	std::map<std::string, std::set<int>> map_words;
	std::stringstream ss;

	while (getline(file, line))
	{
		ss << line;
		num++;
		while (ss >> word)
			if (check(word))
				map_words[word].insert(num);
		ss.clear();
	}
	

	int max = max_line(file);

	for (std::map<std::string, std::set<int>>::const_iterator it = map_words.begin(); it != map_words.end(); ++it)
	{
		if ((it->second).size() == max)
			res.insert(it->first);
	}

	return res;
}

// 2) Описать функцию, которая принимает хэш-таблицу (разрешение коллизий внутреннее, 
// с индикатором ячейки -1, 0, 1), ключ (string) и осуществляет поиск информации по ключу

int find(std::string key, Hash_table_1 HT)
{
	int res{ -1 };
	size_t index = HT.hash(key);
	size_t start_index = index;

	while (!(HT.table[index].state == 0 ||
		HT.table[index].state == 1 && HT.table[index].elem.first == key))
		index = (index + 1) % HT.max_size;

	if (HT.table[index].state == 1)
		res = index;

	return res;
}

// 3) В файле Domino_3.txt записан набор из 15 костей домино. Построить из них цепочку максимальной длины 
// (кость домино можно устанавливать в начало или конец цепочки, поворачивать кость нельзя)

std::pair<std::vector<std::pair<int, int>>, int> task_3(std::vector<std::pair<int, int>>& arr, int left, int right, std::pair<std::vector<std::pair<int, int>>, int> len) 
{
	std::pair<std::vector<std::pair<int, int>>, int > res = len;
	std::pair<std::vector<std::pair<int, int>>, int > cur = len;

	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i].first == right)
		{
			std::pair<int, int> f = arr[i];
			std::vector<std::pair<int, int>> new_arr = arr;
			new_arr.erase(new_arr.begin() + i);
			std::vector<std::pair<int, int>> new_path = len.first;
			new_path.push_back(f);
			cur = task_3(new_arr, left, f.second, { new_path, len.second + 1 });
			if (cur.second > res.second)
				res = cur;
		}

		if (arr[i].second == left)
		{
			std::pair<int, int> f = arr[i];
			std::vector<std::pair<int, int>> new_arr = arr;
			new_arr.erase(new_arr.begin() + i);
			std::vector<std::pair<int, int>> new_path = len.first;
			new_path.insert(new_path.begin(), f);
			cur = task_3(new_arr, f.first, right, { new_path, len.second + 1 });
			if (cur.second > res.second)
				res = cur;
		}
	}
	return res;
}

// 4) В файле  Numbers_4.txt записан одномерный массив из 555 целых чисел. Найти количество 
// четных элементов. Создание потоков организовать с использованием класса thread. Потоки 
// взаимодействующие. Взаимодействие организовать через объект ядра "Событие"

const int ARR_SIZE = 555;
const int NUM_THREADS = 4;
int numbers[ARR_SIZE];
int even_counts[NUM_THREADS] = { 0 }; // Счётчик для каждого потока
HANDLE events[NUM_THREADS];           // События для взаимодействия

void count_evens(int thread_id, int start, int end)
{
	int local_count = 0;
	for (int i = start; i < end; ++i)
	{
		if (numbers[i] % 2 == 0)
			local_count++;
	}

	even_counts[thread_id] = local_count;

	// Сигнализируем главному потоку, что работа завершена
	SetEvent(events[thread_id]);
}

int main()
{
	SetConsoleOutputCP(1251);

	std::cout << "\n------------------------------------\n";

	std::ifstream file("Text_1.txt");
	char ch = 'a';
	std::set<std::string> res = task1([ch](const std::string& word) {return word.back() == 'a'; }, file);
	if (res.empty())
		std::cout << "NO";
	else
		for (std::set<std::string>::const_iterator it = res.begin(); it != res.end(); ++it)
			std::cout << *it << " ";

	std::cout << "\n------------------------------------\n";

	std::ifstream file2("Data_2.txt");
	Hash_table_1 HT(60);
	HT.fill(file2);
	int res2 = find("ct", HT);
	if (res2 == -1)
		std::cout << "\nNO\n";
	else
		std::cout << "\nYES\n";

	std::cout << "\n------------------------------------\n";

	std::fstream file_3("3.txt");
	std::vector<std::pair<int, int>> arr(15);
	for (int i = 0; i < 15; i++)
		file_3 >> arr[i].first >> arr[i].second;

	std::pair<std::vector<std::pair<int, int>>, int> maxi;
	maxi.second = 0;
	std::pair<std::vector<std::pair<int, int>>, int > cur;

	for (int i = 0; i < 15; i++)
	{
		std::pair<int, int> f = arr[i];
		std::vector<std::pair<int, int>> new_arr = arr;
		new_arr.erase(new_arr.begin() + i);
		cur = task_3(new_arr, f.first, f.second, { {f}, 1 });
		if (cur.second > maxi.second)
			maxi = cur;
	}

	std::cout << "\n" << maxi.second << "\n"; 
	for (auto it : maxi.first)
		std::cout << it.first << ":" << it.second << " ";

	std::cout << "\n------------------------------------\n";

	std::ifstream file4("Numbers_4.txt");
	for (int i = 0; i < ARR_SIZE; ++i)
		file4 >> numbers[i];
	// Создание событий и потоков
	std::vector<std::thread> threads;

	int chunk_size = ARR_SIZE / NUM_THREADS;

	for (int i = 0; i < NUM_THREADS; ++i)
	{
		events[i] = CreateEvent(NULL, TRUE, FALSE, NULL); // Автосброс выключен (TRUE), начальное состояние — несигнальное

		int start = i * chunk_size;
		int end = (i == NUM_THREADS - 1) ? ARR_SIZE : start + chunk_size;

		threads.emplace_back(count_evens, i, start, end);
	}
	// Ожидаем сигналы от всех потоков
	WaitForMultipleObjects(NUM_THREADS, events, TRUE, INFINITE);

	// Подсчёт общего количества чётных элементов
	int total_even = 0;
	for (int i = 0; i < NUM_THREADS; ++i)
	{
		total_even += even_counts[i];
		CloseHandle(events[i]); // Освобождаем ресурсы
	}
	// Завершаем потоки
	for (auto& t : threads)
		t.join();

	std::cout << "Количество четных элементов: " << total_even << '\n';

	std::cin.get();
	return 0;
}