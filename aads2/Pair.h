#pragma once

template<typename T, typename K>
class Pair {
public:
    Pair();
    Pair(const T& first, const K& second);
    Pair(T&& first, K&& second);
    ~Pair();

    T first;
    K second;

    Pair<T, K>& operator=(const Pair<T, K>& other);

    friend bool operator<(const Pair<T, K>& left, const Pair<T, K>& right) {
        return left.first < right.first;
    }

    friend bool operator<=(const Pair<T, K>& left, const Pair<T, K>& right) {
        return left.first <= right.first;
    }

    friend bool operator>(const Pair<T, K>& left, const Pair<T, K>& right) {
        return left.first > right.first;
    }

    friend bool operator>=(const Pair<T, K>& left, const Pair<T, K>& right) {
        return left.first >= right.first;
    }
};

template<typename T, typename K>
inline Pair<T, K>::Pair()
    : first(T()), second(K())
{
}

template<typename T, typename K>
inline Pair<T, K>::Pair(const T& first, const K& second)
    : first(first), second(second)
{
}

template<typename T, typename K>
inline Pair<T, K>::Pair(T&& first, K&& second)
    : first((T&&)first), second((K&&)second)
{
}

template<typename T, typename K>
inline Pair<T, K>::~Pair()
{
}

template<typename T, typename K>
inline Pair<T, K>& Pair<T, K>::operator=(const Pair<T, K>& other)
{
    if (this != &other) {
        first = other.first;
        second = other.second;
    }

    return *this;
}