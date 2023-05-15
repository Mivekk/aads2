#pragma once
#include <iostream>

class String
{
public:
	String();
	String(const char* string);
	String(const String& other);
	String(String&& other) noexcept;
	~String();

	std::size_t length;

	char& operator[](int idx);
	char operator[](int idx) const;

	String& operator+=(String& other);
	String& operator+=(const char& other);
	String& operator=(const String& other);
	String& operator=(String&& other) noexcept;
	bool operator==(const String& other) const;
	bool operator==(const char* other) const;

	friend std::ostream& operator<<(std::ostream& out, const String& string);
	friend std::istream& operator>>(std::istream& in, String& string);

private:
	char* m_string;

	std::size_t m_capacity;
};

