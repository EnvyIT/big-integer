#pragma once
class BigInt {

private:
  unsigned long length;
  unsigned short int* digits;
  bool isNegative;
  bool isError = false;

  void resizeDigits(unsigned long newLength);

  void copyDigits(BigInt& other);

  void swap(BigInt& other);

  void removeLeadingZeros();

  void add(BigInt& other);

  void substract(BigInt& other);

  void divide(BigInt& other, BigInt& result);

  void multiply(const BigInt& origin, BigInt& other);

  inline bool isOverFlow(const BigInt& other) {
    return (digits[length - 1] + other.digits[other.length - 1]) > 9;
  }

public:
  BigInt(long int number = 0);
  BigInt(unsigned long length, unsigned short int* digits, bool isNegative);
  BigInt(const BigInt& other);
  ~BigInt();

  BigInt& operator=(const BigInt& other);

  bool operator<(const BigInt& other);
  bool operator<=(const BigInt& other);
  bool operator==(const BigInt& other);
  bool operator!=(const BigInt& other);
  bool operator>=(const BigInt& other);
  bool operator>(const BigInt& other);

  BigInt& operator+=(const BigInt& other);
  BigInt& operator-=(const BigInt& other);
  BigInt& operator*=(const BigInt& other);
  BigInt& operator/=(const BigInt& other);

  friend std::ostream& operator<<(std::ostream& outputStream, const BigInt& thiz);
  friend BigInt operator+(BigInt thiz, const BigInt& other);
  friend BigInt operator-(BigInt thiz, const BigInt& other);
  friend BigInt operator*(BigInt thiz, const BigInt& other);
  friend BigInt operator/(BigInt thiz, const BigInt& other);

  short compare(const BigInt& bigInt) const;

  inline bool isZero() const {
    return this->length == 1 && this->digits[0] == 0;
  }

  inline bool isOne() const {
    return this->length == 1 && this->digits[0] == 1;
  }

  inline bool error() const {
    return this->isError;
  }

  inline bool isSmaller(const BigInt& other) {
    return length < other.length;
  }

  inline bool haveSameSign(const BigInt& other) {
    return isNegative == other.isNegative;
  }

  inline bool areEqual(const BigInt& other) {
    return length == other.length;
  }

  inline bool areNotEqual(const BigInt& other) {
    return !areEqual(other);
  }

  inline bool isAbsoluteSmaller(const BigInt& other) {
    if (length != other.length) {
      return length < other.length;
    }
    for (int i = length - 1; i >= 0; i--) {
      if (digits[i] != other.digits[i]) {
        return digits[i] < other.digits[i];
      }
    }
    return false;
  }

};





