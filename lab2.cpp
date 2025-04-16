/**
 * @file lab2.cpp
 * @brief Файл с реализацией классов, функций и методов из lab2.h
 */

#include "lab2.h"

#include <fstream>


//////////////////////////////////////////////
//                  Объект                  //
//////////////////////////////////////////////

/// @brief Метод, возвращающий ключ объекта
/// @return Ключ объекта. По условию ключом является дата отправки поезда
std::string Object::key () const
{
  return this->depart_date;
}


/// @brief Оператор сравнения "больше" для объектов типа Object
/// @param obj1 первый операнд класса Object
/// @param obj2 первый операнд класса Object
/// @return Поочерёдно сравниваются поля [Дата отправки, Время отправки, Номер поезда, Время в пути]
bool operator> (const Object& obj1, const Object& obj2)
{

  if      (obj1.depart_date  != obj2.depart_date)  return obj1.depart_date  > obj2.depart_date;
  else if (obj1.depart_time  != obj2.depart_time)  return obj1.depart_time  > obj2.depart_time;
  else if (obj1.train_number != obj2.train_number) return obj1.train_number > obj2.train_number;
  else                                             return obj1.travel_time  > obj2.travel_time;

}


/// @brief Оператор сравнения "не меньше" для объектов типа Object
/// @param obj1 первый операнд класса Object
/// @param obj2 первый операнд класса Object
/// @return Поочерёдно сравниваются поля [Дата отправки, Время отправки, Номер поезда, Время в пути]
bool operator>= (const Object& obj1, const Object& obj2)
{
  return !(obj1 < obj2);
}


/// @brief Оператор сравнения "равно" для объектов типа Object
/// @param obj1 первый операнд класса Object
/// @param obj2 первый операнд класса Object
/// @return Поочерёдно сравниваются поля [Дата отправки, Время отправки, Номер поезда, Время в пути]
bool operator== (const Object& obj1, const Object& obj2)
{

  if (obj1.depart_date  == obj2.depart_date  && 
      obj1.depart_time  == obj2.depart_time  &&
      obj1.train_number == obj2.train_number &&
      obj1.travel_time  == obj2.travel_time)
          return true;
  else return false;

}


/// @brief Оператор сравнения "не больше" для объектов типа Object
/// @param obj1 первый операнд класса Object
/// @param obj2 первый операнд класса Object
/// @return Поочерёдно сравниваются поля [Дата отправки, Время отправки, Номер поезда, Время в пути]
bool operator<= (const Object& obj1, const Object& obj2)
{
  return !(obj1 > obj2);
}


/// @brief Оператор сравнения "меньше" для объектов типа Object
/// @param obj1 первый операнд класса Object
/// @param obj2 первый операнд класса Object
/// @return Поочерёдно сравниваются поля [Дата отправки, Время отправки, Номер поезда, Время в пути]
bool operator<  (const Object& obj1, const Object& obj2)
{
  return obj2 > obj1;
}


/// @brief Оператор сравнения "не равно" для объектов типа Object
/// @param obj1 первый операнд класса Object
/// @param obj2 первый операнд класса Object
/// @return Поочерёдно сравниваются поля [Дата отправки, Время отправки, Номер поезда, Время в пути]
bool operator!= (const Object& obj1, const Object& obj2)
{
  return !(obj1 == obj2);
}


/// @brief Оператор чтения объектов типа Object из потока
/// @param in Поток, из которого происходит чтение данных
/// @param obj Объект класса Object, в который происходит запись
std::ifstream& operator>> (std::ifstream& in, Object& obj)
{
  std::string line;
  std::getline(in, line, ',');
  obj.train_number = std::stoi(line);
  
  std::getline(in, obj.depart_date, ',');
  std::getline(in, obj.train_type, ',');
  std::getline(in, obj.depart_time, ',');
  std::getline(in, obj.travel_time);

  return in;
}




//////////////////////////////////////////////
//             Линейный поиск               //
//////////////////////////////////////////////

/// @brief Функция для линейного поиска объектов по ключу
/// @param vec Вектор, в котором происходит поиск
/// @param key Ключ, по которому происходит поиск
/// @return Список объектов класса Object, чьи ключи совпали с искомым
std::vector<Object> linearSearch (const std::vector<Object>& vec, const std::string& key)
{
  std::vector<Object> result;

  for (auto it = vec.begin(); it != vec.end(); ++it)
  {
    if ( it->key() == key ) result.push_back(*it);
  }

  return result;
}




