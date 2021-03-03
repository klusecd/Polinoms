#include <iostream>

template<class T> class Node
{
public:
	Node *next;
	T data;
	Node(T data = T(), Node *next = nullptr) : data(data), next(next) {}
};

template<class T>
class List {
private:
	Node<T>* head;
	int size;
public:
	List() {
		head = nullptr;
		size = 0;
	}

	~List() { Clear(); }
	
	List(const List& lst): List() {
		head = nullptr;
		size = lst.size;
		Node<T>* current = head;
		for (Iterator iter = list.begin(); iter != list.end(); ++iter) {
			current = incert(iter->data, current);
		}
	}

	T GetFirst() { return head->data; }

	void Clear() {
		Iterator it = begin();
		while (it != end()) {
			Iterator tmp(it->next);
			delete* it;
			it = tmp;
		}
		head = nullptr;
		size = 0;
	}

	Node<T>* Push_front(T data) {
		Node<T>* tmp = new Node<T>(data, head);
		head = tmp;
		return tmp;
		size++;
	}
	
	Node<T>* Insert(T data, Node<T>* n) {
		if (n == nullptr) return Push_front(data);
		Node<T>* tmp = new Node<T>(data, n->next);
		n->next = tmp;
		return tmp;
		size++;
	}

	void Pop_front() {
		if (!size) { throw "list is empty"; }
		Node* tmp = head;
		head = tmp->next;
		delete tmp;
		size--;
	}

	void List<T>::Push_back(T d)
	{
		Node<T>* tmp = new Node<T>;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (Node<T>* last = new Node<T>)
		{
			last->data = d;
			last->next = NULL;
			tmp->next = last;
			size++;
		}
		else
			throw "Error: failed to allocate memory";
	}

	void PrintList() {
		for (Iterator iter = begin(); iter != end(); ++iter) {
			std::cout << iter.current->data << ' ';
		}
	}

	bool IsEmpty() {
		return head == nullptr;
	}

	class Iterator {
	private:
		Node<T>* current;
	public:
		Iterator() { current = head; }
		Iterator(Node<T>* n) { current = n; }
		Iterator(const Iterator& iter) { current = iter.current; }
		Node<T>*& operator*() { return current; }
		Node<T>*& operator->() { return current; }
		Iterator operator++() {
			if (current != nullptr)
				current = current->next;
			return *this;
		}
		bool operator==(const Iterator& iter) {
			return iter.current == current;
		}
		bool operator!=(const Iterator& iter) {
			return iter.current != current;
		}
	};

	Iterator begin() const {
		Iterator iter(head);
		return iter;
	}
	Iterator end() const {
		Iterator iter(nullptr);
		return iter;
	}

	void DeleteNextElem(Iterator iter) {
		if (iter != end()) {
			Iterator tmp(iter);
			++tmp;
			iter.current->next = tmp->next;
			delete tmp.current;
			size--;
		}
	}

	int GetSize()
	{
		return size;
	}
};