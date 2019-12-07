#include <iostream>
#include <string>
#include <climits>

#include "Utils.h"
#include "BigInt.h"

#define PRINT(func) (cout << #func << endl)

using namespace std;

template <typename T>
static void printAssertion(T expected, T actual) {
  cout << "Expected: " << expected << " Actual: " << actual << endl;
}

static void println() {
  cout << endl;
}

void testUtils() {
  PRINT(Utils::getNumberLength);
  printAssertion(5, Utils::getNumberLength(12341));
  printAssertion(1, Utils::getNumberLength(1));
  printAssertion(2, Utils::getNumberLength(13.37));
  printAssertion(2, Utils::getNumberLength(42));
  printAssertion(10, Utils::getNumberLength(1234567890));
  println();
  PRINT(Utils::getAbsolute);
  cout << "LONG MAX IS: " << LONG_MAX << endl;
  cout << "LONG MIN IS: " << LONG_MIN << endl;
  cout << "Utils::getAbsolute(LONG_MIN) " << Utils::getAbsolute(LONG_MIN) << endl;
  println();
}

void testBigIntCompare() {
  PRINT(testBigIntCompare);
  unsigned short int digits[] = { 1 , 3 , 4 , 4 };
  BigInt bigIntOfDigits(4, digits, false);
  BigInt bigInt(4431);
  BigInt bigIntNegativeSmaller(-4431);
  BigInt zero(0);
  BigInt bigIntNegative(-1);
  BigInt ninetyNine(99);
  BigInt ninetyEight(98);
  BigInt fiveThousandandFive(5005);
  BigInt fiveThousandOneHundredandFourteen(5114);
  short equals = 0;
  short smaller = -1;
  short greater = 1;
  printAssertion(smaller, fiveThousandandFive.compare(fiveThousandOneHundredandFourteen));
  printAssertion(greater, fiveThousandOneHundredandFourteen.compare(fiveThousandandFive));
  printAssertion(equals, bigInt.compare(bigIntOfDigits));
  printAssertion(smaller, bigIntNegativeSmaller.compare(bigIntOfDigits));
  printAssertion(greater, bigIntOfDigits.compare(bigIntNegativeSmaller));
  printAssertion(smaller, zero.compare(bigInt));
  printAssertion(equals, zero.compare(zero));
  printAssertion(equals, bigIntNegative.compare(bigIntNegative));
  printAssertion(equals, bigIntNegative.compare(bigIntNegative));
  printAssertion(greater, ninetyNine.compare(ninetyEight));
  printAssertion(smaller, ninetyEight.compare(ninetyNine));
  printAssertion(equals, ninetyNine.compare(ninetyNine));
  println();
}

void testBigIntAllComparisonOperators() {
  PRINT(testBigIntAllComparisonOperators);
  BigInt nine(9);
  BigInt ten(10);
  BigInt zero(0);
  BigInt minusOne(-1);
  BigInt minusTwo(-2);
  BigInt oneMillion(1000000);
  bool expectedTrue = true;
  bool expectedFalse = false;
  printAssertion(expectedTrue, nine < ten);
  printAssertion(expectedFalse, nine > ten);
  printAssertion(expectedTrue, nine == nine);
  printAssertion(expectedTrue, nine != oneMillion);
  printAssertion(expectedFalse, oneMillion < ten);
  printAssertion(expectedTrue, zero <= ten);
  printAssertion(expectedTrue, minusOne < zero);
  printAssertion(expectedTrue, minusOne <= minusOne);
  printAssertion(expectedTrue, minusOne == minusOne);
  printAssertion(expectedTrue, minusOne > minusTwo);
  printAssertion(expectedTrue, minusOne >= minusTwo);
  println();
}

void testBigIntOutputStream() {
  PRINT(testBigIntOutputStream);
  unsigned short int digits[] = { 7, 3 ,3 , 1 };
  BigInt bigIntOfDigits(4, digits, false);
  BigInt bigInt(42);
  BigInt bigIntNegativeSmaller(-4431);
  BigInt zero(0);
  BigInt max(LONG_MAX);
  BigInt min(LONG_MIN);
  cout << "Expected: " << 1337 << " Actual: " << bigIntOfDigits << endl;
  cout << "Expected: " << 42 << " Actual: " << bigInt << endl;
  cout << "Expected: " << -4431 << " Actual: " << bigIntNegativeSmaller << endl;
  cout << "Expected: " << 0 << " Actual: " << zero << endl;
  cout << "Expected: " << LONG_MAX << " Actual: " << max << endl;
  cout << "Expected: " << LONG_MIN << " Actual: " << min << endl;
  println();
}

