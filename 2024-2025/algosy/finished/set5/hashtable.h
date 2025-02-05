#ifndef HASHTABLE_P1_RIP_H
#define HASHTABLE_P1_RIP_H
#include <vector>
#include <cstdint>
#include <iostream>

// Элемент хеш-таблицы - список объектов с одним хешем
template <class KeyType, class ValueType> struct Node {
  KeyType key;
  ValueType value;
  Node *next;

  Node(KeyType k, ValueType v) : key(k), value(v), next(nullptr) {}
};

// Хеш-таблица
template <class KeyType, class ValueType, class Func = std::hash<KeyType>>
class HashTable {
// private:
public:
  int _size;
  int _capacity;
  double _filled;
  Func _hashFunc;
  std::vector<Node<KeyType, ValueType>*> _table;

  void print() {
    for (size_t i = 0; i < _capacity; i++) {
      Node<KeyType, ValueType>* cur = _table.at(i);
      if (cur == nullptr) {
        std::cout << "-" << '\n';
      } else {
        while(cur) {
          std::cout << cur->key << " " << cur->value << '\t';
          cur = cur->next;
        }
        std::cout << '\n';
      }
    }
  }

  void nodeDelete(Node<KeyType, ValueType>* node) {
    if (node == nullptr) return;
    nodeDelete(node->next);
    delete node;
  }

  bool filledCheck() {
    double check = (double)_size / _capacity;
    return check > _filled;
  }

  void rehash() {
    std::vector<Node<KeyType, ValueType>*> bufer (_table);

    _table.clear();
    _size = 0;
    _capacity *= 2;
    _table.resize(_capacity, nullptr);
    for (size_t i = 0; i < bufer.size(); i++) {
      Node<KeyType, ValueType>* cur = bufer.at(i);
      while(cur) {
        insert(cur->key, cur->value);
        cur = cur->next;
      }
    }
    for (size_t i = 0; i < bufer.size(); i++) {
      nodeDelete(bufer[i]);
    }
    bufer.clear();
  }

public:
  HashTable() : _size(0), _capacity(100), _filled(0.5) {
    _table.clear();
    _table.resize(_capacity, nullptr);
  }

  HashTable(Func hfunc) : HashTable() {
    _hashFunc = hfunc;
  }

  HashTable(size_t ccapacity, double ffull, Func funn = Func()) : HashTable(funn) {
    _capacity = ccapacity;
    _table.resize(_capacity, nullptr);
    if (0 <= ffull && ffull <= 1) {
      _filled = ffull;
    }
  }

  ~HashTable() {
    for (size_t i = 0; i < _table.size(); i++) {
      nodeDelete(_table[i]);
    }
    _table.clear();
  }

  void insert(KeyType key, ValueType val) { // cst
    size_t ind = _hashFunc(key) % _capacity;
    if (_table[ind] == nullptr) {
      _table[ind] = new Node<KeyType, ValueType>(key, val);
    } else {
      Node<KeyType, ValueType>* cur = _table[ind];
      while(true) {
        // cur = cur->next;
        if (cur->key == key) {
          cur->value = val;
          return;
        }
        if (cur->next) { cur = cur->next; }
        else { break; }
      }
      cur->next = new Node<KeyType, ValueType>(key, val);
    }
    _size++;
    if (filledCheck()) rehash();
  }

  ValueType *find(KeyType key) {
    size_t ind = _hashFunc(key) % _capacity;
    if (_table[ind] == nullptr) {
      return nullptr;
    }
    Node<KeyType, ValueType>* cur = _table[ind];
    while(cur) {
      if (cur->key == key) {
        return &(cur->value);
      }
      cur = cur->next;
    }
    return nullptr;
  }

  void erase(KeyType key) {
    size_t ind = _hashFunc(key) % _capacity;
    if (_table[ind] == nullptr) {
      return;
    }
    Node<KeyType, ValueType>* cur = _table[ind];
    Node<KeyType, ValueType>* prev = nullptr;
    while(cur) {
      if (cur->key == key) {
        if (prev) {
          // todo check
          prev->next = cur->next;
        } else {
          _table[ind] = cur->next;
        }
        _size--;
        delete cur;
        break;
      }
      prev = cur;
      cur = cur->next;
    }
  }

  Node<KeyType, ValueType> &operator[](uint64_t ind) {
    if (ind >= _table.size()) {
      throw std::out_of_range("Index out of range");
    }
    if (_table[ind] == nullptr) {
      throw std::runtime_error("Null pointer encountered");
    }
    // Node<KeyType, ValueType>* res = _table.at(ind);
    return *(_table[ind]);
  }

  Node<KeyType, ValueType> at(uint64_t ind) {
    if (ind >= _table.size()) {
      throw std::out_of_range("Index out of range");
    }
    if (_table[ind] == nullptr) {
      throw std::runtime_error("Null pointer encountered");
    }
    return *_table[ind];
  }

  int size() const {
    return _size;
  }

  int capacity() const {
    return _capacity;
  }
};
#endif