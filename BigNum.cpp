#include "BigNum.hpp"
#include <bitset>

uint32_t leadingBitPosition(uint32_t n) 
{
	// Find the position of the first non-zero bit

	uint32_t result;

	for(result = 0; n; ++result) { 
		n >>= 1;
	}

	return result;	
}

void BigNum::updateBitLength()
{
	// Update the value of this->bitLength

	bitLength = number.size() ? 32 * (number.size() - 1)  + \
					leadingBitPosition(number.back()) : 0;
}

BigNum::BigNum(uint32_t value = 0) 
{
	number.push_back(value);
	updateBitLength();
}



BigNum::BigNum(std::string n, uint32_t base)
{
	// TODO: Implement BigNum-from-string constructor

}

BigNum BigNum::operator+(const BigNum& a)
{
	BigNum sum;
	bool carry = false;
	size_t length = std::max(this->getSize(), a.getSize());

	for(size_t i = 0; i < length; ++i) {
		uint32_t add = number[i] + a[i] + carry;
		sum.setByte(i, add & 0xFFFFFFFF);
		carry = add < a[i];
	}

	if (carry) {
		sum.setByte(length, carry);
	}

	return sum;
}

BigNum BigNum::operator*(const BigNum& a)
{
	// TODO: Implement Karatsuba algorithm

	BigNum product;
	unsigned long long carry = 0;
	size_t length = std::max(this->getSize(), a.getSize());
	
	for(size_t i = 0; i < this->getSize(); ++i) {
		if (!number[i]) {
			continue;
		}

		for(size_t j = 0, k = i; j < a.getSize(); ++j, ++k) {
			uint64_t tmp = a[j];
			tmp *= number[i];
			carry = tmp + product[k];
			product.setByte(k, carry & 0xFFFFFFFF);
			carry >>= 32;
		}

		if (carry) {
			product.setByte(i + a.getSize(), carry);
		}
	}

	return product;
}

uint32_t BigNum::operator[](size_t index) const
{
	return number.at(index);
}

size_t BigNum::getSize() const
{
	return number.size();
}

uint32_t BigNum::getBitLength() const
{
	return bitLength;
}

void BigNum::setByte(size_t index, uint32_t value)
{
	// TODO: think about better name for this function
	// Here Byte means an element of number vector 

	if (number.size() < index + 1) {
		number.resize(index + 1);
	}

	number.at(index) = value;
	updateBitLength();
}

std::ostream& operator<<(std::ostream& os, const BigNum& a)
{
	// Print the hexadecimal number representation
	// To get binary - use bitset<32>(a[i - 1])

	for(size_t i = a.getSize(); i > 0; --i) {
		os << std::hex << a[i - 1];
	}

	os << std::dec;

	return os;
}

int main(void) 
{
	BigNum a(-1);
	BigNum b(-1);
	BigNum sum = a + b;
	BigNum product = a * b;

	std::cout << "a = " << a << std::endl;
	std::cout << "b = " << b << std::endl;
	std::cout << "a + b = " << sum << std::endl;
	std::cout << "#bits in a + b = " << sum.getBitLength() << std::endl;
	std::cout << "a * b = " << a * b << std::endl; 
	std::cout << "#bits in a * b = " << product.getBitLength() << std::endl;

	return 0;
}