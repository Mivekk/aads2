#define _CRT_SECURE_NO_WARNINGS
#include "String.h"

String::String()
	: m_string(new char[8] {0}), length(0), m_capacity(8)
{
}

String::String(const char* string)
{
	length = strlen(string);
	m_capacity = length;

	m_string = new char[length + 1];
	strcpy_s(m_string, length + 1, string);
	m_string[length] = '\0';
}

String::String(const String& other)
{
	length = other.length;
	m_capacity = length;

	char* tmp = new char[length + 1];
	strcpy(tmp, other.m_string);

	m_string = tmp;
}

String::String(String&& other) noexcept
{
	m_string = other.m_string;

	length = other.length;
	m_capacity = length;

	other.m_string = nullptr;
	other.length = 0;
}

String::~String()
{
	delete[] m_string;
}

char& String::operator[](int idx)
{
	return m_string[idx];
}

char String::operator[](int idx) const
{
	return m_string[idx];
}

String& String::operator+=(String& other)
{
	length += other.length;
	m_capacity = length;

	char* tmp = new char[length + 1];

	strcpy(tmp, m_string);
	strcat(tmp, other.m_string);

	delete[] m_string;

	m_string = tmp;

	return *this;
}

String& String::operator+=(const char& other)
{
	length++;
	if (length >= m_capacity) {
		m_capacity = m_capacity * 2 > length ? m_capacity * 2 : length;

		char* tmp = new char[m_capacity + 1];
		strcpy(tmp, m_string);

		delete[] m_string;

		m_string = tmp;
	}

	m_string[length - 1] = other;
	m_string[length] = '\0';

	return *this;
}

String& String::operator=(const String& other)
{
	if (this != &other) {
		length = other.length;
		m_capacity = length;

		char* tmp = new char[length + 1];
		strcpy(tmp, other.m_string);

		// swap elements
		auto el = tmp;
		tmp = m_string;
		m_string = el;

		delete[] tmp;
	}

	return *this;
}

String& String::operator=(String&& other) noexcept
{
	if (this != &other) {
		delete[] m_string;

		m_string = other.m_string;

		length = other.length;
		m_capacity = length;

		other.m_string = nullptr;
		other.length = 0;
	}

	return *this;
}

bool String::operator==(const String& other) const
{
	if (m_string == nullptr) {
		return false;
	}

	return !strcmp(m_string, other.m_string);
}

bool String::operator==(const char* other) const
{
	if (m_string == nullptr) {
		return false;
	}

	return !strcmp(m_string, other);
}

std::ostream& operator<<(std::ostream& out, const String& string)
{
	// if exception is thrown out here probably you are trying
	// to access non-existent (String) object

	out << string.m_string;
	return out;
}

std::istream& operator>>(std::istream& in, String& string)
{
	char buffer[64];
	in >> buffer;

	string = buffer;

	return in;
}
