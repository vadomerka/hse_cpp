#include <iostream>
#include <vector>
#include <exception>


class MyArr {
public:
  MyArr(int capacity) : _size(0), _capacity(capacity), _arr(new int[capacity]) {}

public:
  void push_back(int num) {
    if (_capacity == _size) {
      _capacity *= 2;
      int* old = _arr;
      _arr = new int[_capacity];
      std::copy(old, old + _size, _arr);
    }
    _arr[_size++] = num;
  }

  int pop_back() {
    return _arr[_size-- - 1];
  }

int operator[](int i) {
  if (i < 0 || i >= _size) {
    throw std::exception();
  }
  return *(_arr + i);
}

int size() {
  return _size;
}

int capacity() {
  return _capacity;
}

public:
  void Print() {
    for (size_t i = 0; i < _size; i++) {
      std::cout << _arr[i] << " ";
    }
    std::cout << '\n';
  }

private:
  int* _arr;
  size_t _capacity = 0;
  size_t _size = 0;
};


int main() {
  int aa[] = {1, 2, 4, 5};
  MyArr v (5);
  v.push_back(5);
  v.push_back(6);
  v.push_back(7);
  v.push_back(8);
  v.push_back(9);
  v.push_back(10);
  v.push_back(11);
  v.push_back(12);
  v.Print();

  std::cout << "size: " << v.size() << std::endl;
 
  // Print Element at index 2
  std::cout << "v[2]: " << v[2] << '\n';

  // Pop an element and print it
  std::cout << "Popped Element: " << v.pop_back() << '\n';
  v.Print();
  return 0;
}