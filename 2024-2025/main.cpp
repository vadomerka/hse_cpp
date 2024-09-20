#include <iostream>
#include <vector>
#include <exception>

class MyArr {
public:
  MyArr(int capacity = 0) : _size(0), _capacity(capacity), _arr(new int[capacity]) {}

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

size_t size() {
  return _size;
}

size_t capacity() {
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

class MyStack {
 public:
  MyStack() : arr {}
  {}

  MyStack(int N) {
    for (size_t i = 0; i < N; i++) {
      arr.push_back(0);
    }
  }

  MyStack(int N, int nArr[]) {
    for (size_t i = 0; i < N; i++) {
      arr.push_back(nArr[i]);
    }
  }

  MyStack(std::vector<int> nArr) {
    for (size_t i = 0; i < nArr.size(); i++) {
      arr.push_back(nArr[i]);
    }
  }

 public:
  int operator[] (size_t i) {
    return arr[i];
  }

  size_t Size() {
    return arr.size();
  }

 public:
  void Push(int num) {
    arr.push_back(num);
  }

  int Pop() {
    if (arr.size() < 1) {
      throw std::exception();
    }
    int ret = arr[arr.size() - 1];
    arr.pop_back();
    return ret;
  }

 public:
  void Print() {
    for (size_t i = 0; i < arr.size(); i++) {
      std::cout << arr[i] << " ";
    }
    std::cout << '\n';
  }
 private:
  MyArr arr;
};

class MyQueue {
 public:
  MyQueue(std::vector<int> nArr) {
    for (size_t i = 0; i < nArr.size(); i++) {
      stk1.Push(nArr[i]);
    }
  }

 public:
  void Push(int num) {
    stk1.Push(num);
  }

  int Pop() {
    if (stk2.Size() > 0) {
      return stk2.Pop();
    }
    size_t len = stk1.Size();
    for (size_t i = 0; i < len; i++) {
      stk2.Push(stk1.Pop());
    }
    return stk2.Pop();
  }

 public:
  void Print() {
    if (stk2.Size() > 0) {
      for (int i = stk2.Size() - 1; i >= 0; i--) {
        std::cout << stk2[i] << " ";
      }
    }
    for (int i = 0; i < stk1.Size(); i++) {
      std::cout << stk1[i] << " ";
    }
    std::cout << '\n';
  }
 private:
  MyStack stk1;
  MyStack stk2;
};

int main() {
  std::vector<int> aa {1, 2, 3, 4};
  MyQueue a1 {aa};
  a1.Print();
  a1.Push(5);
  a1.Print();
  a1.Pop();
  a1.Print();
  return 0;
}