//////////////////////////////////////////////
//             Бинарное дерево              //
//////////////////////////////////////////////

/// @brief Конструктор узла бинарного дерева
/// @param obj Объект класса Object, помещаемый в узел
BinaryTree::Node::Node (Object obj)
: left(nullptr), right(nullptr), item(obj) {}


/// @brief Деструктор узла бинарного дерева
/// Рекурсивно удаляет все узлы-дети
BinaryTree::Node::~Node ()
{
  delete left;
  delete right;
}


/// @brief Метод для получения ключа хранимого объекта
/// @return Ключ хранимого объекта класса Object
std::string BinaryTree::Node::key () const
{
  return item.key();
}



/// @brief Конструктор бинарного дерева по умолчанию
BinaryTree::BinaryTree ()
: root(nullptr) {}


/// @brief Конструктор бинарного дерева по набору объектов класса Object
/// @param itemList Список объектов класса Object, которые помещаются в дерево при создании
BinaryTree::BinaryTree (const std::vector<Object>& itemList)
: root(nullptr)
{
  for (auto item : itemList)
  {
    this->insert(item);
  }
}


/// @brief Деструктор бинарного дерева
BinaryTree::~BinaryTree ()
{
  delete root;
}


/// @brief Метод для вставки нового объекта класса Object
/// @param obj Объект класса Object, помещаемый в бинарное дерево
void BinaryTree::insert (const Object& obj)
{
  if ( root == nullptr ) 
  {
    root = new Node(obj);
    return;
  }

  Node *cur = root;
  std::string key = obj.depart_date;

  while ( cur )
  {
    if (cur->key() >= key)
    {
      if (cur->right)  cur = cur->right;
      else
      {
        cur->right = new Node(obj);
        break;
      }
    }
    else
    {
      if (cur->left)  cur = cur->left;
      else
      {
        cur->left = new Node(obj);
        break;
      } 
    }
  }
}


/// @brief Метод для поиска всех объектов в бинарном дереве с заданным ключом
/// @param key Ключ, по которому ищутся объекты класса Object
/// @return Список объектов класса Object, чьи ключи совпали с искомым
std::vector<Object> BinaryTree::search (const std::string& key) const
{
  Node *cur = root;
  std::vector<Object> result;

  while ( cur )
  {
    if (cur->key() >= key)
    {
      if (cur->key() == key) result.push_back(cur->item);

      cur = cur->right;
    }
    else cur = cur->left;
  }

  return result;
}




/////////////////////////////////////////////
//          Красно-чёрное дерево           //
/////////////////////////////////////////////

/// @brief Конструктор узла красно-чёрного дерева по умолчанию
RBTree::Node::Node ()
: left(nullptr), right(nullptr), parent(nullptr), color(Black), empty(true) {}


/// @brief Конструктор узла красно-чёрного дерева
/// @param obj Объект класса Object, помещаемый в узел
RBTree::Node::Node (Object obj)
: left(new Node()), right(new Node()), parent(nullptr), color(Red), empty(false), item(obj) {}


/// @brief Деструктор узла красно-чёрного дерева
/// Рекурсивно удаляет все узлы-дети
RBTree::Node::~Node ()
{
  delete left;
  delete right;
}


/// @brief Метод для точечного удаления узла красно-чёрного дерева
void RBTree::Node::erase ()
{
  left = nullptr;
  right = nullptr;

  delete this;
}


/// @brief Метод для получения ключа хранимого объекта
/// @return Ключ хранимого объекта класса Object
std::string RBTree::Node::key () const
{
  return item.key();
}


/// @brief Метод для определения, является ли узел левым ребёнком родителя
/// @return Истина, если узел является левым ребёнком своего родителя
bool RBTree::Node::isLeft () const
{
  return this->parent->left == this;
}


/// @brief Метод для получения указателя на второго ребёнка родителя узла
/// @return Указатель на второго ребёнка родителя узла
RBTree::Node* RBTree::Node::sibling () const
{
  if (this->isLeft()) return this->parent->right;
  else                return this->parent->left;
}



/// @brief Конструктор красно-чёрного дерева по умолчанию
RBTree::RBTree ()
: root(nullptr) {}


/// @brief Конструктор красно-чёрного дерева по набору объектов класса Object
/// @param itemList Список объектов класса Object, которые помещаются в дерево при создании
RBTree::RBTree (const std::vector<Object>& itemList)
: root(nullptr)
{
  for (auto item : itemList)
  {
    this->insert(item);
  }
}


/// @brief Деструктор красно-чёрного дерева
RBTree::~RBTree ()
{
  delete root;
}


