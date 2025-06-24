#include <string>
#include <iostream>
#include <fstream>
#include <set>
#include <map>
#include <sstream>
#include <climits>
#include <functional>
#include <Windows.h>
#include "HT1.h"
#include <vector>
#include <deque>
#include <thread>
#include <future>
#include <atomic>
using Map = std::map<std::string, int>;
using sMap = std::map<std::string, std::vector<int>>;

//1_1.Разработать функцию для поиска слов, которые 
//чаще всего встречаются в тексте и обладают заданным свойством.Если таких слов несколько, то вы
//вести все, в скобках указать сколько раз встречается слово.

//Map fill_map(std::string filename)
//{
//    std::ifstream file(filename);
//    Map word_map;
//    std::string word;
//    while (file >> word)
//    {
//        if (word_map.count(word)) word_map[word] += 1;
//        else word_map.insert({ word, 1 });
//    }
//    return word_map;
//}
//
//template<typename Predicate >
//void task1_1(Predicate condition, Map word_map)
//{
//    int max_count = 0;
//    std::vector<std::string> vect;
//    for (auto i : word_map)
//        if (i.second == max_count)
//            vect.push_back(i.first);
//        else if (i.second > max_count)
//        {
//            vect.clear();
//            vect.push_back(i.first);
//            max_count = i.second;
//        }
//
//
//    for (auto i : vect)
//        if (condition(i))
//            std::cout << i << " ";
//    std::cout << "  " << max_count << std::endl;
//}

//1_2.Разработать функцию для поиска слов, которые 
//встречаются в файле один раз и обладают заданным свойством.Функция должна принимать лямбду
//для проверки нужного свойства слова.

//Map fill_map(std::string filename)
//{
//    std::ifstream file(filename);
//    Map word_map;
//    std::string word;
//    while (file >> word)
//    {
//        if (word_map.count(word)) word_map[word] += 1;
//        else word_map.insert({word, 1});
//    }
//    return word_map;
//}
//
//template<typename Predicate >
//void task1_2(Predicate condition, Map word_map)
//{
//    for (auto i : word_map)
//        if (i.second == 1 and condition(i.first))
//            std::cout << i.first << " ";
//    std::cout << std::endl;
//}

//1_3.Разработать функцию для поиска слов, которые 
//есть во всех строках файла и обладают заданным свойством.
//вести все, в скобках указать сколько раз встречается слово.

//bool check(std::vector<int> arr, int &str_cnt)
//{
//    for (int i{1}; i < str_cnt; ++i)
//    {
//        bool res = false;
//        for (int j{}; j < arr.size(); ++j)
//        {
//            if (arr[j] == i)
//                res = true;
//        }
//        if (!res) return false;
//    }
//    return true;
//}
//
//sMap fill_map(std::string filename, int &str_cnt)
//{
//    std::ifstream file(filename);
//    sMap word_map;
//    std::string word, string{};
//    
//    while (std::getline(file, string))
//    {
//        str_cnt++;
//        std::istringstream stream(string);
//
//        while (stream >> word)
//            if (word_map.count(word)) word_map[word].push_back(str_cnt);
//            else word_map.insert({ word, {str_cnt} });
//    }
//    return word_map;
//}
//
//template<typename Predicate>
//void task1_3(Predicate condition, sMap word_map, int& str_cnt)
//{
//    for (auto i : word_map)
//        if (check(i.second, str_cnt) and condition(i.first))
//            std::cout << i.first << " " << i.second.size();
//}

//another

//using Set = std::set<std::string>;
//Set task1_3(std::function<bool(std::string)> lambda, std::string filename)
//{
//
//
//    std::ifstream file(filename);
//    Set word_set, help_set;
//
//
//    std::string word, string{};
//
//    std::getline(file, string);
//    std::istringstream stream(string);
//    while (stream >> word)
//        if (lambda(word)) word_set.insert(word);
//
//    while (std::getline(file, string))
//    {
//        std::istringstream stream(string);
//        while (stream >> word)
//            if (word_set.find(word) != word_set.end())
//                help_set.insert(word);
//        word_set = help_set;
//
//    }
//    return word_set;
//
//}

