/**
 * @file main.cpp 
 * @brief Основной файл, в котором прозводится обработка наборов данных
 * 
 * В этом файле производится создание объектов заданных классов и считывание данных из наборов данных.
 * 
 * Через указанные методы производится поиск элементов по определённому ключу и программно замеряется время поиска. 
 * Результаты измерения записываются в отдельный файл.
 */


#include "lab2.h"

#include <fstream>
#include <iostream>
#include <map>
#include <chrono>


#define N 15 ///< Количество наборов данных

/// Осноная функция с полной обработкой данных
int main()
{
  
  std::string in_filepath_base  = "./datasets/dataset_"; ///< Основа для пути к набору данных
  std::string out_filepath = "./results.csv";            ///< Путь к файлу с результатами
  std::string target_filepath = "./target_key.txt";      ///< Путь к файлу с искомым ключом
  
  // Получение искомого ключа из файла
  std::ifstream target_file(target_filepath);
  if (target_file.is_open())
    std::cout << "Open " + target_filepath + "\n\n";

  std::string target;
  getline(target_file, target);

  target_file.close();
  if (!target_file.is_open())
    std::cout << "Close " + target_filepath + "\n\n";



  // Открытие файла результатов и ввод названий полей
  std::ofstream out_file(out_filepath);

  if (out_file.is_open())
    std::cout << "Open " + out_filepath + "\n\n";

  out_file << "Size,Linear Search,Binary Tree,Red-Black Tree,Hash Table,Multimap\n";



  // Основной цикл обработки
  for (int i = 1; i <= N; ++i)
  {
    Object obj; ///< Объект-буфер

    std::vector<Object> vec; ///< Вектор для инициализации объектов

    // Открытие файла с набором данных для чтения
    std::string in_filepath = in_filepath_base + std::to_string(i) + ".csv";
    std::ifstream in_file(in_filepath);

    if (in_file.is_open())
      std::cout << "> Open " + in_filepath + "\n";

    in_file.ignore(100, '\n');



    size_t step = 0; ///< Переменная для подсчёта количества объектов в наборе

    // Цикл считывания набора данных
    while (!in_file.eof())
    {
      if (++step % 10000 == 0)
        std::cout << "\tread " << step << " lines\n";
      
      in_file >> obj;
      vec.push_back(obj);

      in_file.peek();
    }

    // Закрытие файла с набором данных
    in_file.close();

    if (!in_file.is_open())
      std::cout << "> Close " + in_filepath + "\n";

    
    // Вывод и запись размера набора данных
    out_file << step << ",";
    std::cout << "    " << step << " lines was read\n\n";


    // Начало блоков поиска
    std::cout << "Searching for " << target << "...\n";


    std::chrono::time_point<std::chrono::high_resolution_clock> start, end; ///< Переменная для меток времени
    
    // Блок линейного поиска
    {
      std::cout << "    Linear search... " << std::flush;

      start = std::chrono::high_resolution_clock::now();
      linearSearch(vec, target);
      end   = std::chrono::high_resolution_clock::now();

      out_file << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << ",";
      std::cout << "completed\n" << std::flush;
    }

    // Блок поиска в бинарном дереве
    {
      BinaryTree binTree(vec); ///< Объект бинарного дерева

      std::cout << "    Binary tree search... " << std::flush;

      start = std::chrono::high_resolution_clock::now();
      binTree.search(target);
      end   = std::chrono::high_resolution_clock::now();

      out_file << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << ",";
      std::cout << "completed\n" << std::flush;
    }

    // Блок поиска в красно-чёрном дереве
    {
      RBTree rbTree(vec); ///< Объект красно-чёрного дерева

      std::cout << "    Red-Black tree search... " << std::flush;

      start = std::chrono::high_resolution_clock::now();
      rbTree.search(target);
      end   = std::chrono::high_resolution_clock::now();

      out_file << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << ",";
      std::cout << "completed\n" << std::flush;
    }

    // Блок поиска в хеш-таблице
    {
      HashTable hashTable(vec); ///< Объект хеш-таблицы

      std::cout << "    Hash table search... " << std::flush;

      start = std::chrono::high_resolution_clock::now();
      hashTable.search(target);
      end   = std::chrono::high_resolution_clock::now();

      out_file << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << ",";
      std::cout << "completed\n" 
                << "\tcollisions: " << hashTable.getCollisions() << "\n"
                << "\tfullness: " << hashTable.getFullness() << "/" << hashTable.getCapacity() << "\n" 
                << std::flush;
    }

    // Блок поиска в std::multimap
    {
      std::multimap<std::string, Object> mmap; ///< Объект std::multimap

      for (auto item : vec)
        mmap.insert({item.key(), item});

      std::cout << "    Multimap search... " << std::flush;

      start = std::chrono::high_resolution_clock::now();
      mmap.equal_range(target);
      end   = std::chrono::high_resolution_clock::now();

      out_file << std::chrono::duration_cast<std::chrono::microseconds>(end-start).count() << "\n";
      std::cout << "completed\n\n\n" << std::flush;
    }


  }

  // Закрытие файла с результатами
  out_file.close();
  
  if (!out_file.is_open())
  std::cout << "Close " + out_filepath + "\n";
  
  
  return 0;
}