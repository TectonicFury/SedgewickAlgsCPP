#include <iostream>
#include <algorithm>
namespace AMA {
  template <typename T>
  class LinkedList {
  private:
    class Node;
  public:
    class Iterator; //to return iterator objects using function begin() and end()

    LinkedList() {
      first = nullptr;
      last = nullptr;
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
      } else {
        first = new Node(t, nullptr, nullptr);
        last = first;
      }
    }

    void push_front(T t) {
      if (first != nullptr) {
        Node *n = new Node(t, nullptr, first);
        first->prev = n;
        first = n;
      } else {
        first = new Node(t, nullptr, nullptr);
        last = first;
      }
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
  AMA::LinkedList<int> lst;
  lst.push_back(100); lst.push_back(10000); lst.push_back(100000);

  for (auto& i : lst) {
    std::cout<<i<<"\n";
  }

  if (std::find(lst.begin(), lst.end(), 100) != lst.end()) {
    std::cout << "الحمد لله" << '\n';
  }
  return 0;
}
