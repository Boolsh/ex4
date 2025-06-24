#include <iostream>
#include <map>
#include <Windows.h>
#include <fstream>
#include <functional>
#include <string>
#include "HashTable_1.h"
#include <thread>

// 1) Дан файл Text_1.txt, состоящий из нескольких строк. Каждая строка содержит слова, разделенные любым количеством пробелов. 
// Разработать функцию для поиска слов, которые чаще всего встречаются в тексте и обладают заданным свойством. Если таких 
// слов несколько, то вывести все, в скобках указать сколько раз встречается слово. Функция должна принимать лямбду для
// проверки нужного свойства слова.Привести пример вызова функции для свойства : содержит заданную букву

int max_count(std::map<std::string, int> map)
{
	int max_cnt = 0;
	for (std::map<std::string, int>::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		if (it->second > max_cnt)
			max_cnt = it->second;
	}
	return max_cnt;
}

std::map<std::string, int> task1(std::function<bool(const std::string&)> check, std::ifstream& file)
{
	std::map<std::string, int> map;
	std::string word;
	while (file >> word)
	{
		if (check(word))
			map[word]++;
	}

	int max_cnt = max_count(map);

	std::map<std::string, int> res;
	for (std::map<std::string, int>::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		if (it->second == max_cnt)
			res[it->first] = it->second;
	}
	return res;
}

// 2) Описать функцию, которая принимает хэш - таблицу (разрешение коллизий
// внутреннее, с индикатором ячейки –1, 0, 1) и ключ(string) и осуществляет удаление информации по
// ключу. Библиотека HashTable_1.h, файл данных Data_2.txt

bool remove(std::string key, Hash_table_1& HT)
{
	bool res{ false };
	size_t index = HT.hash(key);
	size_t start_index = index;

	while (!(HT.table[index].state == 0 ||
		HT.table[index].state == 1 && HT.table[index].elem.first == key))
		index = (index + 1) % HT.max_size;

	if (HT.table[index].state == 1)
	{
		res = true;
		HT.size--;
		HT.table[index].state = -1;
	}

	return res;
}

// 3) В файле Matrix_3_1.txt записана матрица 10  10. Исполнитель может перемещаться по ячейкам в соседнюю 
// правую ячейку или в соседнюю нижнюю.Перемещение возможно только в пределах матрицы.В ячейке матрицы 
// записано число от 10 до 99 или число 0 – плата за посещение ячейки.Определите максимальную и минимальную 
// плату, которую заплатит исполнитель, пройдя из левой верхней ячейки в правую нижнюю(маршрут должен 
// проходить через две нулевые ячейки)

const int n = 10;

int count_of_zeroes = 0;
int min_cost = INT_MAX;
int max_cost = 0;
int sum = 0;

void task3_1(int i, int j, int matrix[][n]) {

	if (i == n - 1 && j == n - 1)
	{
		if (count_of_zeroes == 2)
		{
			int total_sum = sum + matrix[i][j];
			if (total_sum < min_cost) min_cost = total_sum;
			if (total_sum > max_cost) max_cost = total_sum;
		}
	}
	if (j + 1 < n)
	{
		int next_val = matrix[i][j + 1];
		bool is_zero = (next_val == 0);
		if (count_of_zeroes + (is_zero ? 1 : 0) <= 2)
		{
			sum += next_val;
			count_of_zeroes += is_zero ? 1 : 0;
			task3_1(i, j + 1, matrix);
			sum -= next_val;
			count_of_zeroes -= is_zero ? 1 : 0;
		}
	}
	if (i + 1 < n)
	{
		int next_val = matrix[i + 1][j];
		bool is_zero = (next_val == 0);

		if (count_of_zeroes + (is_zero ? 1 : 0) <= 2)
		{
			sum += next_val;
			count_of_zeroes += is_zero ? 1 : 0;
			task3_1(i + 1, j, matrix);
			sum -= next_val;
			count_of_zeroes -= is_zero ? 1 : 0;
		}
	}
}

// 4) В файле Numbers_4.txt записан одномерный массив из
// 555 целых чисел.Найти номер последнего нечетного максимального элемента.Гарантируется,
// что нечетные элементы есть.Создание потоков организовать с использованием класса thread.
// Потоки взаимодействующие.Взаимодействие организовать через interlocked - функции.Решение 
// реализовать с использованием 4 - х потоков.

const int ARR_SIZE = 555;
const int NUM_THREADS = 4;
int numbers[ARR_SIZE];

volatile long max_odd = -1;
volatile long max_odd_ind = -1;

void task4(int start, int end)
{
	for (int i = start; i < end; ++i)
	{
		if (numbers[i] % 2 != 0)
		{
			if (numbers[i] >= max_odd)
			{
				if (numbers[i] > max_odd || i > max_odd_ind)
				{
					InterlockedExchange(&max_odd, numbers[i]);
					InterlockedExchange(&max_odd_ind, i);
				}
			}
		}
	}
}


int main()
{
	SetConsoleOutputCP(1251);

	std::cout << "\n--------------------------------------------\n";
	std::ifstream file("Text_1.txt");
	char ch = 'a';
	std::map<std::string, int> res = task1([ch](const std::string& word) { return word.find(ch) != std::string::npos; }, file);

	if (res.empty())
		std::cout << "\nНет слов с заданным свойством\n";
	else
	{
		for (std::map<std::string, int>::const_iterator it = res.begin(); it != res.end(); ++it)
			std::cout << it->first << " (" << it->second << ")\n";
	}
	std::cout << "\n--------------------------------------------\n";

	std::ifstream file2("Data_2.txt");
	Hash_table_1 HT(20);
	HT.fill(file2);
	HT.print();
	remove("cat", HT);
	std::cout << "\nПосле удаления:\n";
	HT.print();

	std::cout << "\n--------------------------------------------\n";

	std::ifstream file3("Matrix_3_1.txt");

	int matrix[n][n];
	for (int i{}; i < n; ++i)
		for (int j{}; j < n; ++j)
			file3 >> matrix[i][j];
	sum = matrix[0][0];
	if (sum == 0) count_of_zeroes++;
	task3_1(0, 0, matrix);
	if (min_cost != -1)
		std::cout << "Min cost: " << min_cost << '\n';
	if (max_cost != -1)
		std::cout << "Max cost: " << max_cost << '\n';

	std::cout << "\n--------------------------------------------\n";


	std::ifstream file4("Numbers_4.txt");
	for (int i = 0; i < ARR_SIZE; ++i)
	    file4 >> numbers[i];

	int sub_arr_size = ARR_SIZE / NUM_THREADS;
	std::vector<std::thread> threads;

	for (int i = 0; i < NUM_THREADS; ++i)
	{
	    int start = i * sub_arr_size;
	    int end = (i == NUM_THREADS - 1) ? ARR_SIZE : start + sub_arr_size;
	    threads.emplace_back(task4, start, end);
	}

	for (auto& thread : threads)
	    thread.join();

	if (max_odd_ind != -1)
	{
	    std::cout << "Номер последнего нечетного максимального элемента: " << max_odd_ind << '\n';
	    std::cout << "Значение: " << max_odd << '\n';
	}

	std::cin.get();
	return 0;
}