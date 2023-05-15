#pragma once
#include <cstring>

template <typename T>
struct QueueNode {
	T data;

	QueueNode<T>* next = nullptr;
};

template<typename T>
class Queue {
public:
	Queue();
	~Queue();

	const T& front() const;
	const T& back() const;

	std::size_t size() const;

	void push(const T& value);
	void pop();

private:
	QueueNode<T>* m_front, *m_back;

	std::size_t m_size;
};

template<typename T>
inline Queue<T>::Queue()
	: m_size(0), m_front(nullptr), m_back(nullptr)
{
}

template<typename T>
inline Queue<T>::~Queue()
{
	QueueNode<T>* node = m_back;
	while (node) {
		QueueNode<T>* nextNode = node->next;

		delete node;
		node = nextNode;
	}
}

template<typename T>
inline const T& Queue<T>::front() const
{
	return m_front->data;
}

template<typename T>
inline const T& Queue<T>::back() const
{
	return m_back->data;
}

template<typename T>
inline std::size_t Queue<T>::size() const
{
	return m_size;
}

template<typename T>
inline void Queue<T>::push(const T& value)
{
	m_size++;

	QueueNode<T>* newNode = new QueueNode<T>;
	newNode->data = value;

	if (!m_front) {
		m_front = newNode;
		m_back = newNode;

		return;
	}

	m_back->next = newNode;
	m_back = newNode;
}

template<typename T>
inline void Queue<T>::pop()
{
	if (!m_front) {
		return;
	}

	m_size--;

	QueueNode<T>* tmp = m_front->next;

	delete m_front;
	m_front = tmp;

	if (!m_front) {
		m_back = nullptr;
	}
}
