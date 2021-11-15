#ifndef CS20A_LIST_H
#define CS20A_LIST_H

#include<iostream>
#include<assert.h>

template<typename Item>
class List {
public:

	List();

	List(const List<Item>& other);

	List<Item>& operator=(const List<Item>& other);

	~List();

	void	print() const;
	bool	empty() const;

	void	push_front(const Item &item);
	void	push_rear(const Item &item);
	void	insert(int index, const Item &item);


	Item	front() const;
	Item	rear() const;
	Item	get(int index) const;

	int		size() const;
	int		find(const Item &item) const;

	bool	pop_front();
	bool	pop_rear();
	bool	remove(int index);

#ifndef MAKE_MEMBERS_PUBLIC
private:
#endif

	class Node;

	Node*	m_head;
	Node*	m_tail;

	int		m_size;
};



template<typename Item>
struct List<Item>::Node {
	Node() :next(nullptr), prev(nullptr) {}
	Node(Item it, Node* p, Node* n) : item(it), next(n), prev(p) {}

	Item  item;
	Node* next;
	Node* prev;
};


template<typename Item>
List<Item>::List() :m_head(nullptr), m_tail(nullptr), m_size(0) {
}

/* Copy constructor  
*/
template<typename Item>
List<Item>::List(const List<Item>& other) {
	if (other.m_head == nullptr) { m_head = nullptr; }
	else {
		Node* original_node = other.m_head;
		Node* copy_node = new Node;
		copy_node->item = original_node->item;
		copy_node->next = nullptr;
		copy_node->prev = nullptr;
		m_head = copy_node;
		original_node = original_node->next;
		int iterator = 0;

		while (iterator != (m_size - 1)) {
			Node* new_node = new Node;
			new_node->item = original_node->item;
			new_node->next = nullptr;
			copy_node->next = new_node;
			new_node->prev = copy_node;
			original_node = original_node->next;
			copy_node = copy_node->next;
			m_tail = copy_node;
			iterator++;
		}
	}
}
/* Overloaded assignment operator 
*/
template<typename Item>
List<Item>& List<Item>::operator=(const List<Item>& other) {
	if (this == &other) return *this;

	int iterator = 0;
	Node* current_node = m_head;
	while (iterator != m_size) {
		Node* next_node = current_node->next;
		delete current_node;
		current_node = next_node;
		iterator++;
	}

	m_size = other.m_size;

	if (other.m_head == nullptr) { m_head = nullptr; }
	else {
		Node* original_node = other.m_head;
		Node* copy_node = new Node;
		copy_node->item = original_node->item;
		copy_node->next = nullptr;
		copy_node->prev = nullptr;
		m_head = copy_node;
		original_node = original_node->next;
		int iterator = 0;

		while (iterator != (m_size - 1)) {
			Node* new_node = new Node;
			new_node->item = original_node->item;
			new_node->next = nullptr;
			copy_node->next = new_node;
			new_node->prev = copy_node;
			original_node = original_node->next;
			copy_node = copy_node->next;
			m_tail = copy_node;
			iterator++;
		}
	}
	return *this;
}


/* List destructor
*/
template<typename Item>
List<Item>::~List() {
	int iterator = 0;
	Node* delete_this = m_head;
	while (iterator != m_size) {
		m_head = m_head->next;
		delete delete_this;
		delete_this = m_head;
		iterator++;
	}
}

/* List print
*/		
template<typename Item>
void List<Item>::print() const {
	Node* temp;
	temp = m_head;
	while (temp != nullptr) {
		std::cout << temp->item << std::endl;
		temp = temp->next;
	}
}

/* List empty
*/
template<typename Item>
bool List<Item>::empty() const {
	if (m_head == nullptr) { return false; }
	else return true;
}


/* List push_front
*/
template<typename Item>
void List<Item>::push_front(const Item &item) {
	if (m_head == nullptr) {
		Node* current_node;
		current_node = new Node;
		current_node->item = item;
		current_node->next = m_head;
		current_node->prev = m_tail;
		m_head = current_node;
		m_tail = current_node;
		m_size++;
	}
	else {
		Node* current_node = new Node;
		current_node->item = item;
		current_node->next = m_head;
		current_node->prev = nullptr;
		m_head->prev = current_node;
		m_head = current_node;
		m_size++;
	}
}

