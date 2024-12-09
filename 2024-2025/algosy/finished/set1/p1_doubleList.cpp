#include <stdexcept>
#include "doubleList.h"
#include <map>

List::List() : head(nullptr), tail(nullptr), _size(0) {}

List::List(const List& other) : List() {
    Node* itElem = other.head;
    while(itElem->next) {
      push_back(itElem->value);
      itElem = itElem->next;
    }
    push_back(itElem->value);
  }

List::List(std::vector<int> array) : List() {
    if (array.size() == 0) return;
    for (size_t i = 0; i < array.size(); i++) {
        push_back(array[i]);
    }
}

List::~List() {
    clear();
}

int List::front() {
    if (!head) return 0;
    return head->value;
}

int List::back() {
    if (!tail) return 0;
    return tail->value;
}

void List::push_back(int value)  {
    if (empty()) {
        head = new Node {value};
        tail = head;
        _size++;
        return;
    }
    tail->next = new Node {value};
    tail->next->prev = tail;
    tail = tail->next;
    _size++;
    if (_size == 2) {
        head->next = tail;
        tail->prev = head;
    }
}

void List::push_front(int value) {
    if (empty()) {
        head = new Node {value};
        tail = head;
        _size++;
        return;
    }
    head->prev = new Node {value};
    head->prev->next = head;
    head = head->prev;
    _size++;
    if (_size == 2) {
        head->next = tail;
        tail->prev = head;
    }
}

void List::insert(Node* pos, int value) {
    if (!pos || pos == tail) {
        throw std::runtime_error("Incorrect position!");
    }
    Node *tmp = pos->next;
    pos->next = new Node(value);
    pos->next->next = tmp;
    tmp->prev = pos->next;
    _size++;
}

void List::pop_front() {
    if (empty()) std::runtime_error("Deleting in empty list");
    if (_size == 1) {
        delete[] head;
        head = nullptr;
        tail = nullptr;
        _size--;
        return;
    }
    Node *tmp = head->next;
    delete[] head;
    head = tmp;
    head->prev = nullptr;
    _size--;
    if (_size == 1) {
        head->prev = nullptr;
        tail->prev = nullptr;
    }
}

void List::pop_back() {
    if (empty()) std::runtime_error("Deleting in empty list");
    if (_size == 1) {
        delete[] head;
        head = nullptr;
        tail = nullptr;
        _size--;
        return;
    }
    Node *tmp = tail->prev;
    delete[] tail;
    tail = tmp;
    tail->next = nullptr;
    _size--;
    if (_size == 1) {
        head->prev = nullptr;
        tail->prev = nullptr;
    }
}

void List::erase(Node* pos) {
    if (!pos) {
        throw std::runtime_error("Incorrect position!");
    }
    if (pos == head) {
        pop_front();
        return;
    } 
    if (pos == tail) {
        pop_back();
        return;
    }
    pos->prev->next = pos->next;
    pos->next->prev = pos->prev;
    delete[] pos;
    _size--;
}

void List::clear() {
    while(head) {
        pop_front();
    }
}

void List::reverse() {
    if (_size <= 1) return;
    tail->next = head;
    head->prev = tail;

    head = tail;
    tail = tail->prev;

    tail->next = nullptr;
    head->prev = nullptr;
    
    
    Node *prevN = head;
    while (tail != prevN->next) {
        
        Node *nextN = prevN->next;
        Node *prevT = tail->prev;

        prevN->next = tail;
        tail->prev = prevN;
        nextN->prev = tail;
        tail->next = nextN;
        prevN = tail;

        prevT->next = nullptr;
        tail = prevT;
    }
}

void List::remove_duplicates() {
    if (!_size || _size == 1) return;
    Node *curN = head;
    std::map<int, int> mp;
    while (curN) {
        if (mp.find(curN->value) == mp.end()) {
            mp[curN->value] = 1;
        } else {
            mp[curN->value]++;
        }
        
        Node *tmp = curN->next;
        if (mp[curN->value] > 1) {
            erase(curN);
        }

        curN = tmp;
    }
}

void List::replace(int old_value, int new_value) {
    Node *curN = head;
    while (curN) {
        if (curN->value == old_value) {
            curN->value = new_value;
        }
        curN = curN->next;
    }
}

void List::merge(const List& other) {
    Node *curN = other.head;
    size_t startSize = other._size;
    for (size_t i = 0; i < startSize; i++) {
        push_back(curN->value);
        curN = curN->next;
    }
}

bool List::check_cycle() const {
    Node* fast = head;
    Node* slow = head;
    do {
       if (!fast || !fast->next) return false;
       fast = fast->next->next;
       slow = slow->next; 
    } while (fast != slow);
    return true;
}

size_t List::size() const {
    return _size;
}

bool List::empty() const {
    return _size == 0;
}

void List::copy(const List& other) {
    /*
    Node *curN = head;
    Node *othN = other.head;
    for (int i = 0; i < other._size; i++) {
        if (i < _size) {
            curN->value = othN->value;    
            curN = curN->next;
        } else {
            push_back(othN->value);
        }

        othN = othN->next;
    }
    */
    clear();
    Node *curN = other.head;
    while (curN) {
        push_back(curN->value);

        curN = curN->next;
    }
}
