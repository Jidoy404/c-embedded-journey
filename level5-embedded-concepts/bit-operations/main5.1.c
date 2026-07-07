#include <stdint.h>
#include <stdio.h>

void setBit(uint8_t *reg, int bit);
void clearBit(uint8_t *reg, int bit);
void toggleBit(uint8_t *reg, int bit);
int checkBit(uint8_t reg, int bit);
void printBinary(uint8_t n);

int main()
{
  uint8_t reg = 0;
  // uint8_t reg = 0; reg має рівно 8 біт тобто 00000000
  printBinary(reg); // 00000000

  setBit(&reg, 3);
  printBinary(reg); // 00001000

  setBit(&reg, 7);
  printBinary(reg); // 10001000

  printf("%d\n", checkBit(reg, 3)); // 1
  printf("%d\n", checkBit(reg, 2)); // 0

  toggleBit(&reg, 7);
  printBinary(reg); // 00001000

  clearBit(&reg, 3);
  printBinary(reg); // 00000000

  return 0;
}

// |  — додає одиницю
// &  — фільтрує
// ~  — перевертає маску
// ^  — перемикає

// reg   = 00001000
// ~mask = 11110111
// ---------------- &
// res   = 00000000

// маска показала bit 3
// ~ зробив на цьому місці 0
// & очистив цей біт

// reg  — це панель з 8 перемикачами
// mask — це палець, який показує на один перемикач
// оператор — це дія: увімкнути, вимкнути, перевірити або перемкнути

void setBit(uint8_t *reg, int bit)
{
  *reg |= (1 << bit); // розбір *reg це з тим що ми працюємо, це |= операція,
  // (1 << 3) = 00001000
  // 00000000 | 00001000 = 00001000
}

void clearBit(uint8_t *reg, int bit)
{
  *reg &= ~(1 << bit);
  // (1 << 3)  = 00001000
  // ~(1 << 3) = 11110111
  // 00001000 & 11110111 = 00000000
}

void toggleBit(uint8_t *reg, int bit)
{
  *reg ^= (1 << bit);
// 0 XOR 1 = 1, 1 XOR 1 = 0
}

int checkBit(uint8_t reg, int bit)
{
  return (reg >> bit) & 1;
}

void printBinary(uint8_t n)
{
    for (int i = 7; i >= 0; i--)
        printf("%d", checkBit(n, i));
    printf("\n");
}