//2_1 Описать функцию, которая принимает хэш-таблицу (разрешение коллизий 
//внутреннее, с индикатором ячейки –1, 0, 1) и ключ(string) и осуществляет удаление информации по
//ключу.Библиотека HashTable_1.h, файл данных Data_2.txt

//bool task2_1(std::string key, HashTableInt& table)
//{
//    bool res{};
//    Vector arr = table.get_table();
//    int max_size = table.get_max_size(), index = table.hash(key);
//
//    while (!(arr[index].used == 0 || arr[index].used == 1 && arr[index].info.first == key))
//        index = (index + 1) % max_size;
//    if (arr[index].used == 1)
//    {
//        table.set_table(index, -1);
//        res = 1;
//    }
//
//    return res;
//}

//2_3 Описать функцию, которая принимает хэш-таблицу (разрешение коллизий 
//внутреннее, с индикатором ячейки –1, 0, 1) и ключ(string) и осуществляет ПОИСК информации по
//ключу.Библиотека HashTable_1.h, файл данных Data_2.txt

//int task2_3(std::string key, HashTableInt& table)
//{
//    int res{};
//    Vector arr = table.get_table();
//    int max_size = table.get_max_size(), index = table.hash(key);
//
//    while (!(arr[index].used == 0 || arr[index].used == 1 && arr[index].info.first == key))
//        index = (index + 1) % max_size;
//    if (arr[index].used == 1)
//    {
//        res = index;
//    }
//
//    return res;
//}
//
//


//3_1.В файле Matrix_3_1.txt записана матрица 10  10. Исполнитель мо
//жет перемещаться по ячейкам в соседнюю правую ячейку или в соседнюю нижнюю.Перемещение воз
//можно только в пределах матрицы.В ячейке матрицы записано число от 10 до 99 или число 0 – плата
//за посещение ячейки.Определите максимальную и минимальную плату, которую заплатит исполни
//тель, пройдя из левой верхней ячейки в правую нижнюю

//const int n = 10;
//
//int count_of_zeroes = 0;
//int min_cost = INT_MAX;
//int max_cost = 0;       
//int sum = 0;
//
//void task3_1(int i, int j, int matrix[][n]) 
//{
//
//    if (i == n - 1 && j == n - 1) 
//    {
//        if (count_of_zeroes == 2)
//        {
//            int total_sum = sum + matrix[i][j];
//            if (total_sum < min_cost) min_cost = total_sum;
//            if (total_sum > max_cost) max_cost = total_sum;
//        }
//    }
//    else {
//        if (j + 1 < n)
//        {
//            int next_val = matrix[i][j + 1];
//            bool is_zero = (next_val == 0);
//            if (count_of_zeroes + (is_zero ? 1 : 0) <= 2)
//            {
//                sum += next_val;
//                count_of_zeroes += is_zero ? 1 : 0;
//                task3_1(i, j + 1, matrix);
//                sum -= next_val;
//                count_of_zeroes -= is_zero ? 1 : 0;
//            }
//        }
//        if (i + 1 < n)
//        {
//            int next_val = matrix[i + 1][j];
//            bool is_zero = (next_val == 0);
//
//            if (count_of_zeroes + (is_zero ? 1 : 0) <= 2)
//            {
//                sum += next_val;
//                count_of_zeroes += is_zero ? 1 : 0;
//                task3_1(i + 1, j, matrix);
//                sum -= next_val;
//                count_of_zeroes -= is_zero ? 1 : 0;
//            }
//        }
//    }
//}


//3_2.В файле Matrix_3_2.txt записана матрица 10  10. Исполнитель мо
//жет перемещаться по ячейкам в соседнюю правую ячейку или в соседнюю нижнюю.Перемещение воз
//можно только в пределах матрицы.В ячейке матрицы записано число(монета) от 1 до 10. Посетив
//ячейку, исполнитель забирает монету.Определите максимальную денежную сумму, которую может со
//брать исполнитель, пройдя из левой верхней ячейки в правую нижнюю, и количество различных марш
//рутов, каждый из которых позволяет собрать эту сумму.

