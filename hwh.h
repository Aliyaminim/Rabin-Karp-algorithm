#pragma once

unsigned get_hash(const char *pat, const char *end);

unsigned update_hash(unsigned hash, unsigned n, char cf, char cl);

unsigned long long pow_mod(unsigned n, unsigned k, unsigned m);

unsigned cmp(unsigned target, unsigned cur, unsigned left,
             const char *needle, const char *haystack);

long long unsigned rabin_karp(const char *needle, const char *haystack);

char * read_text(int *len);
