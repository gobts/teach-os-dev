#ifndef STRING_H
#define STRING_H

#include <stdbool.h>

int strlen(const char* ptr);

bool isdigit(char c);

int to_numeric_digit(char c);
int strnlen(const char* ptr, int max);

#endif // !STRING_H
