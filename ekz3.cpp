#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <set>
#include <functional>
#include <vector>
#include<list>
#include "HT1.h"
#include <thread>
// task 1
//Разработать функцию для поиска слов, которые 
//есть во всех строках файла и обладают заданным свойством.
//вести все, в скобках указать сколько раз встречается слово.
std::set<std::string> task1_3(std::function<bool(std::string)> lambda, std::istream file)
{
    std::set<std::string> word_set, help_set;

    std::string word, string{};

    std::getline(file, string);
    std::istringstream stream(string);
    while (stream >> word)
        if (lambda(word)) word_set.insert(word);

    while (std::getline(file, string))
    {
        std::istringstream stream(string);
        while (stream >> word)
            if (word_set.find(word) != word_set.end())
                help_set.insert(word);
        word_set = help_set;
    }
    return word_set;

}

// task 2
//Описать функцию, которая принимает хэш-таблицу (разрешение коллизий 
//внутреннее, с индикатором ячейки –1, 0, 1) и ключ(string) и осуществляет удаление информации по
//ключу.Библиотека HashTable_1.h, файл данных Data_2.txt

int task2_3(std::string key, HashTableInt& table)
{
    int res{};
    Vector arr = table.get_table();
    int max_size = table.get_max_size(), index = table.hash(key);

    while (!(arr[index].used == 0 || arr[index].used == 1 && arr[index].info.first == key))
        index = (index + 1) % max_size;
    if (arr[index].used == 1)
    {
        res = index;
    }

    return res;
}



// task 3
//Алгоритмы с возвратом.В файле Domino_3.txt записан набор из 15 костей домино.
// Построить из них цепочку максимальной длины(кость домино можно устанавливать 
// в начало или конец це - почки, поворачивать кость нельзя).

using Domino = std::pair<int, int>;
std::vector<Domino> dominoes{};
std::list<Domino> bestChain;
std::list<Domino> currentChain;

void task_3(bool used[])
{
    bool extended = false;

    for (size_t i = 0; i < dominoes.size(); ++i)
    {
        if (!used[i])
        {
            const Domino& d = dominoes[i];
            if (d.second == currentChain.front().first)
            {
                used[i] = true;
                currentChain.push_front(d);
                task_3(used);
                currentChain.pop_front();
                used[i] = false;
                extended = true;
            }
            else if (d.first == currentChain.back().second) {
                used[i] = true;
                currentChain.push_back(d);
                task_3(used);
                currentChain.pop_back();
                used[i] = false;
                extended = true;
            }
        }
    }
    if (!extended && currentChain.size() > bestChain.size())
    {
        bestChain = currentChain;
    }
}


//4. Параллельное программирование.В файле Numbers_4.txt записан одномерный массив из 555 целых чисел. 
// Найти количество четных элементов.
//нием класса thread.Потоки взаимодействующие.Взаимодействие организовать через объект ядра «Событие».

const size_t COUNT = 10;
const size_t NTHREADS = 4;

HANDLE event;

void task_thread_event_winapi(int* left, int* right, volatile unsigned int& cnt)
{
    unsigned int local_cnt = 0;
    while (left < right) {
        if (*left % 2 == 0) {
            local_cnt++;
        }
        ++left;
    }

    WaitForSingleObject(event, INFINITE);
    cnt += local_cnt;
    SetEvent(event);
}

void task4_3(int* arr)
{
    const int NTHREADS = 4;
    std::thread t[NTHREADS - 1];
    size_t block = COUNT / NTHREADS;
    volatile unsigned int cnt = 0;

    event = CreateEvent(NULL, FALSE, TRUE, NULL);

    for (int i = 0; i < NTHREADS - 1; ++i)
    {
        int* left = arr + block * i;
        int* right = arr + (i + 1) * block;
        t[i] = std::thread(task_thread_event_winapi, left, right, std::ref(cnt));
    }

    task_thread_event_winapi(arr + block * (NTHREADS - 1), arr + COUNT, std::ref(cnt));

    for (size_t i = 0; i < NTHREADS - 1; ++i)
        t[i].join();

    CloseHandle(event);
    std::cout << "Number of even elements: " << cnt << '\n';
}


int main() {
    ////task 1
    // std::ifstream file("test1.txt");
    //std::set<std::string> word_set = task1_3([](std::string word) {return word[word.length() - 1] == 'a'; }, file);
    //if (word_set.empty())
    //    std::cout << "No words\n";
    //else
    //    for (std::string i : word_set)
    //        std::cout << i << " ";

    //// task 2
    //std::ifstream file("test2.txt");
    //HashTableInt table(100);
    //table.fill(file);
    //table.print();
    //int t2_3 = task2_3("ponos", table);
    //std::cout << t2_3 << "\n";
    //table.print();

    //task 3
    std::ifstream file("Domino_3.txt");
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int a, b;
        char sep;
        if (iss >> a >> sep >> b) {
            dominoes.emplace_back(a, b);
        }
    }
    file.close();

    if (dominoes.empty())
    {
        std::cout << "no dominoes" << std::endl;
        return 1;
    }

    bool used[15]{ false };

    for (size_t i = 0; i < dominoes.size(); ++i) {
        used[i] = true;
        currentChain = { dominoes[i] };
        task_3(used);
        used[i] = false;
    }

    std::cout << "max chain lengh: " << bestChain.size() << "\n";
    std::cout << "Chain:\n";
    for (auto i : bestChain)
    {
        std::cout << "[" << i.first << "," << i.second << "] ";
    }
    std::cout << "\n";

    std::cin.ignore(std::cin.rdbuf()->in_avail()).get();

}