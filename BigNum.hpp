#pragma once

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

class BigNum 
{

	std::vector<uint32_t> number;
	uint32_t bitLength;

	void updateBitLength();

public:

	BigNum(uint32_t value);
	BigNum(std::string n, uint32_t base);

	size_t getSize() const;
	uint32_t getBitLength() const;

	void setByte(size_t index, uint32_t value);

	BigNum operator+(const BigNum& a);
	BigNum operator*(const BigNum& a);
	uint32_t operator[](size_t index) const;

	friend std::ostream& operator<<(std::ostream& os, const BigNum& a);
};