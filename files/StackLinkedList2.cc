#include <iostream>
#include <string>
#include <algorithm>
namespace AMA {
  template <typename T>
  class StackLinkedList {
  private:
    class Node;
  public:
    class Iterator; //to return iterator objects using function begin() and end()

    StackLinkedList() {
      first = nullptr;
      last = nullptr;
      _size = 0;
    }

    Iterator begin() {
      return Iterator(first);
    }

    Iterator end() {
      return Iterator(nullptr);
    }

    void push_back(T t) {
      if (first != nullptr) {
        Node *n = new Node(t, last, nullptr);
        last->next = n;
        last = n;
        ++_size;
      } else {
        first = new Node(t, nullptr, nullptr);
        last = first;
        ++_size;
      }
    }

    T* pop_back() {
      if (_size > 0) {
        Node* lastNode = last;
        last = last->prev;
        last->next = nullptr;
        --_size;
        return &(lastNode->value);
      }
      return nullptr;
    }

    int size() {
      return _size;
    }
    class Iterator { //iterator class
      Node* current;
    public:
      Iterator(Node* p) : current{p} {
      }
      T& operator*() {
        return current->value;
      }
      Iterator& operator++() {
        current = current->next;
        return *this;
      }

      bool operator!=(const Iterator& it) {
        return (this->current != it.current);
      }
    };

  private:
    Node* first;
    Node* last;
    int _size;
    class Node { //private class Node
    public:
      Node(T t, Node* _prev, Node* _next) : value{t}, prev{_prev}, next{_next} {}
      T value;
      Node* prev;
      Node* next;
    };
  };
}

int main(int argc, char const *argv[]) {
  AMA::StackLinkedList<std::string> lst;
  std::string str;

  for (size_t i = 0; i < 4; i++) {
    std::cin >> str;
    lst.push_back(str);
  }

  for (auto& i : lst) {
    std::cout<<i<<"\n";
  }

  if (std::find(lst.begin(), lst.end(), "Ahmad") != lst.end()) {
    std::cout << "الحمد لله" << '\n';
  } else {
    std::cout << "الله اكبر" << '\n';
  }

  std::cout << "here" << '\n';

  for (auto p = lst.begin(); p != lst.end(); ++p) {
    std::cout << *p << '\n';
  }
  return 0;
}
