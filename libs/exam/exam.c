#include "exam.h"

// Функция для проверки, делится ли число на все свои цифры
int isDivisibleByDigits(int number) {
    int temp = number;
    while (temp > 0) {
        int digit = temp % 10;
        if (digit == 0 || number % digit != 0) {
            return 0; // Если цифра равна 0 или число не делится на цифру, возвращаем 0
        }
        temp /= 10;
    }
    return 1; // Если число делится на все свои цифры, возвращаем 1
}