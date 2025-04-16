/**
 * @file lab2.h
 * @brief Заголовочный файл содержащий необходимые классы и функции
 * 
 * В этом файле объявляются следующие классы и функции:
 * - Object
 * - linearSearch
 * - BinaryTree
 * - RBTree
 * - HashTable
 */

#include <string>
#include <vector>


/// @brief Объекты класса Object хранят данные о поездах
struct Object
{
  int         train_number; ///< Номер поезда. format: ######
  std::string depart_date;  ///< Дата отправления поезда. format: YYYY.MM.DD
  std::string train_type;   ///< Тип поезда. [скорый, пассажирский, товарный]
  std::string depart_time;  ///< Время отправления поезда. format: hh.mm.ss
  std::string travel_time;  ///< Время в пути. format: hh.mm.ss

  std::string key() const;  ///< Метод, возвращающий ключ объекта
};


bool operator>  (const Object&, const Object&); ///< Оператор сравнения "больше"    для объектов типа Object
bool operator>= (const Object&, const Object&); ///< Оператор сравнения "не меньше" для объектов типа Object
bool operator== (const Object&, const Object&); ///< Оператор сравнения "равно"     для объектов типа Object
bool operator<= (const Object&, const Object&); ///< Оператор сравнения "не больше" для объектов типа Object
bool operator<  (const Object&, const Object&); ///< Оператор сравнения "меньше"    для объектов типа Object
bool operator!= (const Object&, const Object&); ///< Оператор сравнения "не равно"  для объектов типа Object


std::ifstream& operator>> (std::ifstream&, Object&); ///< Оператор чтения объектов типа Object из потока


std::vector<Object> linearSearch (const std::vector<Object>&, const std::string&); ///< Функция для линейного поиска объектов по ключу


/// @brief Класс бинарного дерева
class BinaryTree
{
  /// @brief Класс узла бинарного дерева
  struct Node
  {
    Object item;        ///< Хранимый в узле объект класса Object
    Node *left, *right; ///< Указатель на узел-ребёнка

    Node(Object); ///< Конструктор узла бинарного дерева
    ~Node();      ///< Деструктор  узла бинарного дерева

    std::string key() const; ///< Метод для получения ключа хранимого объекта
  };

  Node* root; ///< Указатель на корень бинарного дерева
  
public:
  BinaryTree();                           ///< Конструктор бинарного дерева по умолчанию
  BinaryTree(const std::vector<Object>&); ///< Конструктор бинарного дерева по набору объектов класса Object
  ~BinaryTree();                          ///< Деструктор бинарного дерева
  
  void insert(const Object&);                           ///< Метод для вставки нового объекта класса Object
  std::vector<Object> search(const std::string&) const; ///< Метод для поиска всех объектов в бинарном дереве с заданным ключом
};


/// @brief Класс красно-чёрного дерева 
class RBTree
{
  /// @brief Перечисление возможных цветов узлов красно-чёрного дерева
  enum Color {None, Black, Red};

  /// @brief Класс узла красно-чёрного дерева
  struct Node
  {
    Object item;                 ///< Хранимый в узле объект класса Object
    Color color;                 ///< Цвет узла красно-чёрного дерева
    Node *left, *right, *parent; ///< Указатель на детей и родителя узла красно-чёрного дерева
    bool empty;                  ///< Метка фиктивного узла красно-чёрного дерева

    Node();       ///< Конструктор узла красно-чёрного дерева по умолчанию
    Node(Object); ///< Конструктор узла красно-чёрного дерева
    ~Node();      ///< Деструктор  узла красно-чёрного дерева
    
    void        erase();         ///< Метод для точечного удаления узла красно-чёрного дерева
    std::string key()     const; ///< Метод для получения ключа хранимого объекта класса Object
    bool        isLeft()  const; ///< Метод для определения, является ли узел левым ребёнком родителя
    Node*       sibling() const; ///< Метод для получения указателя на второго ребёнка родителя узла
  };

  Node* root; ///< Указатель на корень красно-чёрного дерева

  void rotateLeft  (Node*); ///< Метод для совершения левого  поворота вокруг узла красно-чёрного дерева
  void rotateRight (Node*); ///< Метод для совершения правого поворота вокруг узла красно-чёрного дерева

  void balanceTree (Node*); ///< Метод для восстановления свойств красно-чёрного дерева

public:
  RBTree();                           ///< Конструктор красно-чёрного дерева по умолчанию
  RBTree(const std::vector<Object>&); ///< Констуктор красно-чёрного дерева по набору объектов класса Object
  ~RBTree();                          ///< Деструктор красно-чёрного дерева

  void insert(const Object&);                                            ///< Метод для вставки нового объекта класса Object
  std::vector<Object> search(const std::string&, Node* = nullptr) const; ///< Метод для поиска всех объектов в красно-чёрном дереве с заданным ключом
};


/// @brief Класс хеш-таблицы
class HashTable
{
  /// @brief Класс узла хеш-таблицы
  struct Node
  {
    std::string key; ///< Ключ объекта класса Object, хранимого в узле
    Object item;     ///< Хранимый в узле объект класса Object
    Node* next;      ///< Указатель на следующий узел списка

    Node(Object); ///< Конструктор узла хеш-таблицы
    ~Node();      ///< Деструктор  узла хеш-таблицы

    bool insert(const Object&);                           ///< Рекурсивный метод для вставки объекта класса Object в список
    std::vector<Object> search(const std::string&) const; ///< Рекурсивный метод для поиска объектов с заданным ключом
  };

  std::vector<Node*> table; ///< Таблица для хранения узлов хеш-таблицы
  size_t table_size;        ///< Размер хеш-таблицы

  size_t collisions; ///< Количество возникших коллизий
  size_t fullness;   ///< Заполненность хеш-таблицы
  
  size_t hashFunc(const std::string&) const; ///< Хеш-функция
  void expandTable();                        ///< Метод для расширения хеш-таблицы

public:
  HashTable();                           ///< Конструктор хеш-таблицы по умолчанию
  HashTable(const std::vector<Object>&); ///< Конструктор хеш-таблицы по набору объектов класса Object
  ~HashTable();                          ///< Деструктор  хеш-таблицы

  void insert(const Object&);                           ///< Метод для вставки нового объекта класса Object
  std::vector<Object> search(const std::string&) const; ///< Метод для поиска всех объектов в хеш-таблице с заданным ключом

  size_t getCollisions() const; ///< Метод для получения количества возникших коллизий
  size_t getFullness() const;   ///< Метод для получения заполненности хеш-таблицы
  size_t getCapacity() const;   ///< Метод для получения размера хеш-таблицы
};