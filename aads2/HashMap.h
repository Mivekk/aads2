#pragma once
#include "Vector.h"
#include "String.h"

#define HASHMAP_CAPACITY 200003

template<typename T, typename K>
struct HashNode {
	T key;
	K value;
};

template<typename T, typename K>
class HashMap {
public:
	HashMap();
	~HashMap();

	void set(const T& key, const K& value);
	const K& get(const T& key);

private:
	int hash(const T& key);

	Vector<Vector<HashNode<T, K>>> m_nodes;
};

template<typename T, typename K>
inline HashMap<T, K>::HashMap()
{
	m_nodes.resize(HASHMAP_CAPACITY);
}

template<typename T, typename K>
inline HashMap<T, K>::~HashMap()
{
}

template<typename T, typename K>
inline void HashMap<T, K>::set(const T& key, const K& value)
{
	int hashedKey = hash(key);

	HashNode<T, K> newNode = { key, value };

	m_nodes[hashedKey].push_back(newNode);
}

template<typename T, typename K>
inline const K& HashMap<T, K>::get(const T& key)
{
	int hashedKey = hash(key);

	if (m_nodes[hashedKey].size() == 0) {
		return K();
	}
	else if (m_nodes[hashedKey].size() == 1) {
		return m_nodes[hashedKey][0].value;
	}

	for (int i = 0; i < m_nodes[hashedKey].size(); i++) {
		if (m_nodes[hashedKey][i].key == key) {
			return m_nodes[hashedKey][i].value;
		}
	}

	return K();
}

template<typename T, typename K>
inline int HashMap<T, K>::hash(const T& key)
{
	// djb2
	unsigned long long hash = 5381;
	for (int i = 0; i < key.length; i++) {
		hash = ((hash << 5) + hash) + key[i];
	}

	return hash % HASHMAP_CAPACITY;
}
