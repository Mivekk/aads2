#pragma once
#include "Vector.h"

template<typename T>
class PriorityQueue {
public:
	PriorityQueue();
	~PriorityQueue();
	
	const T& top() const;

	std::size_t size() const;

	void push(const T& value);
	void pop();

private:
	Vector<T> data;
};

template<typename T>
inline PriorityQueue<T>::PriorityQueue()
{
}

template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
}

template<typename T>
inline const T& PriorityQueue<T>::top() const
{
	if (!data.size()) {
		return T();
	}

	return data[0];
}

template<typename T>
inline std::size_t PriorityQueue<T>::size() const
{
	return data.size();
}

template<typename T>
inline void PriorityQueue<T>::push(const T& value)
{
	data.push_back(value);

	int index = data.size() - 1;
	int parent = (index - 1) / 2;

	while (index > 0 && data[index] < data[parent]) {
		swap(data[index], data[parent]);

		index = parent;
		parent = (index - 1) / 2;
	}
}

template<typename T>
inline void PriorityQueue<T>::pop()
{
	if (!data.size()) {
		return;
	}

	swap(data[0], data[data.size() - 1]);
	data.pop_back();

	int index = 0;
	int smaller = 0;
	while (true) {
		int leftIndex = 2 * index + 1;
		int rightIndex = 2 * index + 2;

		if (leftIndex < data.size() && data[leftIndex] < data[smaller]) {
			smaller = leftIndex;
		}
		if (rightIndex < data.size() && data[rightIndex] < data[smaller]) {
			smaller = rightIndex;
		}

		if (smaller == index) {
			break;
		}

		swap(data[index], data[smaller]);
		index = smaller;
	}
}
