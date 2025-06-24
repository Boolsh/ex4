#include <iostream>
#include <Windows.h>
#include <functional>
#include <fstream>
#include <map>
#include <set>
#include "HashTable_2.h"
#include <atomic>
#include <future>

// 1) Дан файл(Text_1.txt), состоящий из нескольких строк.Каждая строка содержит
// слова, разделенные любым количеством пробелов.Разработать функцию для поиска слов, которые
// встречаются в файле один раз и обладают заданным свойством.Функция должна принимать лямбду
// для проверки нужного свойства слова.Привести пример вызова функции для свойства : оканчиваются
// заданной буквой.

std::set<std::string> task1(std::function<bool(const std::string&)> check, std::ifstream& file)
{
	std::map<std::string, int> map;
	std::string word; 
	while (file >> word)
	{
		if (check(word))
			map[word]++;
	}

	std::set<std::string> res;
	for (std::map <std::string, int>::const_iterator it = map.begin(); it != map.end(); ++it)
	{
		if (it->second == 1)
			res.insert(it->first);
	}
	return res;
}

// 2) Описать функцию, которая принимает хэш - таблицу(разрешение коллизий внутреннее, с индикатором
// ячейки false, true) и ключ(string) и осуществляет поиск информации по ключу.
// Библиотека HashTable_2.h, файл данных Data_2.txt

int find(std::string key, Hash_table_2 HT)
{
	int res{ -1 };
	size_t index = HT.hash(key);

	while (HT.table[index].state && HT.table[index].elem.first != key)
		index = (index + 1) % HT.max_size;

	if (HT.table[index].state)
		res = index;

	return res;
}

// 3) В файле Matrix_3_2.txt записана матрица 10  10. Исполнитель может перемещаться по ячейкам в соседнюю правую
// ячейку или в соседнюю нижнюю.Перемещение возможно только в пределах матрицы.В ячейке матрицы записано 
// число(монета) от 1 до 10. Посетив ячейку, исполнитель забирает монету.Определите максимальную денежную сумму, 
// которую может собрать исполнитель, пройдя из левой верхней ячейки в правую нижнюю, и количество различных 
// маршрутов, каждый из которых позволяет собрать эту сумму.

const int N = 10;
int matrix[N][N];
int max_sum = 0;
int path_count = 0;
std::vector<std::pair<int, int>> current_path;

void load_matrix(std::ifstream& file) {
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			file >> matrix[i][j];
		}
	}
}

void backtrack(int i, int j, int current_sum) {
	current_path.push_back({ i, j });
	current_sum += matrix[i][j];

	if (i == N - 1 && j == N - 1) {
		if (current_sum > max_sum) {
			max_sum = current_sum;
			path_count = 1;
		}
		else if (current_sum == max_sum) {
			path_count++;
		}
	}
	else {
		if (j + 1 < N) {
			backtrack(i, j + 1, current_sum);
		}
		if (i + 1 < N) {
			backtrack(i + 1, j, current_sum);
		}
	}
	current_path.pop_back();
}

// 4) В файле Numbers_4.txt записан одномерный массив из
// 555 целых чисел.Найти минимум среди четных элементов.Создание потоков 
// организовать с использованием асинхронных задач.Потоки взаимодействующие.
// Взаимодействие организовать через атомарные типы.Решение реализовать
// с использованием 4 - х потоков.

std::atomic<int> min_even = -1;

void task_4(int* arr, int l, int r) 
{
	int min = -1;
	for (int i = l; i < r; i++) 
	{
		if (arr[i] % 2 == 0) 
			if (min == -1) 
				min = arr[i];
			else 
				if (arr[i] < min) min = arr[i];

	}
	if (min != -1) 
	{
		int current_min = min_even.load();
		if (current_min == -1) 
		{
			while (!min_even.compare_exchange_weak(current_min, min)) {}
		}
		else 
		{
			while (min < current_min && !min_even.compare_exchange_weak(current_min, min)) {}
		}
	}
}

int main()
{
	SetConsoleOutputCP(1251);

	std::cout << "\n--------------------------------------------\n";

	std::ifstream file("Text_!.txt");
	char ch = 'a';
	std::set<std::string> res = task1([ch](const std::string& word) {return word.back() == ch; }, file);

	if (res.empty())
		std::cout << "Нет слов, которые встречаются один раз\n";
	else
		for (std::set<std::string>::const_iterator it = res.begin(); it != res.end(); ++it)
			std::cout << *it << '\n';

	std::cout << "\n--------------------------------------------\n";

	std::ifstream file2("Data_2.txt");
	Hash_table_2 HT(60);
	HT.fill(file2);
	int res2 = find("april", HT);
	if (res2 == -1)
		std::cout << "\nNO\n";
	else
	{
		std::cout << "\nYES\n";
		//std::cout << HT.table[res2].elem.second << '\n';
	}

	std::cout << "\n--------------------------------------------\n";

	std::ifstream file3("Matrix_3_2.txt");
	load_matrix(file3);

	backtrack(0, 0, 0);

	std::cout << "Максимальная сумма: " << max_sum << '\n';
	std::cout << "Количество маршрутов: " << path_count << '\n';
	 
	std::cout << "\n--------------------------------------------\n";

	const int size = 5;
	int chung = size / 4;
	std::fstream file_4("Numbers_4.txt");
	int elem;
	int arr[size];
	for (int i = 0; i < size; i++)
		file_4 >> arr[i];

	std::vector<std::future<void>> treads;
	for (int i = 0; i < 4; i++)
	{
		int start = i * chung;
		int end = (i != 3) ? start + chung : size;

		treads.push_back(std::async(std::launch::async, task_4, std::ref(arr), start, end));
	}

	for (auto& it : treads)
		it.get();
	std::cout << " " << min_even.load();

	std::cin.get();
	return 0;
}