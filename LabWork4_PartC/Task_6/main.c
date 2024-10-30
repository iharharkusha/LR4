#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

const int INF = 2000000000;

int readIntegerInLine() {
    int inputValue;
    char term;
    if (scanf("%d%c", &inputValue, &term) != 2 || term != '\n') {
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {
        }
        return -INF;
    }
    return inputValue;
}  

void StepMetod(long long n, int nLength, int x, int y, unsigned long long* arr) {
    for (unsigned long long i = 0; i < n * n; i++) {
        arr[x * nLength + y] = i + 1;
        int xb = x, yb = y;
        if (x - 1 < 0) x = n - 1; else x = x - 1; 
        if (y + 1 > n - 1) y = 0; else y = y + 1;
        if (arr[x * nLength + y] != 0) {
            if (xb == n - 1) xb = 0; else xb = xb + 1;
            x = xb; y = yb;
        }
    }
}

void SwapArr(int x1, int y1, int x2, int y2, unsigned long long *a, int n) {
    unsigned long long sw = a[x1 * n + y1];
    a[x1 * n + y1] = a[x2 * n + y2];
    a[x2 * n + y2] = sw;
}

void PrintMagicSquare(unsigned long long *a, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%5llu ", a[i * n + j]); 
        }
        printf("\n");
    }
}

int main() {
    printf("Задание 6. Сгенерировать магический квадрат\n");
    printf("Выполнил Гаркуша Игорь Вячеславович, группа 453502\n\n"); 
    while (true) {
        printf("Введите 1 для запуска программы, 0 для ее завершения:\n");
        int type = readIntegerInLine();
        if (type != 0 && type != 1) {
            printf("Некорректный ввод\n");
            continue;
        }
        if (type == 0) {
            break;
        }
        int n;
        printf("Введите размер магического квадрата (целое число больше 2):\n");
        while (true) {
            n = readIntegerInLine();
            if (n == -INF) {
                printf("Некорректный ввод\n");
                continue;
            }
            break;
        }
        //основной код
        unsigned long long* a = (unsigned long long*)malloc(n * n * sizeof(unsigned long long));    
        // Проверка на успешное выделение памяти
        if (a == NULL) {
            fprintf(stderr, "Ошибка выделения памяти.\n");
            return 1;
        }
        // Инициализация массива
        for (long long i = 0; i < n * n; i++) {
            a[i] = 0;
        }
        int halfMat = n / 2;
        if ((n / 2) % 2 != 0 && n % 2 == 0) {
            StepMetod(halfMat, n, 0, n / 4, a);
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (i < halfMat && j > halfMat - 1) 
                        a[i * n + j] = a[i * n + (j - halfMat)] + (n * n) / 2;
                    if (i > (halfMat) - 1 && j < halfMat) 
                        a[i * n + j] = a[(i - halfMat) * n + j] + ((n * n) / 4) * 3;
                    if (i > (halfMat) - 1 && j > halfMat - 1) 
                        a[i * n + j] = a[(i - halfMat) * n + (j - halfMat)] + (n * n) / 4;
                }
            }
            for (int i = 0; i < n / 2; i++) {
                for (int h = 0; h < n / 4; h++) 
                    SwapArr(i, (i == 0 || i == halfMat - 1 ? h + 1 : h), i + halfMat, (i == 0 || i == halfMat - 1 ? h + 1 : h), a, n);
                for (int h = 0; h < n / 4 - 1; h++) 
                    SwapArr(i, n - 1 - h, halfMat + i, n - 1 - h, a, n);
            }
        }
        if ((n / 2) % 2 == 0 && n % 2 == 0) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if ((n / 4) > i || (n / 4) * 3 - 1 < i) 
                        if (j > (n / 4) - 1 && j < (n / 4) * 3) {
                            a[(n - i - 1) * n + (n - j - 1)] = i * n + j + 1;
                            continue;
                        }
                    if ((n / 4) > j || (n / 4) * 3 - 1 < j) 
                        if (i > (n / 4) - 1 && i < (n / 4) * 3) {
                            a[(n - i - 1) * n + (n - j - 1)] = i * n + j + 1;
                            continue;
                        }
                    a[i * n + j] = i * n + j + 1;
                }
            }
        }
        if (n % 2 != 0) {
            StepMetod(n, n, 0, 0, a);
        }
        // Вывод магического квадрата
        PrintMagicSquare(a, n);   
        free(a);
    }
    return 0;
}
