#pragma once

#include <iostream>
#include <string>
#include <sstream>

class bigint
{
	private:
		std::string _strnum;

		static std::string revert(const std::string& strnum);
		static std::string add(const std::string& str1, const std::string& str2);
		static unsigned int stringToUint(const std::string& str);

	public:
		bigint(unsigned int n = 0);
		bigint(const std::string& strnum);
		bigint(const bigint& other);
		~bigint();

		bigint& operator=(const bigint& other);

		// addition
		bigint operator+(const bigint& other) const;
		bigint& operator+=(const bigint& other);

		// increment
		bigint& operator++();
		bigint operator++(int);

		// digit-shifting
		bigint operator<<(unsigned int n) const;
		bigint operator>>(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint& operator>>=(unsigned int n);

		bigint operator<<(const bigint& other) const;
		bigint operator>>(const bigint& other) const;
		bigint& operator<<=(const bigint& other);
		bigint& operator>>=(const bigint& other);

		// comparison
		bool operator==(const bigint& other) const;
		bool operator!=(const bigint& other) const;
		bool operator<(const bigint& other) const;
		bool operator>(const bigint& other) const;
		bool operator<=(const bigint& other) const;
		bool operator>=(const bigint& other) const;

		// getters
		std::string getString() const;
};

std::ostream& operator<<(std::ostream& out, const bigint& obj);