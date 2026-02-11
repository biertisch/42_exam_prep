#include "bigint.hpp"

bigint::bigint(unsigned int n)
{
	std::stringstream ss;
	ss << n;
	_strnum = ss.str();
}

bigint::bigint(const std::string& strnum) : _strnum(strnum) {}

bigint::bigint(const bigint& other) : _strnum(other._strnum) {}

bigint::~bigint() {}

bigint& bigint::operator=(const bigint& other)
{
	if (this != &other)
		_strnum = other._strnum;
	return *this;
}

std::string bigint::revert(const std::string& str)
{
	std::string reverse;
	for (int i = str.length() - 1; i >= 0; i--)
		reverse.push_back(str[i]);
	return reverse;
}

std::string bigint::add(const std::string& str1, const std::string& str2)
{
	std::string rev1 = revert(str1);
	std::string rev2 = revert(str2);
	std::string sum;

	while (rev1.length() < rev2.length())
		rev1.push_back('0');
	while (rev2.length() < rev1.length())
		rev2.push_back('0');

	int result = 0;
	int carry = 0;
	for (int i = 0; i < rev1.length() && i < rev2.length(); i++)
	{
		result = rev1[i] - '0' + rev2[i] - '0' + carry;
		sum.push_back(result % 10 + '0');
		carry = result / 10;
	}

	while (carry)
	{
		sum.push_back(carry % 10 + '0');
		carry /= 10;
	}

	return (revert(sum));
}

unsigned int bigint::stringToUint(const std::string& str)
{
	std::stringstream ss(str);
	unsigned int res;
	ss >> res;
	return res;
}

bigint bigint::operator+(const bigint& other) const
{
	return bigint(add(_strnum, other._strnum));
}

bigint& bigint::operator+=(const bigint& other)
{
	(*this) = (*this) + other;
	return *this;
}

bigint& bigint::operator++()
{
	_strnum = add(_strnum, "1");
	return *this;
}

bigint bigint::operator++(int)
{
	bigint temp(*this);
	_strnum = add(_strnum, "1");
	return temp;
}

bigint bigint::operator<<(unsigned int n) const
{
	return bigint(_strnum + std::string(n, '0'));
}

bigint bigint::operator>>(unsigned int n) const
{
	std::string temp = _strnum;

	if (n >= temp.length())
		temp = "0";
	else
		temp.erase(temp.length() - n, n);

	return bigint(temp);
}

bigint& bigint::operator<<=(unsigned int n)
{
	(*this) = (*this) << n;
	return *this;
}

bigint& bigint::operator>>=(unsigned int n)
{
	(*this) = (*this) >> n;
	return *this;
}

bigint bigint::operator<<(const bigint& other) const
{
	return (*this) << stringToUint(other._strnum);
}

bigint bigint::operator>>(const bigint& other) const
{
	return (*this) >> stringToUint(other._strnum);
}

bigint& bigint::operator<<=(const bigint& other)
{
	(*this) = (*this) << other;
	return *this;
}

bigint& bigint::operator>>=(const bigint& other)
{
	(*this) = (*this) >> other;
	return *this;
}

bool bigint::operator==(const bigint& other) const
{
	return _strnum == other._strnum;
}

bool bigint::operator!=(const bigint& other) const
{
	return !((*this) == other);
}

bool bigint::operator<(const bigint& other) const
{
	if (_strnum.length() != other._strnum.length())
		return (_strnum.length() < other._strnum.length());
	return (_strnum < other._strnum);
}

bool bigint::operator>(const bigint& other) const
{
	return !((*this) <= other);
}

bool bigint::operator<=(const bigint& other) const
{
	return (*this) < other || (*this) == other;
}

bool bigint::operator>=(const bigint& other) const
{
	return (*this) > other || (*this) == other;
}

std::string bigint::getString() const
{
	return _strnum;
}

std::ostream& operator<<(std::ostream& out, const bigint& obj)
{
	out << obj.getString();
	return out;
}
