#include <iostream>
#include <cstdlib>
template <class T>
class StackLinkedList {
private:
	class Node {
	public:
		T item;
		Node* next;
		Node* prev;
	};

public:
	StackLinkedList() {
		first = nullptr;
		last = nullptr;
		size = 0;
	}
	
	void push(T item) {
		if (first) {
			last->next = (Node*)malloc(sizeof(Node));
			last->next->prev = last;
			last = last->next;
			last->item = item;
			last->next = nullptr;
			++size;
		} else {
			first = (Node*)malloc(sizeof(Node));
			last = first;
			last->item = item;
			last->next = nullptr;
			last->prev = nullptr;
			++size;
		}
	}
	
	T pop() {
		T item;
		item = last->item;
		Node *temp;
		temp = last;
		last = last->prev;
		free(temp);
		--size;
		return item;
	}
	
	int sizeOfStack() {
		return size;
	}
	
	/*typedef T* iterator;
	typedef const T* const_iterator;
	iterator begin() { return &(first->item); }
	iterator end() { return &arr[count]; }*/
private:
	Node *first;
	Node *last;
	int size;
};

int main() {
	StackLinkedList<std::string> stack = StackLinkedList<std::string>();
	for(std::string temp; std::cin>>temp;) {
		stack.push(temp);
	}
	std::cout<<"Printing...\n";
	
	while (stack.sizeOfStack() > 0) {
		std::cout<<stack.pop()<<"\n";
	}
}