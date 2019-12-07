#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>

#include "BigInt.h"
#include "Utils.h"

using namespace std;

static unsigned short int* createDigits(const unsigned short int* source, unsigned long length) {
  unsigned short int* destination = new unsigned short int[length];
  assert(destination != nullptr);
  for (long unsigned int i = 0; i < length; i++) {
    destination[i] = source[i];
  }
  return destination;
}

static unsigned short int* createDigits(long int number, unsigned long length) {
  unsigned long absoluteNumber = Utils::getAbsolute(number);
  unsigned short int* digits = new unsigned short int[length];
  assert(digits != nullptr);
  for (long unsigned int i = 0; i < length; i++) {
    digits[i] = absoluteNumber % 10;
    absoluteNumber /= 10;
  }
  return digits;
}

static bool isNumberNegative(long int number) {
  return number < 0;
}

BigInt::BigInt(long int number) : length(Utils::getNumberLength(number)), digits(createDigits(number, length)), isNegative(isNumberNegative(number)) {
  assert(digits != nullptr);
}

BigInt::BigInt(unsigned long length, unsigned short int* digits, bool isNegative) : length(length), digits(createDigits(digits, length)), isNegative(isNegative) {
  assert(digits != nullptr);
}


BigInt::BigInt(const BigInt& bigInt) : length(bigInt.length), digits(createDigits(bigInt.digits, bigInt.length)), isNegative(bigInt.isNegative), isError(bigInt.isError) {
  assert(digits != nullptr);
}


BigInt::~BigInt() {
  delete[] digits;
}

BigInt& BigInt::operator=(const BigInt& other) {
  if (this == &other) {
    return *this;
  }
  length = other.length;
  digits = createDigits(other.digits, other.length);
  isNegative = other.isNegative;
  return *this;
}

bool BigInt::operator<(const BigInt& other) {
  return compare(other) < 0;
}

bool BigInt::operator<=(const BigInt& other) {
  return compare(other) <= 0;
}

bool BigInt::operator==(const BigInt& other) {
  return compare(other) == 0;
}

bool BigInt::operator!=(const BigInt& other) {
  return compare(other) != 0;
}

bool BigInt::operator>=(const BigInt& other) {
  return compare(other) >= 0;
}

bool BigInt::operator>(const BigInt& other) {
  return compare(other) > 0;
}

BigInt& BigInt::operator+=(const BigInt& other) {
  BigInt otherCopy(other);
  if (haveSameSign(otherCopy)) {
    if (isSmaller(otherCopy)) {
      swap(otherCopy);
    }
    if (isOverFlow(otherCopy)) {
      resizeDigits(length + 1);
      otherCopy.resizeDigits(length + 1);
    }
    if (areNotEqual(otherCopy)) {
      otherCopy.resizeDigits(length);
    }
    add(otherCopy);
  } else {
    if (isNegative) {
      swap(otherCopy);
    }
    otherCopy.isNegative = false;
    *this -= otherCopy;
  }
  return *this;
}

BigInt& BigInt::operator-=(const BigInt& other) {
  BigInt otherCopy(other);
  BigInt zero;
  if (*this == other) {
    return *this = zero;
  }
  if (isZero()) {
    otherCopy.isNegative = true;
    return *this = otherCopy;
  }
  if ((!isNegative && otherCopy.isNegative) || (isNegative && !otherCopy.isNegative)) {
    otherCopy.isNegative = !otherCopy.isNegative;
    return *this += otherCopy;
  }
  bool isAbsSmaller = isAbsoluteSmaller(other);
  if (isSmaller(other) || isAbsSmaller) {
    swap(otherCopy);
    isNegative = isAbsSmaller ? !other.isNegative : other.isNegative;
  }
  if (areNotEqual(otherCopy)) {
    otherCopy.resizeDigits(length);
  }
  substract(otherCopy);
  return *this;
}

BigInt& BigInt::operator*=(const BigInt& other) {
  BigInt result;
  BigInt otherCopy(other);
  result.multiply(*this, otherCopy);

  return *this = result;
}


BigInt& BigInt::operator/=(const BigInt& other) {
  if (other.isZero()) {
    isError = true;
    return *this;
  }
  if (other.isOne()) {
    isNegative = (isNegative != other.isNegative);;
    return *this;
  }
  BigInt count;
  BigInt copy(*this);
  BigInt otherCopy(other);
  copy.divide(otherCopy, count);
  *this = count;
  isNegative = (isNegative != other.isNegative);
  return *this;
}

BigInt operator+(BigInt a, const BigInt& b) {
  return a += b;
}

