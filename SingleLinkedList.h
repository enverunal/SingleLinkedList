#pragma once
#include <string>
#include <initializer_list>
#include <functional>
#include "llUtility.h"

namespace Single {
	template <typename T>
	struct node {
		T m_value{};
		node<T>* next{ nullptr };
	};
}


template <typename T>
class SingleLinkedList{
private:
	Single::node<T>* startPointer{};
	Single::node<T>* lastPointer{};
	int_fast64_t m_size{ 0 };
public:

	SingleLinkedList() noexcept;

	SingleLinkedList(std::initializer_list<T> init_list) noexcept;

	SingleLinkedList(int_fast64_t size);

	~SingleLinkedList() noexcept;

	int_fast64_t length() noexcept;

	T elementAt(int_fast64_t position) const;

	void append(const T& value);

	void append(std::initializer_list<T> init_list);

	void insert(const T& value, int_fast64_t position);

	void merge(const SingleLinkedList<T>& singleLinkedList) noexcept;

	void removeAt(int_fast64_t position);

	void removeValueFirst(const T& value) noexcept;

	void pop();

	T first() const;

	T last() const;

	bool contains(const T& value) noexcept;

	bool every(std::function<bool(const T& element)> test) const noexcept;

	void forEach(std::function<void(T &element)> function) noexcept;

	std::string join(const std::string &seperator = "") const noexcept;

	bool isEmpty() const noexcept;

	void clear()noexcept;

	std::string toString() const noexcept;

	bool operator==(const SingleLinkedList<T>& singleLinkedList) const noexcept;

};

template <typename T>
SingleLinkedList<T>::SingleLinkedList() noexcept {

}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(std::initializer_list<T> init_list)noexcept {
	for (auto i : init_list) {
		this->append(i);
	}
}

template <typename T>
SingleLinkedList<T>::SingleLinkedList(int_fast64_t size) {
	if (size < 0) {
		throw "size cannot be an negative number";
		return;
	}

	for (auto i{ 0 }; i < size; ++i) {
		if (i == 0) {
			Single::node<T>* newnode = new Single::node<T>();
			startPointer = newnode;
			lastPointer = newnode;
			++m_size;
		}
		else {
			Single::node<T>* newnode = new Single::node<T>();
			lastPointer->next = newnode;
			lastPointer = newnode;
			++m_size;
		}
	}
}

template <typename T>
SingleLinkedList<T>::~SingleLinkedList() noexcept {
	clear();
}

template <typename T>
void SingleLinkedList<T>::clear() noexcept {
	Single::node<T>* tempPointer{ nullptr };
	while (startPointer != nullptr) {
		tempPointer = startPointer;
		startPointer = startPointer->next;
		delete tempPointer;
	}
	startPointer = nullptr;
	lastPointer = nullptr;
	m_size = 0;
}

template <typename T>
int_fast64_t SingleLinkedList<T>::length() noexcept {
	return m_size;
}

template <typename T>
void SingleLinkedList<T>::append(const T& value) {
	if (m_size == INT_FAST64_MAX) {
		throw "maximum size has been reached already";
		return;
	}
	if (m_size == 0) {
		Single::node<T>* newnode = new Single::node<T>();
		newnode->m_value = value;
		startPointer = newnode;
		lastPointer = newnode;
		++m_size;
	}
	else {
		Single::node<T>* newnode = new Single::node<T>();
		newnode->m_value = value;
		lastPointer->next = newnode;
		lastPointer = newnode;
		++m_size;
	}
}

template <typename T>
void SingleLinkedList<T>::append(std::initializer_list<T> init_list) {
	if (static_cast<int_fast64_t>((m_size + init_list.size())) < m_size) {
		throw "maximum size has been reached already";
		return;
	}
	for (auto i : init_list) {
		this->append(i);
	}
}

template <typename T>
void SingleLinkedList<T>::removeValueFirst(const T& value) noexcept {
	Single::node<T>* tempPointer = startPointer;
	Single::node<T>* oneBefore = startPointer;
	for (auto i{ 0 }; i < m_size; ++i) {

		if (tempPointer->m_value == value) {
			/*if it is first value then you need to move startPointer*/
			if (i == 0) {
				if (m_size == 1) {
					startPointer = nullptr;
					lastPointer = nullptr;
				}
				else {
					startPointer = startPointer->next;
				}
				delete tempPointer;
				m_size -= 1;
				return;
			}
			/*if it is last value then you need to move lastPointer*/
			else if (tempPointer == lastPointer) {
				lastPointer = oneBefore;
				lastPointer->next = nullptr;
				delete tempPointer;
				m_size -= 1;
				return;
			}
			else {
				oneBefore->next = tempPointer->next;
				delete tempPointer;
				m_size -= 1;
				return;
			}
		}
		oneBefore = tempPointer;
		tempPointer = tempPointer->next;
	}
}

template <typename T>
void SingleLinkedList<T>::removeAt(int_fast64_t position) {
	if (position >= m_size || position < 0) {
		throw "unexcepted position";
		return;
	}
	Single::node<T>* tempPointer = startPointer;
	Single::node<T>* oneBefore = startPointer;
	if (position < m_size) {
		for (auto i{ 0 }; i < m_size; ++i) {
			if (position == 0) {
				startPointer = startPointer->next;
				delete tempPointer;
				m_size -= 1;
				return;
			}
			else if (i == position) {
				if (tempPointer == lastPointer) {
					lastPointer = oneBefore;
					lastPointer->next = nullptr;
					delete tempPointer;
					m_size -= 1;
					return;
				}
				else {
					oneBefore->next = tempPointer->next;
					delete tempPointer;
					m_size -= 1;
					return;
				}

			}
			oneBefore = tempPointer;
			tempPointer = tempPointer->next;

		}
	}
}

