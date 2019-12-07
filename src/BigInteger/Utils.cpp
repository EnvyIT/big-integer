#include <cmath>
#include  <climits>

#include "Utils.h"

using namespace std;

static bool isLongMinValue(long long number) {
  return number == LONG_MIN;
}

unsigned long Utils::getAbsolute(long long number) {
  return isLongMinValue(number) ? (LONG_MAX + 1UL) : labs(number); // workaround for not undefined behaviour of labs on LONG_MIN
}

int Utils::getNumberLength(long long  number) {
  unsigned long absoluteNumber = Utils::getAbsolute(number);
  int digitCount = 0;
  do {
    absoluteNumber /= 10;
    digitCount++;
  } while (absoluteNumber > 0);
  return digitCount;
}