BigInt operator-(BigInt a, const BigInt& b) {
  return a -= b;
}

BigInt operator*(BigInt a, const BigInt& b) {
  return a *= b;
}

BigInt operator/(BigInt a, const BigInt& b) {
  return a /= b;
}

static short getComparisonValue(bool isSmaller) {
  return isSmaller ? -1 : 1;
}

short BigInt::compare(const BigInt& other) const {
  if (isNegative != other.isNegative) {
    return getComparisonValue(isNegative);
  }
  if (length != other.length) {
    return getComparisonValue(length < other.length);
  }
  for (int i = length - 1; i >= 0; i--) {
    if (digits[i] != other.digits[i]) {
      return getComparisonValue((digits[i] < other.digits[i]) && !isNegative); //if negative the return value is inverted
    }
  }
  return 0;
}

void BigInt::resizeDigits(unsigned long newLength) {
  BigInt copy(*this);
  if (digits != nullptr) {
    delete[] digits;
    digits = nullptr;
  }
  digits = new unsigned short int[newLength];
  assert(digits != nullptr);
  if (copy.length > newLength) {
    copy.length = newLength;
  }
  for (long unsigned int i = 0; i < copy.length; i++) {
    digits[i] = copy.digits[i];
  }
  for (long unsigned int i = copy.length; i < newLength; i++) {
    digits[i] = 0;
  }
  length = newLength;
}

void BigInt::copyDigits(BigInt& other) {
  if (length < other.length) {
    resizeDigits(other.length);
  } else if (other.length < length) {
    other.resizeDigits(length);
  }
  for (long unsigned int i = 0; i < length; i++) {
    unsigned short int tmp = digits[i];
    digits[i] = other.digits[i];
    other.digits[i] = tmp;
  }
  bool tmpNegative = isNegative;
  isNegative = other.isNegative;
  other.isNegative = tmpNegative;
}

void BigInt::swap(BigInt& other) {
  BigInt tmp(other);
  unsigned long otherLength = other.length;
  unsigned long thisLength = length;
  other.copyDigits(*this);
  copyDigits(tmp);
  other.length = thisLength;
  length = otherLength;
  resizeDigits(otherLength);
  other.resizeDigits(thisLength);
}

void BigInt::removeLeadingZeros() {
  unsigned int resizedLength = length - 1;
  while (digits[resizedLength] == 0 && resizedLength != 0) {
    resizedLength--;
  }
  resizedLength++;
  if (resizedLength < length) {
    resizeDigits(resizedLength);
  }
}

void BigInt::add(BigInt& other) {
  int carry = 0;
  for (long unsigned int i = 0; i < length; i++) {
    int tmp = (digits[i] + other.digits[i]) % 10 + carry;
    carry = (digits[i] + other.digits[i]) / 10;
    if (tmp > 9) {
      tmp %= 10;
      carry++;
    }
    digits[i] = tmp;
  }
  removeLeadingZeros();
}

void BigInt::substract(BigInt& other) {
  int borrow = 0;
  for (long unsigned int i = 0; i < length; i++) {
    auto result = digits[i] - other.digits[i] - borrow;
    if (result < 0) {
      digits[i] = result + 10;
      borrow = 1;
    } else {
      digits[i] = result;
      borrow = 0;
    }
  }
  removeLeadingZeros();
}

void BigInt::divide(BigInt& other, BigInt& count) {
  isNegative = false;
  other.isNegative = false;
  while (*this >= other) {
    *this -= other;
    count += 1;
  }
  count.removeLeadingZeros();
}

void BigInt::multiply(const BigInt& origin, BigInt& other) {
  digits = createDigits(0L, (origin.length + other.length));
  length = origin.length + other.length;
  for (long unsigned int i = 0; i < origin.length; i++) {
    for (long unsigned int j = 0; j < other.length; j++) {
      digits[i + j] += origin.digits[i] * other.digits[j];
      digits[i + j + 1] = digits[i + j + 1] + digits[i + j] / 10;
      digits[i + j] %= 10;
    }
  }
  removeLeadingZeros();
  isNegative = (origin.isNegative != other.isNegative) && (!origin.isZero() && !other.isZero());
}

ostream& operator<<(std::ostream& outputStream, const BigInt& bigInt) {
  if (bigInt.error()) {
    return outputStream << "NaN";
  }
  if (bigInt.length == 0) {
    return outputStream << 0;
  }
  if (bigInt.isNegative) {
    outputStream << "-";
  }
  for (long unsigned int i = 0; i < bigInt.length; i++) {
    outputStream << bigInt.digits[bigInt.length - i - 1];
  }
  return outputStream;
}