#include <iostream>
#include <vector>
#include <unordered_set>

class HashCuckooTable {
private:
  std::vector<int> table1;
  std::vector<int> table2;
  int size1;
  int size2;
  int capacity;
  std::unordered_set<int> cycleSearch1;
  std::unordered_set<int> cycleSearch2;

  int hash1(int key) { return key % capacity; }
  int hash2(int key) { return (key / capacity) % capacity; }

public:
  HashCuckooTable(int capacity) : capacity(capacity), size1(0), size2(0) {
    table1.resize(capacity, -1);
    table2.resize(capacity, -1);
  }

  bool h1(int key) {
    int idx = hash1(key);
    
    if (table1[idx] == -1) {
      table1[idx] = key;
      return true;
    } else {

      if (cycleSearch1.find(idx) == std::end(cycleSearch1)) {
        cycleSearch1.emplace(idx);
      } else {
        return false;
      }

      std::swap(key, table1[idx]);
      return h2(key);
    }
  }

  bool h2(int key) {
    int idx = hash2(key);
    
    if (table2[idx] == -1) {
      table2[idx] = key;
      return true;
    } else {

      if (cycleSearch2.find(idx) == std::end(cycleSearch2)) {
        cycleSearch2.emplace(idx);
      } else {
        return false;
      }

      std::swap(key, table2[idx]);
      return h1(key);
    }
  }

  bool insert(int key) {
    if (size1 + size2 == 2 * capacity) {
      std::cout << "Hash Table is full\n";
      return false;
    }

    while (true) {
      cycleSearch1.clear();
      cycleSearch2.clear();
      if (h1(key)) {
        return true;
      }
      cycleSearch1.clear();
      cycleSearch2.clear();
      if (h2(key)) {
        return true;
      }

      std::cout << "cycle found. Rehash!\n";
      rehash();
    }
  }

  bool rehash() {
    std::vector<int> readd;
    for (int i = 0; i < capacity; i++) {
      if (table1[i] != -1) readd.push_back(table1[i]);
      if (table2[i] != -1) readd.push_back(table2[i]);
    }
    capacity++;
    table1.clear();
    table1.resize(capacity, -1);
    table2.clear();
    table2.resize(capacity, -1);
    // если при рехешировании снова цикл, еще раз перехешируем.
    while(true) {
      bool flag = false;
      for (int i = 0; i < readd.size(); i++) {
        if (!insert(readd[i])) {
          capacity++;
          table1.clear();
          table1.resize(capacity, -1);
          table2.clear();
          table2.resize(capacity, -1);
          flag = true;
        }
      }
      if (flag) continue;
      break;
    }
    
    return true;
  }

  int search(int key) {
    if (table1[hash1(key)] == key) return hash1(key);
    if (table2[hash2(key)] == key) return hash2(key);
    return -1;
  }

  void printTable() {
    for (int i = 0; i < capacity; ++i) {
      std::cout << table1[i] << ' ';
    }
    std::cout << '\n';
    for (int i = 0; i < capacity; ++i) {
      std::cout << table2[i] << ' ';
    }
    std::cout << '\n';
  }
};

int main() {
  HashCuckooTable hashTable(11);

  // Вставка элементов
  // hashTable.insert(20);
  // hashTable.insert(50);
  // hashTable.insert(53);
  // hashTable.insert(75);
  // hashTable.insert(100);
  // hashTable.insert(67);
  // hashTable.insert(105);
  // hashTable.insert(3);
  // hashTable.insert(36);
  // hashTable.insert(39);
  // hashTable.insert(6);

  std::vector<int> arr {20, 50, 53, 75, 100, 67, 105, 3, 36, 39};
  for (int i = 0; i < arr.size(); i++) {
    hashTable.insert(arr[i]);
  }

  // hashTable.printTable();

  std::cout << hashTable.search(20) << '\n';
  std::cout << hashTable.search(21) << '\n';
  // std::cout << hashTable.deleteKey(12) << '\n';
  // std::cout << hashTable.search(12) << '\n';

  hashTable.printTable();

  return 0;
}
