#pragma once

#include <iostream>

class vect2
{
	private:
		int _x;
		int _y;

	public:
		vect2(int x = 0, int y = 0);
		vect2(const vect2& other);
		~vect2();

		vect2& operator=(const vect2& other);

		// negative
		vect2 operator-();

		// increment
		vect2& operator++();
		vect2 operator++(int);

		// decrement
		vect2& operator--();
		vect2 operator--(int);

		// addition
		vect2 operator+(const vect2& other) const;
		vect2& operator+=(const vect2& other);

		// subtraction
		vect2 operator-(const vect2& other) const;
		vect2& operator-=(const vect2& other);

		// multiplication
		vect2 operator*(int num) const;
		vect2& operator*=(int num);
		vect2 operator*(const vect2& other) const;
		vect2& operator*=(const vect2& other);

		// comparison
		bool operator==(const vect2& other) const;
		bool operator!=(const vect2& other) const;

		// subscript access
		int operator[](int index) const;
		int& operator[](int index);
};

std::ostream& operator<<(std::ostream& os, const vect2& obj);
vect2 operator*(int num, const vect2& obj);