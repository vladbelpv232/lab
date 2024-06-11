#include "exam.h"

// Функция для тестирования функции isDivisibleByDigits
void testIsDivisibleByDigits() {
    assert(isDivisibleByDigits(12) == 1); // 12 делится на 1 и 2
    assert(isDivisibleByDigits(15) == 1); // 15 делится на 1 и 5
    assert(isDivisibleByDigits(24) == 1); // 24 делится на 2 и 4
    assert(isDivisibleByDigits(30) == 0); // 30 делится на 3 и 0, но 0 не является натуральным числом
}

int main(){
    testIsDivisibleByDigits();

    return 0;
}