/// @brief Метод для совершения левого поворота вокруг узла красно-чёрного дерева
/// @param node Указатель на узел, вокруг которого происходит поворот
void RBTree::rotateLeft (Node* node)
{
  Node *child = node->right;
  
  // Узел -- внук  =>  узел -- сын
  node->right = child->left;
  child->left->parent = node;

  // Узел -- отец  =>  узел -- дед
  if (node == root)
    root = child;
  else
    if ( node->isLeft() )
      node->parent->left = child; 
    else  
      node->parent->right = child;
  
  child->parent = node->parent;

  // Узел -- сын   =>  узел -- отец
  child->left = node;
  node->parent = child;
}


/// @brief Метод для совершения правого поворота вокруг узла красно-чёрного дерева
/// @param node Указатель на узел, вокруг которого происходит поворот
void RBTree::rotateRight (Node* node)
{
  Node *child = node->left;
  
  // Узел -- внук  =>  узел -- сын
  node->left = child->right;
  child->right->parent = node;

  // Узел -- отец  =>  узел -- дед
  if ( node == root )
    root = child;
  else
    if ( node->isLeft() )
      node->parent->left = child;
    else
      node->parent->right = child; 

  child->parent = node->parent;

  // Узел -- сын   =>  узел -- отец
  child->right = node;
  node->parent = child;
}


/// @brief Метод для восстановления свойств красно-чёрного дерева
/// @param node Указатель на узел, относительно которого восстанавливаются свойства красно-чёрного дерева
void RBTree::balanceTree (Node* node)
{
  if (node == root || node->parent == root) 
  {
    root->color = Black;
    return;
  }

  Node *parent = node->parent, 
        *uncle = parent->sibling(), 
       *granpa = parent->parent;
  
  if (parent->color == Black) return;

  if (uncle->color == Red)
  {
    parent->color = Black;
    uncle->color  = Black;
    granpa->color = Red;

    balanceTree(granpa);
    return;
  }

  if (uncle->color == Black)
  {
    if ( node->isLeft() == parent->isLeft() )
    {
      parent->color = Black;
      granpa->color = Red;
      
      if (node->isLeft())
      {
        rotateRight(granpa);
        return;
      }
      else
      {
        rotateLeft(granpa);
        return;
      }
    }
    else
    {
      node->color = Black;
      granpa->color = Red;
      
      if (node->isLeft())
      {
        rotateRight(parent);
        rotateLeft(granpa);
        return;
      }
      else
      {
        rotateLeft(parent);
        rotateRight(granpa);
        return;
      }
    }
  }
}


/// @brief Метод для вставки нового объекта класса Object
/// @param obj Объект класса Object, помещаемый в красно-чёрное дерево
void RBTree::insert (const Object& obj)
{
  if (root == nullptr)
  {
    root = new Node(obj);
    balanceTree(root);
    return;
  }

  Node* cur = root;
  std::string key = obj.key();

  while ( cur )
  {
    
    if (cur->key() <= key)
    {
      if (!cur->right->empty)  cur = cur->right;
      else
      {
        cur->right->erase();
        cur->right = new Node(obj);
        cur->right->parent = cur;
        
        balanceTree(cur->right);
        break;
      }
    }
    else
    {
      if (!cur->left->empty)  cur = cur->left;
      else
      {
        cur->left->erase();
        cur->left = new Node(obj);
        cur->left->parent = cur;

        balanceTree(cur->left);
        break;
      } 
    }
  }
}


/// @brief Метод для поиска всех объектов в красно-чёрном дереве с заданным ключом
/// @param key Ключ, по которому ищутся объекты класса Object
/// @param node Указатель на узел, начиная с которого происходит поиск
/// @return Список объектов класса Object, чьи ключи совпали с искомым
std::vector<Object> RBTree::search (const std::string& key, Node* node) const
{
  Node *cur = (node ? node : root);
  std::vector<Object> result;
  

  if (cur->empty) return result;

  if ( cur->key() < key )
    return search(key, cur->right);
  else if ( cur->key() > key )
    return search(key, cur->left);
  else  
  {
    for (auto obj : search(key, cur->left))
    {
      result.push_back(obj);
    }
    
    result.push_back(cur->item);
    
    for (auto obj : search(key, cur->right))
    {
      result.push_back(obj);
    }
  }
    
  return result;
}




//////////////////////////////////////////////
//                Хеш-таблица               //
//////////////////////////////////////////////

