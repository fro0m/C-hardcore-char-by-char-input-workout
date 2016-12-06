#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
/*
4. Дана последовательность из N целых
16тиразрядных чисел (входной поток в
консоли, заданы только числа, а их
общее число не указано). Выполнить
циклический сдвиг элементов на k<16
разрядов. Вывести результат в консоль,
 уменьшить k на 1, повторить. Повторять
 процедуру, пока k > 0. Пример сдвига на 8
 разрядов: входная последовательность:
 0xAABB 0хCCDD 0хEEFF 0x1122;
результат: 0хBBCC 0xDDEE 0xFF11 0x22AA.
Если для хранения введенных пользователем
чисел недостаточно ресурсов - прервать
работу программы. При решении задачи
 нельзя использовать статические массивы.
Утечек памяти в программе быть не должно -
после завершения работы все динамические
объекты должны быть очищены.
*/

unsigned short shl(unsigned short a, unsigned short s) {
  return (a << s) | (a >> 16 - s);
}

int convertToHex(int ch) {
    switch (ch) {
    case 'A':
        return 10;
        break;
    case 'B':
        return 11;
        break;
    case 'C':
        return 12;
        break;
    case 'D':
        return 13;
        break;
    case 'E':
        return 14;
        break;
    case 'F':
        return 15;
        break;
    default:
        return ch - 48;
    }
}

int main(int argc, char *argv[])
{
    int i;
    int ch = 1;
    int currentIndex = 0;
    int maxSize = 3;
    unsigned short *arr = (unsigned short *)malloc(maxSize * sizeof(unsigned short));
    // fill arr with numbers
    printf("Enter hexadecimal numbers, separated with space ex: A5A5\n");
    unsigned short num = 0;
    short curr = 0;
    while(1) {
        num = 0;
        for(i = 0; i < 4; ++i) {
            curr = _getch();
            if (curr == (unsigned char)'\r' ||
                    curr == (unsigned char)' ' ||
                    curr == (unsigned char)'\t') {
                --i;
                continue;
            }
            putchar(curr);
            num = num << 4;
            num = num | convertToHex(curr);
            //num = num & 0x0000FFFF;
        }
        if (currentIndex + 1 > maxSize) {
            maxSize = maxSize + 3;
            arr = (unsigned short *)realloc(arr, maxSize);
            if (arr == 0) {
                printf("\nCritical error with memory");
                return -1;
            }
        }
        arr[currentIndex] = num;
        currentIndex++;

        // check if we need to enter more
        ch = _getch();
        if (ch == ' ') {
            putchar(ch);
            continue;
        } else {
            break;
        }
    }
    // making the output
    for(i = 16; i > 0; --i) {
        int j;
        printf("\nMaking a shift for %d\n", i);
        for(j = 0; j < currentIndex; ++j) {
            printf("0x%X ", shl(arr[j], i));
        }
        printf("\n");
    }
    free(arr);
    return 0;
}
