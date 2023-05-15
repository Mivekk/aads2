#pragma once
#include <cstring>

template<typename T>
class Vector
{
public:
	Vector();
	Vector(const Vector& other);
	Vector(std::size_t size);
	Vector(std::size_t size, const T& value);
	~Vector();

	std::size_t size() const;
	std::size_t capacity() const;

	void push_back(const T& element);
	void pop_back();
	void resize(std::size_t newSize);

	T& operator[](int idx);
	const T& operator[](int idx) const;

	Vector<T>& operator=(const Vector& other);

private:
	T* m_arr;

	std::size_t m_size;
	std::size_t m_capacity;
};

template<typename T>
inline Vector<T>::Vector()
	: m_arr(new T[1]), m_size(0), m_capacity(1)
{
}

template<typename T>
inline Vector<T>::Vector(const Vector& other)
	: m_arr(new T[other.m_size]), m_size(other.m_size), m_capacity(other.m_capacity)
{
	for (int i = 0; i < m_size; i++) {
		m_arr[i] = other.m_arr[i];
	}
}

template<typename T>
inline Vector<T>::Vector(std::size_t size)
	: m_arr(new T[size]), m_size(size), m_capacity(size)
{
}

template<typename T>
inline Vector<T>::Vector(std::size_t size, const T& value)
	: m_arr(new T[size]), m_size(size), m_capacity(size)
{
	for (int i = 0; i < size; i++) {
		m_arr[i] = value;
	}
}

template<typename T>
inline Vector<T>::~Vector()
{
	delete[] m_arr;
}

template<typename T>
inline std::size_t Vector<T>::size() const
{
	return m_size;
}

template<typename T>
inline std::size_t Vector<T>::capacity() const
{
	return m_capacity;
}

template<typename T>
inline void Vector<T>::push_back(const T& el)
{
	m_size++;
	if (m_size >= m_capacity) {
		m_capacity = m_capacity * 2 > m_size ? m_capacity * 2 : m_size;

		T* tmp = new T[m_capacity];
		
		for (int i = 0; i < m_size - 1; i++) {
			tmp[i] = m_arr[i];
		}

		delete[] m_arr;

		m_arr = tmp;
	}

	m_arr[m_size - 1] = el;
}

template<typename T>
inline void Vector<T>::pop_back()
{
	m_size--;

	m_arr[m_size] = T();
}

template<typename T>
inline void Vector<T>::resize(std::size_t newSize)
{
	if (newSize <= m_capacity) {
		return;
	}
	else {
		m_capacity = newSize;
	}

	T* tmp = new T[m_capacity];
	for (int i = 0; i < m_size; i++) {
		tmp[i] = m_arr[i];
	}

	delete[] m_arr;

	m_arr = tmp;

	m_size = newSize;
}

template<typename T>
inline T& Vector<T>::operator[](int idx)
{
	return m_arr[idx];
}

template<typename T>
inline const T& Vector<T>::operator[](int idx) const
{
	return m_arr[idx];
}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector& other)
{
	if (this != &other) {
		m_size = other.m_size;

		if (other.m_size <= m_capacity) {
			for (int i = 0; i < other.m_size; i++) {
				m_arr[i] = other.m_arr[i];
			}
		}
		else {
			T* tmp = new T[m_size];

			for (int i = 0; i < other.m_size; i++) {
				tmp[i] = other.m_arr[i];
			}

			delete[] m_arr;

			m_arr = tmp;
		}

		m_capacity = other.m_capacity;
	}

	return *this;
}

template<typename T>
void swap(T& left, T& right) {
	auto tmp = left;
	left = right;
	right = tmp;
}