#pragma once
#include <stdint.h>
#include <stdbool.h>

//TODO: char* format(char* buf, ...);
/**
 * Calculates the length of a null-terminated string.
 *
 * This function calculates the length of the string pointed to by `str`,
 * excluding the terminating null character ('\0').
 *
 * @param str The null-terminated string to calculate the length of.
 * @return The length of the string.
 */
uint64_t strlen(const char* str);

/**
 * Compares two null-terminated strings.
 *
 * This function compares the string pointed to by `str1` to the string
 * pointed to by `str2`. The comparison is done lexicographically.
 *
 * @param str1 The first null-terminated string to compare.
 * @param str2 The second null-terminated string to compare.
 * @return true if the strings are equal, false otherwise.
 */
bool strcmp(const char* str1, const char* str2);

/**
 * Concatenates the string pointed to by src to the end of the string pointed to by dest.
 *
 * @param dest The destination string where the concatenated string will be stored.
 * @param src The source string to be concatenated.
 * @return A pointer to the resulting string dest.
 */
char* strcat(char* dest, const char* src);