#include "vect2.hpp"

vect2::vect2(int x, int y) : _x(x), _y(y) {}

vect2::vect2(const vect2& other) : _x(other._x), _y(other._y) {}

vect2::~vect2() {}

vect2& vect2::operator=(const vect2& other)
{
	if (this != &other)
	{
		_x = other._x;
		_y = other._y;
	}
	return *this;
}

vect2 vect2::operator-()
{
	return vect2(-_x, -_y);
}

vect2& vect2::operator++()
{
	++_x;
	++_y;
	return *this;
}

vect2 vect2::operator++(int)
{
	vect2 temp(*this);
	++(*this);
	return temp;
}

vect2& vect2::operator--()
{
	--_x;
	--_y;
	return *this;
}

vect2 vect2::operator--(int)
{
	vect2 temp(*this);
	--(*this);
	return temp;
}

vect2 vect2::operator+(const vect2& other) const
{
	return vect2(_x + other._x, _y + other._y);
}

vect2& vect2::operator+=(const vect2& other)
{
	*this = *this + other;
	return *this;
}

vect2 vect2::operator-(const vect2& other) const
{
	return vect2(_x - other._x, _y - other._y);
}

vect2& vect2::operator-=(const vect2& other)
{
	*this = *this - other;
	return *this;
}

vect2 vect2::operator*(int num) const
{
	return vect2(_x * num, _y * num);
}

vect2& vect2::operator*=(int num)
{
	*this = *this * num;
	return *this;
}

vect2 vect2::operator*(const vect2& other) const
{
	return vect2(_x * other._x, _y * other._y);
}

vect2& vect2::operator*=(const vect2& other)
{
	*this = *this * other;
	return *this;
}

bool vect2::operator==(const vect2& other) const
{
	return (_x == other._x && _y == other._y);
}

bool vect2::operator!=(const vect2& other) const
{
	return !(*this == other);
}

int vect2::operator[](int index) const
{
	if (index < 0 || index > 1)
		return -1;

	return (index == 0) ? _x : _y;
}

int& vect2::operator[](int index)
{
	return (index == 0) ? _x : _y;
}

std::ostream& operator<<(std::ostream& os, const vect2& obj)
{
	os << "{" << obj[0] << ", " << obj[1] << "}";
	return os;
}

vect2 operator*(int num, const vect2& obj)
{
	return obj * num;
}