//const int n = 10;
//
//int count_of_zeroes = 0;
//int min_cost = INT_MAX;
//int max_cost = 0;       
//int sum = 0;
//void task3_2(int i, int j, int matrix[][n], int& max_cnt)
//{
//    if (i == n - 1 && j == n - 1)
//    {
//        if (sum > max_cost)
//        {
//            max_cost = sum + matrix[i][j];
//            max_cnt = 1;
//        }
//        else if (sum + matrix[i][j] == max_cost) max_cnt++;
//    }
//    else
//    {
//        if (j + 1 < n)
//        {
//            sum += matrix[i][j + 1];
//            task3_2(i, j + 1, matrix, max_cnt);
//            sum -= matrix[i][j + 1];
//        }
//        if (i + 1 < n)
//        {
//            sum += matrix[i+1][j];
//            task3_2(i + 1, j, matrix, max_cnt);
//            sum -= matrix[i+1][j];
//        }
//    }
//}

//3_3 Домино цепочку максимальной длины.

//using Domino = std::pair<int, int>;
//std::vector<Domino> dominoes{};
//std::list<Domino> bestChain;
//std::list<Domino> currentChain;
//
//void task_3(bool used[])
//{
//    bool extended = false;
//
//    for (size_t i = 0; i < dominoes.size(); ++i)
//    {
//        if (!used[i])
//        {
//            const Domino& d = dominoes[i];
//            if (d.second == currentChain.front().first)
//            {
//                used[i] = true;
//                currentChain.push_front(d);
//                task_3(used);
//                currentChain.pop_front();
//                used[i] = false;
//                extended = true;
//            }
//            else if (d.first == currentChain.back().second) {
//                used[i] = true;
//                currentChain.push_back(d);
//                task_3(used);
//                currentChain.pop_back();
//                used[i] = false;
//                extended = true;
//            }
//        }
//    }
//    if (!extended && currentChain.size() > bestChain.size())
//    {
//        bestChain = currentChain;
//    }
//}
//
//void task3_3()
//{
//    std::ifstream file("domino.txt");
//    std::string line;
//    while (std::getline(file, line)) {
//        std::istringstream iss(line);
//        int a, b;
//        char sep;
//        if (iss >> a >> b) {
//            dominoes.emplace_back(a, b);
//        }
//    }
//    file.close();
//
//    if (dominoes.empty())
//    {
//        std::cout << "no dominoes" << std::endl;
//        return;
//    }
//
//    bool used[15]{ false };
//
//    for (size_t i = 0; i < dominoes.size(); ++i) {
//        used[i] = true;
//        currentChain = { dominoes[i] };
//        task_3(used);
//        used[i] = false;
//    }
//
//    std::cout << "max chain lengh: " << bestChain.size() << "\n";
//    std::cout << "Chain:\n";
//    for (auto i : bestChain)
//    {
//        std::cout << "[" << i.first << "," << i.second << "] ";
//    }
//    std::cout << "\n";
//}

//deepSeek

