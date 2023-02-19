#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hwh.h"

const unsigned R = 10u;
const unsigned Q = 31u;

unsigned get_hash(const char *pat, const char *end)
{
    unsigned p = 0;
    for (; pat != end; ++pat)
        p = (p * R + *pat) % Q;
    return p;
}

unsigned update_hash(unsigned hash, unsigned n, char cf, char cl)
{
    unsigned nf = (cf * n) % Q;
    if (hash < nf)
        hash += Q;
    hash = ((hash - nf) * R + cl) % Q;
    return hash;
}

unsigned long long pow_mod(unsigned n, unsigned k, unsigned m)
{
    unsigned long long mult, prod;
    if (n == 0 || n == 1 || k == 1)
        return n;
    if (k == 0)
        return 1;
    mult = n;
    prod = 1;
    while (k > 0) {
        if ((k % 2) == 1)
            prod = (prod * mult) % m;
        mult = (mult * mult) % m;
        k = k / 2;
    }
    return prod;
}

unsigned cmp(unsigned target, unsigned cur, unsigned left,
             const char *needle, const char *haystack)
{
    int i, len = strlen(needle);
    if (target != cur)
        return 1;
    for (i = 0; i < len; i++) {
        if (haystack[left + i] != needle[i])
            break;
    }

    if (i == len)
        return 0;
    return 1;

}

long long unsigned rabin_karp(const char *needle, const char *haystack)
{
    long long unsigned n, target, cur, left = 0, right, pom;

    right = strlen(needle);
    pom = strlen(haystack);
    if (pom < right)
        return -1;
    target = get_hash(needle, needle + right);
    cur = get_hash(haystack, haystack + right);
    n = pow_mod(R, right - 1, Q);
    pom = cmp(target, cur, left, needle, haystack);
    while (pom == 1 && haystack[right] != '\0') {
        cur = update_hash(cur, n, haystack[left], haystack[right]);
        left += 1;
        right += 1;
        pom = cmp(target, cur, left, needle, haystack);
    }
    return (target == cur && pom == 0) ? (int) left : -1;
}

char *read_text(int *len)
{
    char *text;
    int n, i;
    int res; 

    res = scanf("%d", len);
    assert(res == 1);

    n = *len;
    assert(n > 0);

    text = (char *) calloc(n + 1, sizeof(char));
    assert(text != NULL);

    res = scanf("%*c");
    (void) res;

    for (i = 0; i < n; ++i) {
        char c;
        res = scanf("%c", &c);
        assert(res == 1);
        text[i] = c;
    }
    text[n] = '\0';

    return text;
}