/* List push_rear
*/
template<typename Item>
void List<Item>::push_rear(const Item &item) {
	if (m_head == nullptr) { push_front(item); }
	else {
		Node* current_node = new Node;
		current_node->item = item;
		current_node->prev = m_tail;
		current_node->next = nullptr;
		m_tail->next = current_node;
		m_tail = current_node;
		m_size++;
	}
}

/* List insert
*/
template<typename Item>
void List<Item>::insert(int index, const Item &item) {
	if (index < 0 || index == 0) { push_front(Item); m_size++; }
	else if (index > m_size || index == m_size) { push_rear(Item); m_size++; }
	else {
		int iterator = 0;

		Node* current_node = m_head;
		while (iterator != index) {
			current_node = current_node->next;
			iterator++;
		}
		Node* new_node = new Node;
		Node* top_node = current_node->prev;
		Node* bottom_node = current_node;
		new_node->item = Item;
		new_node->prev = top_node;
		new_node->next = bottom_node;
		top_node->next = new_node;
		bottom_node->prev = new_node;
		m_size++;
	}
}

/*  List front
*/
template<typename Item>
Item List<Item>::front() const {
	assert(m_head != nullptr); 
	Node* current_node = m_head;
	return current_node->item;
}

/* List rear
*/
template<typename Item>
Item List<Item>::rear() const {

	assert(m_tail != nullptr);
	Node* current_node = m_tail;
	return current_node->item;
}

/* List get
//		returns the item at index
*/
template<typename Item>
Item List<Item>::get(int index) const {

	assert(index >= 0 && index < m_size);

	int iterator = 0;
	Node* current_node = m_head;
	while (iterator != index) { current_node = current_node->next; iterator++; }
	return current_node->item;
}

/* List size
*/
template<typename Item>
int List<Item>::size() const {
	return m_size;
}

/* List find
*/
template<typename Item>
int List<Item>::find(const Item &item) const {

	Node* current_node = m_head;
	int current_index = 0;
	while (current_node != nullptr) {
		if (current_node->item == item) { return current_index; }
		current_node = current_node->next;
		current_index++;
	}
	return -1;
}

/* List pop_front
*/		
template<typename Item>
bool List<Item>::pop_front() {

	if (m_head == nullptr) {
		std::cout << "there's nothing in the list" << std::endl;
		return false;
	}
	else {
		Node* delete_this = m_head;
		m_head = m_head->next;
		m_head->prev = nullptr;
		delete delete_this;
		m_size--;
		return true;
	}
}

/* List pop_rear
*/	
template<typename Item>
bool List<Item>::pop_rear() {
	if (m_head == nullptr) {
		std::cout << "there's nothing in the list" << std::endl;
		return false;
	}
	else {
		Node* delete_this = m_tail;
		m_tail = m_tail->prev;
		m_tail->next = nullptr;
		delete delete_this;
		m_size--;
		return true;
	}
}

/* List remove
*/
template<typename Item>
bool List<Item>::remove(int index) {

	if (index > m_size - 1 || index < 0) { return false; }

	// OR
	// if(index > m_size - 1){ index = m_size - 1; } 
	// else if(index < 0) { index = 0; }

	if (m_head == nullptr) { return false; }
	else {
		if (index == m_size - 1) {
			pop_rear();
			return true;
		}
		else if (index == 0) {
			pop_front();
			return true;
		}
		else {
			Node* current_node = m_head;
			int iterator = 0;
			while (iterator != index) {
				current_node = current_node->next;
				iterator++;
			}
			Node* top_node = current_node->prev;
			Node* bottom_node = current_node->next;
			top_node->next = bottom_node;
			bottom_node->prev = top_node;
			delete current_node;
			m_size--;
			return true;
		}
	}
}

#endif