//struct Domino {
//    int left;
//    int right;
//};
//
//int max_length = 0;
//std::vector<Domino> best_chain;
//
//void find_max_chain(std::vector<Domino>& dominoes, std::vector<bool>& used, std::vector<Domino>&current_chain) 
//{
//    if (current_chain.size() > max_length)
//    {
//        max_length = current_chain.size();
//        best_chain = current_chain;
//    }
//    for (size_t i = 0; i < dominoes.size(); ++i) 
//    {
//        if (!used[i]) 
//        {
//            if (current_chain.empty() or current_chain.back().right == dominoes[i].left) 
//            {
//                used[i] = true;
//                current_chain.push_back(dominoes[i]);
//
//                find_max_chain(dominoes, used, current_chain);
//
//                current_chain.pop_back();
//                used[i] = false;
//            }
//        }
//    }
//}
//
//void task3_3()
//{
//    std::ifstream file("domino.txt");
//    std::vector<Domino> dominoes;
//    int left, right;
//    while (file >> left >> right) {
//        dominoes.push_back({ left, right });
//    }
//
//    std::vector<bool> used(dominoes.size(), false);
//    std::vector<Domino> current_chain;
//
//    find_max_chain(dominoes, used, current_chain);
//
//
//    std::cout << "Максимальная длина цепочки: " << max_length << std::endl;
//    std::cout << "Цепочка: ";
//    for (const auto& domino : best_chain) {
//        std::cout << "[" << domino.left << "," << domino.right << "] ";
//    }
//    std::cout << std::endl;
//}


//4_1. В файле Numbers_4.txt записан одномерный массив из
//555 целых чисел.Найти номер последнего нечетного максимального элемента.Гарантируется, что не
//четные элементы есть.Создание потоков организовать с использованием класса thread.Потоки взаи
//модействующие.Взаимодействие организовать через interlocked - функции.Решение реализовать с ис
//пользованием 4 - х потоков.



// 4_1 В файле Numbers_4.txt записан одномерный массив из 555 целых чисел.
// Найти номер последнего нечетного максимального элемента. Гарантируется, что не -
// четные элементы есть. Создание потоков организовать с использованием класса thread. Потоки взаи -
// модействующие.Взаимодействие организовать через interlocked - функции.Решение реализовать с ис -
// пользованием 4 - х потоков.


//Л
// ЕСЯ

//const size_t COUNT = 10;
//const size_t NTHREADS = 4;
//volatile LONG global_max;
//volatile LONG global_num;
//
//void Max(int* arr, size_t left, size_t right)
//{
//    int max_val{ arr[left] };
//    size_t num{ left };
//
//    for (size_t i = left + 1; i < right; ++i)
//    {
//        if ((abs(arr[i]) % 2) && ((abs(max_val) % 2) == 0 or arr[i] >= max_val))
//        {
//            max_val = arr[i];
//            num = i;
//        }
//    }
//
//    LONG curr_max = InterlockedCompareExchange(&global_max, 0, 0);
//
//    if (max_val > curr_max || max_val == curr_max && num > global_num || curr_max % 2 == 0)
//    {
//        InterlockedCompareExchange(&global_max, max_val, curr_max);
//        InterlockedExchange(&global_num, num);
//    }
//}
//
//size_t task4_1(int* arr)
//{
//    std::thread t[NTHREADS - 1];
//    size_t block = COUNT / NTHREADS;
//
//    global_max = arr[0];
//    global_num = 0;
//
//    for (size_t i = 0; i < NTHREADS - 1; ++i)
//    {
//        t[i] = std::thread(Max, arr, block * i, block * (i + 1));
//    }
//
//    Max(arr, block * (NTHREADS - 1), COUNT);
//    for (size_t i = 0; i < NTHREADS - 1; ++i)
//        t[i].join();
//
//    return global_num;
//}

//4_2. В файле Numbers_4.txt записан одномерный массив из
//555 целых чисел.Найти минимум среди четных элементов.Создание потоков организовать с исполь
//зованием асинхронных задач.Потоки взаимодействующие.Взаимодействие организовать через ато
//марные типы.Решение реализовать с использованием 4 - х потоков.

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

int task4_2(int* arr)
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

//4_3.В файле Numbers_4.txt записан одномерный массив из 555 целых чисел.