void testBigIntAddition() {
  PRINT(testBigIntAddition);
  BigInt operandOne(15);
  BigInt operandTwo(9);
  BigInt eight(8);
  BigInt three(3);
  BigInt minusThirteen(-13);
  operandTwo += operandTwo;
  cout << "Expected: " << 100 << " Actual: " << BigInt(99) + BigInt(1) << endl;
  cout << "Expected: " << 100 << " Actual: " << BigInt(1) + BigInt(99) << endl;
  cout << "Expected: " << 3 << " Actual: " << BigInt(3) + BigInt(0) << endl;
  cout << "Expected: " << 0 << " Actual: " << BigInt(0) + BigInt(0) << endl;
  cout << "Expected: " << 5 << " Actual: " << BigInt(3) + BigInt(2) << endl;
  cout << "Expected: " << 18 << " Actual: " << operandTwo << endl;
  cout << "Expected: " << 18 << " Actual: " << BigInt(9) + BigInt(9) << endl;
  cout << "Expected: " << 1141 << " Actual: " << BigInt(9) + BigInt(9) + 123 + 1000 << endl;
  BigInt minusOperand(-99);
  BigInt minusSecondOperand(-99);
  cout << "Expected: " << -198 << " Actual: " << minusOperand + minusSecondOperand << endl;
  operandOne += eight; // 15 + 8
  cout << "Expected: " << 23 << " Actual: " << operandOne << endl;
  three += operandOne; // 3 + 23 
  cout << "Expected: " << 26 << " Actual: " << three << endl;
  cout << "Expected: " << 315 << " Actual: " << BigInt(3) + BigInt(312) << endl;
  operandOne += minusThirteen; // 23 + (-13)
  cout << "Expected: " << 10 << " Actual: " << operandOne << endl;
  BigInt summandMax(LONG_MAX);
  BigInt one(1);
  summandMax += one;
  cout << "Expected: " << BigInt(LONG_MAX) + 1 << " Actual: " << summandMax << endl;
  cout << "Expected: " << "123456616" << " Actual: " << BigInt(123451234) + 234 * 23 << endl;
  println();
}

void  testBigIntSubtraction() {
  PRINT(testBigIntSubtraction);
  cout << "Expected: " << 9 << " Actual: " << BigInt(9) - BigInt(0) << endl;
  cout << "Expected: " << 6 << " Actual: " << BigInt(9) - BigInt(3) << endl;
  cout << "Expected: " << 12 << " Actual: " << BigInt(9) - BigInt(-3) << endl;
  cout << "Expected: " << -12 << " Actual: " << BigInt(-9) - BigInt(3) << endl;
  cout << "Expected: " << -6 << " Actual: " << BigInt(-9) - BigInt(-3) << endl;
  BigInt result(15);
  result -= BigInt(3);
  cout << "Expected: " << 12 << " Actual: " << result << endl;
  BigInt resultTwo(6);
  resultTwo -= resultTwo;
  cout << "Expected: " << 0 << " Actual: " << resultTwo << endl;
  cout << "Expected: " << -3 << " Actual: " << BigInt(0) - BigInt(3) << endl;
  cout << "Expected: " << 3 << " Actual: " << BigInt(3) - BigInt(0) << endl;
  cout << "Expected: " << -313 << " Actual: " << BigInt(-516) - BigInt(-203) << endl;
  cout << "Expected: " << 2 << " Actual: " << BigInt(-1) - BigInt(-3) << endl;
  BigInt subtrahendMax(LONG_MIN);
  BigInt one(1);
  subtrahendMax -= one;
  cout << "Expected: " << BigInt(LONG_MIN) - 1 << " Actual: " << subtrahendMax << endl;
  BigInt nine = 9;
  BigInt fifteen = 15;
  cout << "Expected: " << 6 << " Actual: " << fifteen - nine << endl;
  cout << "Expected: " << 0 << " Actual: " << nine - nine << endl;
  cout << "Expected: " << -6 << " Actual: " << nine - fifteen << endl;
  cout << "Expected: " << 2459988 << " Actual: " << BigInt(2460000) - BigInt(12) << endl;
  println();
}

