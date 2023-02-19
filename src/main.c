#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hwh.h"

int main()
{
    int num, len_text, len_wordS;
    char *haystack, *needle, *cop_haystack;
    int kol = 0, j, pom;

    scanf("%d", &num);


    haystack = read_text(&len_text);
    needle = read_text(&len_wordS);

    cop_haystack = haystack;

    for (int i = 0; i < num; i++) {
        //выделим слово из needle, с которым будем работать, и обозначим его конец как '\0'
        pom = strlen(needle);
        for (j = 0; j < pom; j++) {
            if (isspace(needle[j]) != 0 || needle[j] == '\0') {
                needle[j] = '\0';
                break;
            }
        }
        //подсчет количества такого слова
        for ( ; ; ) {
            long long int pos = rabin_karp(needle, haystack);
            if (pos == -1)
                break;
            kol++;
            haystack += (pos + j + 1);
        }
        needle += sizeof(char) * (j + 1); //передвигаемся на следующее слово
        printf("%d ", kol);
        kol = 0;
        haystack = cop_haystack; //возвращаем указатель на начало
    }

    printf("\n");

    return 0;
}