//const size_t COUNT = 10;
//const size_t NTHREADS = 4;
//
//HANDLE event;
//
//void task_thread_event_winapi(int* left, int* right, volatile unsigned int& cnt) 
//{
//    unsigned int local_cnt = 0;
//    while (left < right) {
//        if (*left % 2 == 0) {
//            local_cnt++;
//        }
//        ++left;
//    }
//
//    WaitForSingleObject(event, INFINITE);
//    cnt += local_cnt;
//    SetEvent(event);
//}
//
//void task4_3(int* arr) 
//{
//    const int NTHREADS = 4;
//    std::thread t[NTHREADS - 1];
//    size_t block = COUNT / NTHREADS;
//    volatile unsigned int cnt = 0;
//
//    event = CreateEvent(NULL, FALSE, TRUE, NULL);
//
//    for (int i = 0; i < NTHREADS - 1; ++i) 
//    {
//        int* left = arr + block * i;
//        int* right = arr + (i + 1) * block;
//        t[i] = std::thread(task_thread_event_winapi, left, right, std::ref(cnt));
//    }
//
//    task_thread_event_winapi(arr + block * (NTHREADS - 1), arr + COUNT, std::ref(cnt));
//
//    for (size_t i = 0; i < NTHREADS - 1; ++i)
//        t[i].join();
//
//    CloseHandle(event);
//    std::cout << "Number of even elements: " << cnt << '\n';
//}




int main()
{
    //Map word_map = fill_map("test1.txt");
   

    //1_1
    
    //task1_1([](std::string word) {return word.find('a') != std::string::npos; }, word_map);

    //1_2
    
    //task1_1([](std::string word) {return word[word.length()-1] == 'a'; }, word_map );

    //1_3
    
    //int str_cnt = 0;
    //sMap word_map = fill_map("test1.txt", str_cnt);
    //task1_3([](std::string word) {return word[word.length()-1] == 'a'; }, word_map, str_cnt );
    //std::cout << "==============================================\n";
    //Set word_set = task1_3([](std::string word) {return word[word.length() - 1] == 'a'; }, "test1.txt");
    //if (word_set.empty())
    //    std::cout << "No words\n";
    //else
    //    for (std::string i : word_set)
    //        std::cout << i << " ";

    //2_3
    //std::ifstream file("gavno.txt");
    //HashTableInt table(100);
    //table.fill(file);
    //table.print();

    //task2_1("ponos", table);

    //int t2_3 = task2_3("ponos", table);
    //std::cout << t2_3 << std::endl;

    //table.print();



    //3_1

    //std::ifstream file("matrix1.txt");
    //int matrix[n][n];
    //for (int i{}; i < n; ++i)
    //    for (int j{}; j < n; ++j)
    //        file >> matrix[i][j];
    //sum = matrix[0][0];
    //if (sum == 0) count_of_zeroes++;
    //task3_1(0, 0, matrix);
    //if (min_cost != -1)
    //    std::cout << "Min cost: " << min_cost << '\n';
    //if (max_cost != -1)
    //    std::cout << "Max cost: " << max_cost << '\n';


    //3_2
    
    //int max_cnt{ 1 };
    //std::ifstream file("matrix1.txt");
    //int matrix[n][n];
    //for (int i{}; i < n; ++i)
    //    for (int j{}; j < n; ++j)
    //        file >> matrix[i][j];
    //sum = matrix[0][0];
    //if (sum == 0) count_of_zeroes++;
    //task3_2(0, 0, matrix, max_cnt);
    //if (max_cost != -1)
    //    std::cout << "Max cost: " << max_cost << ' ' << max_cnt << '\n';

    //3_3

    //task3_3();

    //4_1

    //std::ifstream file("Data_4.txt");
    //int arr[COUNT];
    //int a, b{0};
    //for (size_t i = 0; i < COUNT; ++i)
    //    file >> arr[i];

    //std::cout << "parallel = " << task4_1(arr) << '\n';

    //4_2
    srand(GetTickCount());
    int arr[COUNT];
    init_array(arr);

    for (size_t i = 0; i < COUNT; ++i)
    {
        std::cout << arr[i] << ' ';
    }
    std::cout << "\n\n";

    std::cout << "non parallel = " << min_non_parallel(arr) << '\n';
    std::cout << "parallel = " << task4_2(arr) << '\n';


    //4_3
    
    //task4_3(arr);

}