template <typename T>
void SingleLinkedList<T>::pop() {
	this->removeAt(m_size - 1);
}

template <typename T>
void SingleLinkedList<T>::insert(const T& value, int_fast64_t position) {
	if (position > m_size || position < 0) {
		throw "unexcepted position";
	}
	if (m_size == INT_FAST64_MAX) {
		throw "maximum size has been reached already";
	}

	Single::node<T>* tempPointer = startPointer;
	Single::node<T>* oneBefore = startPointer;
	if (m_size == 0) {
		Single::node<T>* newnode = new Single::node<T>();
		newnode->m_value = value;
		startPointer = newnode;
		lastPointer = newnode;
		++m_size;
		return;
	}
	else if (position == 0) {
		Single::node<T>* newnode = new Single::node<T>();
		newnode->m_value = value;
		newnode->next = startPointer;
		startPointer = newnode;
		++m_size;
		return;
	}
	else if (m_size == position) {
		Single::node<T>* newnode = new Single::node<T>();
		newnode->m_value = value;
		lastPointer->next = newnode;
		lastPointer = newnode;
		++m_size;
		return;
	}
	else {
		for (auto i{ 0 }; i < m_size; ++i) {
			if (position == i) {
				Single::node<T>* newnode = new Single::node<T>();
				oneBefore->next = newnode;
				newnode->next = tempPointer;
				newnode->m_value = value;
				++m_size;
				return;
			}
			oneBefore = tempPointer;
			tempPointer = tempPointer->next;
		}
	}
}

template <typename T>
void SingleLinkedList<T>::merge(const SingleLinkedList<T>& singleLinkedList) noexcept {
	Single::node<T>* tempPointer{ singleLinkedList.startPointer };
	for (auto i{ 0 }; i < singleLinkedList.m_size; ++i) {
		this->append(tempPointer->m_value);
		tempPointer = tempPointer->next;
	}
}

template <typename T>
T SingleLinkedList<T>::elementAt(int_fast64_t position) const {
	if (position >= m_size || position < 0) {
		throw "unexpected position";
	}
	Single::node<T>* temp{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		if (position == i) {
			return temp->m_value;
		}
		temp = temp->next;
	}
	throw "not found";
}

template <typename T>
bool SingleLinkedList<T>::contains(const T& value)noexcept {
	Single::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		if (tempPointer->m_value == value) {
			return true;
		}
		tempPointer = tempPointer->next;
	}
	return false;
}

template <typename T>
bool SingleLinkedList<T>::every(std::function<bool(const T& element)> test) const noexcept {
	Single::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		if (!test(tempPointer->m_value)) {
			return false;
		}
		tempPointer = tempPointer->next;
	}
	return true;
}

template <typename T>
void SingleLinkedList<T>::forEach(std::function<void(T& element)> function)noexcept {
	Single::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		function(tempPointer->m_value);
		tempPointer = tempPointer->next;
	}
}

template <typename T>
std::string SingleLinkedList<T>::join(const std::string& seperator) const noexcept {
	std::string join;
	join.reserve(m_size * (2 + seperator.size()));
	Single::node<T>* tempPointer{ startPointer };
	for (auto i{ 0 }; i < m_size; ++i) {
		join.append(llUtility::to_string(tempPointer->m_value) + seperator);
		tempPointer = tempPointer->next;
	}
	return join;
}

template <typename T>
T SingleLinkedList<T>::first() const {
	if (m_size > 0) {
		return startPointer->m_value;
	}
	else {
		throw "empty";
	}
}

template <typename T>
T SingleLinkedList<T>::last() const {
	if (m_size > 0) {
		return lastPointer->m_value;
	}
	else {
		throw "empty";
	}
}

template <typename T>
bool SingleLinkedList<T>::isEmpty() const noexcept {
	return m_size > 0 ? false : true;
}



template <typename T>
std::string SingleLinkedList<T>::toString() const noexcept {
	std::string result{};
	if (m_size == 0) {
		result = "-";
		return result;
	}
	else {
		result.reserve(m_size * 4);
		Single::node<T>* tempPointer = startPointer;
		for (auto i{ 0 }; i < m_size; ++i) {
			result.append(llUtility::to_string(tempPointer->m_value) + "->");
			tempPointer = tempPointer->next;
		}
		return result;
	}
}

template <typename T>
bool SingleLinkedList<T>::operator==(const SingleLinkedList<T>& singleLinkedList) const noexcept {
	if (this->m_size == singleLinkedList.m_size) {
		Single::node<T>* tempPointer1{ this->startPointer };
		Single::node<T>* tempPointer2{ singleLinkedList.startPointer };
		for (auto i{ 0 }; i < m_size; ++i) {
			if (tempPointer1->m_value != tempPointer2->m_value) {
				return false;
			}
			tempPointer1 = tempPointer1->next;
			tempPointer2 = tempPointer2->next;
		}
		return true;
	}
	else {
		return false;
	}
}

