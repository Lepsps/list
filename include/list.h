#ifndef LIST_H
#define LIST_H


template <typename T>
class list {
private:
	template <typename T>
	class Node {
	public:
		T data;
		Node* next;
		Node(T val = T(), Node* next = nullptr) : data(val), next(next) {}
	};

	Node<T>* head_elem = 0;
	int size = 0;
public:

	list(int n = 0) {
		if (n < 0) throw "Incorrect size";
		size = n;
		for (int i = 0; i < n; i++) {
			Node<T>* temp = new Node<T>(0, head_elem);
			head_elem = temp;
		}
	}

	list(const list& lst) {
		Node<T>* curr_elem = lst.head_elem;
		while (curr_elem != nullptr) {
			this->push_back(curr_elem->data);
			curr_elem = curr_elem->next;
		}
	}

	list(list&& lst) noexcept : size(lst.size), head_elem(lst.head_elem) {
		lst.size = 0;
		lst.head_elem = nullptr;
	}

	list& operator=(list&& lst) noexcept {
		size = lst.size;
		head_elem = lst.head_elem;
		lst.size = 0;
		lst.head_elem = nullptr;
		return *this;
	}

	list& operator=(const list& lst) {
		if (&lst == this)
			return *this;
		clear();
		Node<T>* curr_elem = lst.head_elem;
		while (curr_elem != nullptr) {
			this->push_back(curr_elem->data);
			curr_elem = curr_elem->next;
		}
		return *this;
	}

	void push_back(T data) {
		if (head_elem != nullptr) {
			Node<T>* curr_elem = head_elem;
			while (curr_elem->next != nullptr)
				curr_elem = curr_elem->next;
			curr_elem->next = new Node<T>(data);
		}
		else
			head_elem = new Node<T>(data);
		size++;
	}

	void pop_back() {
		if (!this->empty()) {
			if (size == 1)
				this->pop_front();
			else {
				Node<T>* curr_elem = head_elem;
				while (curr_elem->next->next != nullptr)
					curr_elem = curr_elem->next;
				delete curr_elem->next;
				curr_elem->next = nullptr;
			}
			size--;
		}
		else
			throw "Incorrect operation";
	}

	void clear() {
		if (!this->empty())
			while (size)
				this->pop_front();
	}

	bool empty() {
		return head_elem == nullptr;
	}

	int get_size() { return size; }

	~list() {
		clear();
	}

	template <typename T>
	class Iterator {
	public:
		Node<T>* curr = nullptr;
	public:

		Iterator(Node<T>* node) : curr(node) {}

		Node<T>& operator*() {
			return *(curr);
		}
		Node<T> operator*() const {
			return *(curr);
		}

		Iterator& operator++() {
			if (curr) {
				curr = curr->next;
			}
			return *this;
		}

		Iterator operator++(int) {
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const Iterator& it) const {
			return curr == it.curr;
		}

		bool operator!=(const Iterator& it) const {
			return curr != it.curr;
		}

	};

	using iterator = Iterator<T>;

	iterator begin() { return iterator(head_elem); }
	iterator end() { return iterator(nullptr); }

	iterator pop_front() {
		if (!this->empty()) {
			Node<T>* tmp = head_elem->next;
			delete head_elem;
			head_elem = tmp;
			size--;
			return iterator(head_elem);
		}
		else
			throw "Incorrect operation";
	}

	iterator push_front(T data) {
		head_elem = new Node<T>(data, head_elem);
		size++;
		return iterator(head_elem);
	}



	T& at(iterator it) { return (*it).data; }
	T at(iterator it) const { return (*it).data; }

	iterator insert(T data, iterator prev) {
		Node<T>* tmp = new Node<T>(data, nullptr);
		tmp->next = prev.curr->next;
		prev.curr->next = tmp;
		size++;
		return iterator(tmp);
	}

	iterator erase(iterator prev) {
		Node<T>* tmp = prev.curr->next;
		if (tmp) {
			prev.curr->next = prev.curr->next->next;
			delete tmp;
		}
		size--;
		return iterator(prev.curr->next);
	}

	iterator find(T data) {
		for (list<int>::iterator it = begin(); it != end(); it++) {
			if (this->at(it) == data)
				return iterator(it);
		}
		throw "Elem not found";
	}

};

#endif