void  testBigIntMultiplication() {
  PRINT(testBigIntMultiplication);
  cout << "Expected: " << 15129 << " Actual: " << BigInt(123) * BigInt(123) << endl;
  cout << "Expected: " << 27 << " Actual: " << BigInt(9) * BigInt(3) << endl;
  cout << "Expected: " << "99989990001" << " Actual: " << BigInt(9999999) * BigInt(9999) << endl;
  cout << "Expected: " << "-99989990001" << " Actual: " << BigInt(9999999) * BigInt(-9999) << endl;
  cout << "Expected: " << "-99989990001" << " Actual: " << BigInt(-9999999) * BigInt(9999) << endl;
  cout << "Expected: " << -27 << " Actual: " << BigInt(9) * BigInt(3) * BigInt(-1) << endl;
  cout << "Expected: " << 1 << " Actual: " << BigInt(-1) * BigInt(-1) << endl;
  cout << "Expected: " << 405 << " Actual: " << BigInt(45) * BigInt(9) << endl;
  cout << "Expected: " << 0 << " Actual: " << BigInt(-9999999) * BigInt(0) << endl;
  cout << "Expected: " << 0 << " Actual: " << BigInt(0) * BigInt(-9999999) << endl;
  cout << "Expected: " << -9999999 << " Actual: " << BigInt(-9999999) * BigInt(1) << endl;
  cout << "Expected: " << 246000 << " Actual: " << BigInt(123) * BigInt(2000) << endl;
  println();
}

void testBigIntDivision() {
  PRINT(testBigIntDivision);
  cout << "Expected: " << 26 << " Actual: " << BigInt(3210) / BigInt(123) << endl;
  cout << "Expected: " << 0 << " Actual: " << BigInt(3) / BigInt(15) << endl;
  cout << "Expected: " << 0 << " Actual: " << BigInt(10) / BigInt(12) << endl;
  cout << "Expected: " << 3 << " Actual: " << BigInt(9) / BigInt(3) << endl;
  cout << "Expected: " << 1 << " Actual: " << BigInt(9) / BigInt(9) << endl;
  cout << "Expected: " << 5 << " Actual: " << BigInt(45) / BigInt(9) << endl;
  cout << "Expected: " << -5 << " Actual: " << BigInt(45) / BigInt(-9) << endl;
  cout << "Expected: " << 0 << " Actual: " << BigInt(10) / BigInt(100) << endl;
  cout << "Expected: " << 1 << " Actual: " << BigInt(-1) / BigInt(-1) << endl;
  cout << "Expected: " << -51 << " Actual: " << BigInt(51) / BigInt(-1) << endl;
  cout << "Expected: " << -25 << " Actual: " << BigInt(-25) / BigInt(1) << endl;
  cout << "Expected: " << -5 << " Actual: " << BigInt(-15) / BigInt(-3) << endl;
  cout << "Expected: " << 13 << " Actual: " << BigInt(3210) / BigInt(123) / BigInt(2) << endl;
  cout << "Expected: " << 94615 << " Actual: " << BigInt(123) * BigInt(20000) / BigInt(26) << endl;
  println();
}

void testBigIntAllOperators() {
  PRINT(testBigIntAllOperators);
  cout << "Expected: " << 20000 << " Actual: " << BigInt(3210) / BigInt(123) + BigInt(20000) - BigInt(26) << endl;
  cout << "Expected: " << 76152 << " Actual: " << BigInt(1337) * BigInt(42) + BigInt(20000) - BigInt(26) / BigInt(10) << endl;
  cout << "Expected: " << 3184 << " Actual: " << BigInt(3210) + BigInt(123) / BigInt(20000) - BigInt(26) << endl;
  cout << "Expected: " << -91405 << " Actual: " << BigInt(3210) - BigInt(123) * BigInt(20000) / BigInt(26) << endl;
  println();
}


int main() {
  println();
  testUtils();
  testBigIntCompare();
  testBigIntAllComparisonOperators();
  testBigIntOutputStream();
  testBigIntAddition();
  testBigIntSubtraction();
  testBigIntMultiplication();
  testBigIntDivision();
  testBigIntAllOperators();
  println();
  return 0;
}