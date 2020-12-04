#include<iostream>
#include<string>
#include<array>
#include<cstdlib>
#include<vector>
#include<optional>

namespace AMA {
	template <typename T> //templates are a compile time mechanism, no runtime overhead
	class Stack {
	public:
		Stack(int capacity) {
			maxLen = capacity;
			_size = 0;
			arr = new T[capacity];
			std::cout << "capacity = " << capacity << " maxLen = " << maxLen << '\n';
		}

		Stack(): Stack(10) {} //default constructor

		Stack(const Stack& st):_size{st._size}, arr{new T[st._size]}, maxLen{st.maxLen}  { //copy constructor
			for (int i = 0; i < _size; i++) {
				arr[i] = st.arr[i];
			}
		}

		Stack& operator=(const Stack& st) { //copy assignment
			T* temp = new T[st._size];
			for (int i = 0; i < st._size; i++) {
				temp[i] = st.arr[i];
			}
			delete[] arr;
			arr = temp;
			_size = st._size;
			maxLen = st.maxLen;
			return *this;
		}

		Stack(Stack&& st): arr{st.arr}, _size{st._size}, maxLen{st.maxLen} { //move constructor
			st.arr = nullptr;
			st._size = 0;
		}

		Stack& operator=(Stack&& st) { //move assignment
			delete[] arr;
			arr = st.arr;
			st.arr = nullptr;
			_size = st._size;
			st._size = 0;
			maxLen = st.maxLen;
			return *this;
		}

		~Stack() { //destructor
			delete[] arr;
			_size = 0;
			maxLen = 0;
		}

		void push(T s) {
			if (_size < maxLen) {
				arr[_size++] = s;
			} else {
				maxLen = 2 * maxLen;
				resize(maxLen);
				arr[_size++] = s;
			}
		}

		T* pop() {
			if (_size > 0) {
				if (_size < maxLen/4) {
					maxLen = maxLen/2;
					resize(maxLen);
				}
				return &arr[--_size];
			}

			return nullptr;
		}
		unsigned long long printAddress() {
			return (unsigned long long)arr;
		}
		int size() {
			return _size;
		}

		bool isEmpty() {
			return _size == 0;
		}

		T* begin() {
			if (_size > 0) return &arr[0];
			return nullptr;
		}

		T* end() {
			if (_size > 0) return &arr[0] + _size;
			return nullptr;
		}

	private:
		void resize(int max) {
			arrTemp = new T[max];
			if (arrTemp != nullptr) {
				for (int i = 0; i < _size; i++) {
					arrTemp[i] = arr[i];
				}
				delete[] arr;
				arr = arrTemp;
			} else {
				std::cout<<"MEMORY ERROR\n";
			}
		}

		T *arr;
		T *arrTemp;
		int _size;
		int maxLen;
	};
}

int main() {
	AMA::Stack<std::string> fs(10000);
	std::string in;
	AMA::Stack<std::string> fs2 = fs;
	std::cout << fs.printAddress() << " ### " << fs2.printAddress() << '\n';
	fs2 = fs;
	std::cout << "!!!" << fs2.printAddress() << '\n';
	while (true) {
		std::cin>>in;
		if (in == "EXIT_C0dE") break;
		if (in == "-") {
			if (auto a = fs.pop()) {
				std::cout<<*a<<" ";
			}

		} else {
			fs.push(in);
		}
	}
	std::cout << "here" << '\n';
	//AMA::Stack<std::string> fs2;
	std::cout << fs.printAddress() << " ### " << fs2.printAddress() << '\n';
	fs2 = std::move(fs);
	std::cout << fs.printAddress() << " ### " << fs2.printAddress() << '\n';
	fs.~Stack();

	std::cout << "\n****printing fs2****" << '\n';
	for (auto&i : fs2) {
		std::cout << i << '\n';
	}
	std::cout<<"\nInput Ends\n";

	std::cout<<"Size = "<<fs.size()<<"\n";

	for (auto& i : fs) {
		i += "hi";
	}

	for (auto i : fs) {
		std::cout<<"Here is << "<<i<<"\n";
	}

	if (auto a = fs.pop()) {
		std::cout<<"Subhaan Allaah!"<<std::endl;
	} else {
		std::cout<<"Allaah u Akbar!"<<std::endl;
	}
}
