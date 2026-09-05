#include "util/string.h"

#include <stddef.h> // for NULL
#include <errno.h>  // to dump error message
#include <stdio.h>  // to print output

/*
 * @brief Returns length of string
 *
 * @param[in] *str The input string
 * @param[out] strlen The length of the string
 */
long strlen(const char *str)
{
    long len = 0;

    while (*(str + len) != '\0')
    {
        len++;
    }

    return len;
}

/*
 * @brief Returns a pointer to the first index of a substring within another string
 *
 * @param[in] *haystack The given string
 * @param[in] *needle The specified substring
 * @param[out] *strstr The pointer to the first index of the substring in the string
 */
char *strstr(const char *haystack, const char *needle)
{
    // Check if substring is longer than string
    long needle_len = strlen(needle);
    long haystack_len = strlen(haystack);
    if (needle_len > haystack_len)
    {
        return NULL;
    }
    for (long i = 0; i <= haystack_len - needle_len; ++i)
    {
        long j = 0;
        while (j < needle_len)
        {
            if (*(needle + j) != *(haystack + i + j))
            {
                break;
            }
            ++j;
        }
        // Check if the whole substring was found in the string
        if (j == needle_len)
        {
            return haystack + i;
        }
    }
    return NULL;
}

/*
 * @brief concatenate one string to another
 *
 * @param[in] *dest The destination string.
 * @param[in] *src The source string.
 * @param[in] n The number of characters to copy.
 */
char *strncat(char *dest, const char *src, long n)
{
    // compare length of src to n
    long srclen = strlen(src);
    if (n > srclen)
    {
        n = srclen;
    }

    long destlen = strlen(dest);
    long i = 0;
    while (i < n)
    {
        *(dest + destlen + i) = *(src + i);
        ++i;
    }
    *(dest + destlen + n) = '\0';
    return dest;
}

/*
 * @brief Compares the first n characters of two string; returns an integer indicating which one is greater
 *
 * @param[in] *s1 The first input string
 * @param[in] *s2 The second input string
 * @param[in] n  The max number of characters to check
 * @param[out] strncmp Integer value which is positive if first string is greater, negative if second string is greater, and 0 if the two strings are equal
 */
int strncmp(const char *s1, const char *s2, long n)
{
    // Check string lengths to avoid long while loops due to large n
    long strlen1 = strlen(s1);
    long strlen2 = strlen(s2);
    if (strlen1 < n)
    {
        n = strlen1;
    }
    if (strlen2 < n)
    {
        n = strlen2;
    }

    int cmp = 0;
    long i = 0;
    while (i < n)
    {
        cmp = *(s1 + i) - *(s2 + i);
        if (cmp != 0)
        {
            return cmp;
        }
        i++;
    }
    return 0;
}
