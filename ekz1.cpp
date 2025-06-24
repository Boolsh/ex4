#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <functional>
#include <sstream>
#include <list>
#include <Windows.h>
#include <vector>
#include <thread>

#include "HT1.h"

// ким 1

// задание 1
//1. Контейнеры. Дан файл (Text_1.txt), состоящий из нескольких строк. Каждая строка содержит 
//слова, разделенные любым количеством пробелов.Разработать функцию для поиска слов, которые
//чаще всего встречаются в тексте и обладают заданным свойством.Если таких слов несколько, то вы -
//вести все, в скобках указать сколько раз встречается слово.Функция должна принимать лямбду для
//проверки нужного свойства слова.Привести пример вызова функции для свойства : содержит задан -
//ную букву
//

std::map < std::string, int> map_create(std::ifstream& file,
    std::function<bool(std::string)> lambda, int& maxi)
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
                maxi = maxi < ++mp[word] ? mp[word] : maxi;
            }
        }
        ss.clear();
    }
    return mp;
}

void task1(std::ifstream& file, std::function<bool(std::string)> lambda)
{
    int maxi{};
    std::map < std::string, int> mp = map_create(file, lambda, maxi);

    for (const auto& elem : mp)
    {
        if (elem.second == maxi)
            std::cout << elem.first << ", ";
    }
    std::cout << "( " << maxi << " )\n";
}


// задание 2 
//   Хэширование. Описать функцию, которая принимает хэш - таблицу (разрешение коллизий
//    внутреннее, с индикатором ячейки –1, 0, 1) и ключ(string) и осуществляет удаление информации по
//    ключу. Библиотека HashTable_1.h, файл данных Data_2.txt

bool task2(HashTableInt& ht, std::string key)
{
    bool result = false;
    int index = ht.hash(key);
    Vector t = ht.get_table();
    size_t ms = ht.get_max_size();

    while (!(t[index].used == 0 || t[index].used == 1 && t[index].info.first == key))
        index = (index + 1) % ms;
    if (t[index].used == 1)
    {
        result = true;
        ht.set_table(index, -1);
    }
    return result;
}

//задание 3
//Алгоритмы с возвратом.В файле Matrix_3_1.txt записана матрица 10  10. Исполнитель мо -
//жет перемещаться по ячейкам в соседнюю правую ячейку или в соседнюю нижнюю.Перемещение воз -
//можно только в пределах матрицы.В ячейке матрицы записано число от 10 до 99 или число 0 – плата
//за посещение ячейки.Определите максимальную и минимальную плату, которую заплатит исполни -
//тель, пройдя из левой верхней ячейки в правую нижнюю(маршрут должен проходить через две нулевые
//ячейки)

const int n = 15;

int count_of_zeroes{};
int matrix[n][n];
int min_cost = -1;
int max_cost = -1;
int sum = 0;
void readMatrixFromFile(const std::string& filename) {
    std::ifstream file(filename);
    for (int i = 0; i < n; ++i) 
        for (int j = 0; j < n; ++j) 
            file >> matrix[i][j];
    file.close();
}
void Try(int i, int j)
{
    if (i == n - 1 && j == n - 1 && count_of_zeroes == 2)
    {
        if (sum < min_cost || min_cost == -1)
            min_cost = sum + matrix[n - 1][n - 1];
        if (sum > max_cost)
            max_cost = sum + matrix[n - 1][n - 1];
    }
    else
    {
        if (j + 1 < n)
        {
            sum += matrix[i][j + 1];
            count_of_zeroes += (matrix[i][j + 1] == 0) ? 1 : 0;
            Try(i, j + 1);
            sum -= matrix[i][j + 1];
            count_of_zeroes -= (matrix[i][j + 1] == 0) ? 1 : 0;
        }
        if (i + 1 < n)
        {
            sum += matrix[i + 1][j];
            count_of_zeroes += (matrix[i + 1][j] == 0) ? 1 : 0;
            Try(i + 1, j);
            sum -= matrix[i + 1][j];
            count_of_zeroes -= (matrix[i + 1][j] == 0) ? 1 : 0;
        }
    }
}

// задание 4
// файле Numbers_4.txt записан одномерный массив из 555 целых чисел.
// Найти номер последнего нечетного максимального элемента. Гарантируется, что не -
// четные элементы есть. Создание потоков организовать с использованием класса thread. Потоки взаи -
// модействующие.Взаимодействие организовать через interlocked - функции.Решение реализовать с ис -
// пользованием 4 - х потоков.
const size_t COUNT = 555;
const size_t NTHREADS = 4;
volatile LONG global_max;
volatile LONG global_num;

void Max(int* arr, size_t left, size_t right)
{
    int max_val{ arr[left] };
    size_t num{ left };

    for (size_t i = left + 1; i < right; ++i)
    {
        if ((abs(arr[i]) % 2) && ((abs(max_val) % 2) == 0 || arr[i] >= max_val))
        {
            max_val = arr[i];
            num = i;
        }
    }

    LONG curr_max = InterlockedCompareExchange(&global_max, 0, 0);
    if ((max_val > curr_max || (max_val == curr_max && num > global_num)) && max_val % 2)
    {
        InterlockedCompareExchange(&global_max, max_val, curr_max);
        InterlockedExchange(&global_num, num);
    }
}

size_t max_parallel(int* arr)
{
    std::thread t[NTHREADS - 1];
    size_t block = COUNT / NTHREADS;

    global_max = arr[0];
    global_num = 0;

    for (size_t i = 0; i < NTHREADS - 1; ++i)
    {
        t[i] = std::thread(Max, arr, block * i, block * (i + 1));
    }

    Max(arr, block * (NTHREADS - 1), COUNT);
    for (size_t i = 0; i < NTHREADS - 1; ++i)
        t[i].join();

    return global_num;
}



int main()
{
    ///////// task 1
    /*std::ifstream file("Text_1.txt");
    char c = 'o';
    task1(file, [c](std::string s) {return s.find(c) != std::string::npos; });*/


    ///////// task 2
    /*std::ifstream file("Data_2.txt");
    HashTableInt ht(15);
    ht.fill(file);
    ht.print();

    bool res2 = task2(ht, "oihgvb");
    if (!res2)
        std::cout << "NOT FOUND\n";
    else std::cout << '\n';
    ht.print();*/

    ///////// task 4
    srand(GetTickCount());
    std::ifstream file("Data_4.txt");
    int arr[COUNT];
    for (size_t i = 0; i < COUNT; ++i)
    {
        file >> arr[i];
    }
    std::cout << "parallel = " << max_parallel(arr) << '\n';
    ///3

    //Try(0, 0);
    //if (min_cost != -1)
    //    std::cout << "Min cost: " << min_cost << '\n';
    //if (max_cost != -1)
    //    std::cout << "Max cost: " << max_cost << '\n';


    std::cin.ignore(std::cin.rdbuf()->in_avail()).get();
}