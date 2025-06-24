#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <functional>
#include <sstream>
#include <list>
#include <future>
#include <atomic>

#include "HT2.h"

// ким 2

// задание 1
//. Контейнеры. Дан файл (Text_1.txt), состоящий из нескольких строк. Каждая строка содержит 
//слова, разделенные любым количеством пробелов.Разработать функцию для поиска слов, которые
//встречаются в файле один раз и обладают заданным свойством.Функция должна принимать лямбду
//для проверки нужного свойства слова.Привести пример вызова функции для свойства : оканчиваются
//заданной буквой


std::map < std::string, int> map_create(std::ifstream& file,
    std::function<bool(std::string)> lambda)
{
    std::map < std::string, int> mp{};
    std::string line;
    std::stringstream ss;
    while (std::getline(file, line))
    {
        ss << line;
        std::string word;
        while (ss >> word)
        {
            if (lambda(word))
            {
                ++mp[word];
            }
        }
        ss.clear();
    }
    return mp;
}

void task1(std::ifstream& file, std::function<bool(std::string)> lambda)
{
    std::map < std::string, int> mp = map_create(file, lambda);

    for (const auto& elem : mp)
    {
        if (elem.second == 1)
            std::cout << elem.first << ", ";
    }
}

// задание 2
 //Хэширование.Описать функцию, которая принимает хэш - таблицу(разрешение коллизий внут -
 //   реннее, с индикатором ячейки false, true) и ключ(string) и осуществляет поиск информации по ключу.
 //   Библиотека HashTable_2.h, файл данных Data_2.txt

int task2(HashTableBool& ht, std::string key)
{
    int result = -1;
    int index = ht.hash(key);
    Vector t = ht.get_table();
    size_t ms = ht.get_max_size();

    while (t[index].used && t[index].info.first != key)
        index = (index + 1) % ms;

    if (t[index].used)
        result = index;

    return result;
}
//задание 3
//В файле Matrix_3_2.txt записана матрица 10  10. Исполнитель мо -
//жет перемещаться по ячейкам в соседнюю правую ячейку или в соседнюю нижнюю.Перемещение воз -
//можно только в пределах матрицы.В ячейке матрицы записано число(монета) от 1 до 10. Посетив
//ячейку, исполнитель забирает монету.Определите максимальную денежную сумму, которую может со -
//брать исполнитель, пройдя из левой верхней ячейки в правую нижнюю, и количество различных марш -
//рутов, каждый из которых позволяет собрать эту сумму.


const int n = 15;
int matrix[n][n];

void readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            file >> matrix[i][j];
    file.close();
}


int max_cost = -1;
int cnt_res = 1;
int sum = 0;

void Try(int i, int j)
{
    if (i == n - 1 && j == n - 1)
    {
        if (sum > max_cost)
        {
            max_cost = sum + matrix[n - 1][n - 1];
            cnt_res = 1;
        }
        else
            if ((sum + matrix[n - 1][n - 1]) == max_cost)
                cnt_res++;
    }
    else
    {
        if (j + 1 < n)
        {
            sum += matrix[i][j + 1];
            Try(i, j + 1);
            sum -= matrix[i][j + 1];
        }
        if (i + 1 < n)
        {
            sum += matrix[i + 1][j];
            Try(i + 1, j);
            sum -= matrix[i + 1][j];
        }
    }
}




// задание 4
//В файле Numbers_4.txt записан одномерный массив из 555 целых чисел.
//Найти минимум среди четных элементов.Создание потоков организовать с исполь -
//зованием асинхронных задач.Потоки взаимодействующие.Взаимодействие организовать через ато -
//марные типы.Решение реализовать с использованием 4 - х потоков

const size_t COUNT = 555;
const size_t NTHREADS = 4;

void Min(int* arr, size_t left, size_t right, std::atomic_int& result)
{
    for (size_t i = left; i < right; ++i)
    {
        if (abs(arr[i]) % 2 == 0)
        {
            int curr = result.load();
            if (abs(curr) % 2 || arr[i] <= curr)
            {
                result.compare_exchange_weak(curr, arr[i]);
            }

        }

    }
}

int min_parallel(int* arr)
{
    std::future<void> t[NTHREADS - 1];
    size_t block = COUNT / NTHREADS;
    std::atomic_int global_min{ arr[0] };
    for (size_t i = 0; i < NTHREADS - 1; ++i)
    {
        t[i] = std::async(std::launch::async, Min, arr, block * i, block * (i + 1), std::ref(global_min));
    }

    Min(arr, block * (NTHREADS - 1), COUNT, std::ref(global_min));
    for (size_t i = 0; i < NTHREADS - 1; ++i)
    {
        t[i].get();
    }
    return global_min;
}

void init_array(int* arr)
{
    for (size_t i = 0; i < COUNT; ++i)
        arr[i] = rand() % 1000 - 7;
}

int min_non_parallel(int* arr)
{
    int min_val{ arr[0] };

    for (size_t i = 1; i < COUNT; ++i)
    {
        if (abs(arr[i]) % 2 == 0 && (abs(min_val) % 2 || arr[i] <= min_val))
        {
            min_val = arr[i];
        }
    }
    return min_val;
}

int main()
{
    //// task 1
    //std::ifstream file("Text_1.txt");
    //std::string c{ "e" };
    //task1(file, [c](std::string s) {return s.substr(s.size() - 1) == c; });

    //task 2
   /* std::ifstream file("Data_2.txt");
    HashTableBool ht(15);
    ht.fill(file);

    int res2 = task2(ht, "oihgvb");
    if (res2 == -1)
        std::cout << "NOT FOUND\n";
    else std::cout << res2;*/

    ///////3
    Try(0, 0);
    if (max_cost != -1)
    {
        std::cout << "Max cost: " << max_cost << '\n';
        std::cout << "cnt: " << cnt_res << '\n';
    }


    ///////// task 4
    /*srand(GetTickCount());
    int arr[COUNT];
    init_array(arr);

    for (size_t i = 0; i < COUNT; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";

    std::cout << "non parallel = " << min_non_parallel(arr) << '\n';
    std::cout << "parallel = " << min_parallel(arr) << '\n';*/

    std::cin.ignore(std::cin.rdbuf()->in_avail()).get();
}