/// @brief Конструктор узла хеш-таблицы
/// @param obj Объект класса Object, помещаемый в узел
HashTable::Node::Node (Object obj)
: next(nullptr), key(obj.key()), item(obj) {} 


/// @brief Деструктор узла хеш-таблицы
HashTable::Node::~Node ()
{
  delete next;
}


/// @brief Рекурсивный метод для вставки объекта класса Object в список
/// @param obj Объект класса Object, помещаемый в список
/// @return Истина, если в списке был встечен объект с тем же ключом
bool HashTable::Node::insert (const Object& obj)
{
  if ( next )
    return (next->insert(obj) | (key == obj.key()));
  else
    next = new Node(obj);
  return (key == obj.key());
}


/// @brief Рекурсивный метод для поиска объектов с заданным ключом
/// @param key Ключ, по которому ищутся объекты класса Object
/// @return Список объектов класса Object, чьи ключи совпали с искомым
std::vector<Object> HashTable::Node::search(const std::string& key) const
{
  std::vector<Object> result;
  
  if ( next )
    result = next->search(key);
  
  if ( this->key == key )
    result.push_back(item);
  
  return result;
}



/// @brief Конструктор хеш-таблицы по умолчанию
HashTable::HashTable ()
: table_size(1<<16), collisions(0), fullness(0)
{
  table.resize(table_size, nullptr);
}


/// @brief Конструктор хеш-таблицы по набору объектов класса Object
/// @param itemList Список объектов класса Object, которые помещаются в таблицу при создании
HashTable::HashTable (const std::vector<Object>& itemList)
: table_size(1<<16), collisions(0), fullness(0)
{
  table.resize(table_size, nullptr);

  for (auto item : itemList)
  {
    this->insert(item);
  }
}


/// @brief Деструктор хеш-таблицы
HashTable::~HashTable ()
{
  for (auto node : table)
  {
    delete node;
  }
}


/// @brief Хеш-функция
/// @param key Хешируемый ключ
/// @return Хеш-ключ
size_t HashTable::hashFunc (const std::string& key) const
{
  size_t hash = 1777; 
  size_t stride1 = 43, stride2 = 97;
  // int prev = 1;

  for (char ch : key)
  {
    // hash = hash*31 + ch*97 - prev*4;
    hash = hash*stride1 + ch*stride2;
    
    // prev = ch;
  }
  
  hash %= table_size;
  return hash;
}


/// @brief Метод для расширения хеш-таблицы
void HashTable::expandTable ()
{
  std::vector<Node*> temp = table;

  table_size *= 2;

  table.clear();
  table.resize(table_size, nullptr);

  collisions = 0;
  fullness   = 0;
  
  for (auto node : temp)
  {
    if (node)
    {
      while (node)
      {
        std::string key = node->key;
        Node* temp_node = node->next;
        node->next = nullptr;

        size_t hash = hashFunc(key);

        if ( table.at(hash) )
        {
          ++collisions;
          node->next = table.at(hash);
          table.at(hash) = node;
        }
        else
        {
          ++fullness;
          table.at(hash) = node;
        }

        node = temp_node;
      }
    }
  }
}


/// @brief Метод для вставки нового объекта класса Object
/// @param obj Объект класса Object, помещаемый в хеш-таблицу
void HashTable::insert (const Object& obj)
{
  std::string key = obj.key();
  size_t hash = hashFunc(key);

  while ( fullness == table_size )
    expandTable();

  if ( table.at(hash) )
  {
    if ( !(table.at(hash)->insert(obj)) )
      ++collisions;
  }
  else
  {
    table.at(hash) = new Node(obj);
    ++fullness;
  }
}


/// @brief Метод для поиска всех объектов в хеш-таблице с заданным ключом
/// @param key Ключ, по которому ищутся объекты класса Object
/// @return Список объектов класса Object, чьи ключи совпали с искомым
std::vector<Object> HashTable::search (const std::string& key) const
{
  size_t hash = hashFunc(key);

  if ( table.at(hash) )
    return table.at(hash)->search(key);
  else
    return {};
}


/// @brief Метод для получения количества возникших коллизий
/// @return Количество возникших коллизий
size_t HashTable::getCollisions () const
{ return collisions; }


/// @brief Метод для получения заполненности хеш-таблицы
/// @return Заполненность хеш-таблицы
size_t HashTable::getFullness () const
{ return fullness; }


/// @brief Метод для получения размера хеш-таблицы
/// @return Размер хеш-таблицы
size_t HashTable::getCapacity () const
{ return table_size; }

