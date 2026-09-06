#include "exec.h"
#include "input.h"

#include "util/string.h"

#include <errno.h>    // to dump error message
#include <stdio.h>    // to print output
#include <stdlib.h>   // for malloc, realloc, free
#include <sys/wait.h> // for waitpid

// Tests strlen on a standard string.
int strlentest1()
{
    char *helloworld = "Hello World!";
    long string_len_hello_world = strlen(helloworld);
    if (string_len_hello_world != 12)
    {
        fprintf(stderr, "String length doesn't match expected: %li ... vs. 12\n", string_len_hello_world);
        return -1;
    }
    fprintf(stdout, "Success for strlentest1!\n");
    return 0;
}

// Tests strlen on a longer string.
int strlentest2()
{
    char *text = "What additional background information could you find to help understand the organization's business/competitors/etc?";
    long string_len_text = strlen(text);
    if (string_len_text != 117)
    {
        fprintf(stderr, "String length doesn't match expected: %li ... vs. 117\n", string_len_text);
        return -1;
    }
    fprintf(stdout, "Success for strlentest2!\n");
    return 0;
}

// Tests strlen on an empty string.
int strlentestempty()
{
    char *empty = "";
    long string_len_empty = strlen(empty);
    if (string_len_empty != 0)
    {
        fprintf(stderr, "String length doesn't match expected: %li ... vs. 0\n", string_len_empty);
        return -1;
    }
    fprintf(stdout, "Success for strlentestempty!\n");
    return 0;
}

// Tests strstr when the substring is not found.
int strstrtest1()
{
    char *haystack = "harveymudd";
    char *needle = "pomona";

    char *result = strstr(haystack, needle);
    if (result != NULL)
    {
        fprintf(stderr, "\"pomona\" is not in the string \"harveymudd\"\n");
        return -1;
    }
    fprintf(stdout, "Success for strstrtest1!\n");
    return 0;
}

// Tests strstr when the substring is at the beginning.
int strstrtest2()
{
    char *haystack = "harveymudd";
    char *needle = "harvey";

    char *result = strstr(haystack, needle);
    if (result != haystack)
    {
        fprintf(stderr, "\"mudd\" is not in the string \"harveymudd\"\n");
        return -1;
    }
    fprintf(stdout, "Success for strstrtest2!\n");
    return 0;
}

// Tests strstr when the needle is longer than the haystack.
int strstrtest3()
{
    char *haystack = "harvey";
    char *needle = "harveymudd";

    char *result = strstr(haystack, needle);
    if (result != NULL)
    {
        fprintf(stderr, "\"harveymudd\" is not in the string \"mudd\"\n");
        return -1;
    }
    fprintf(stdout, "Success for strstrtest3!\n");
    return 0;
}

// Tests strstr when the substring occurs in the middle.
int strstrtest4()
{
    char *haystack = "What additional background information could you find to help understand the organization's business/competitors/etc?";
    char *needle = "hat";

    char *result = strstr(haystack, needle);
    char *reference = haystack + 1;
    if (result != reference)
    {
        fprintf(stderr, "\"info\" is in the reference string. Pointer \"%c\" is not equivalent to \"%c\"", *result, *reference);
        return -1;
    }
    fprintf(stdout, "Success for strstrtest4!\n");
    return 0;
}

// Tests strncmp on two empty strings.
int strncmp1()
{
    char *s1 = "";
    char *s2 = "";
    long n = 1;

    int result = strncmp(s1, s2, n);
    if (result != 0)
    {
        fprintf(stderr, "Strings are both empty.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncmp1!\n");
    return 0;
}

// Tests strncmp on two identical strings.
int strncmp2()
{
    char *s1 = "Harvey";
    char *s2 = "Harvey";
    long n = 6;

    int result = strncmp(s1, s2, n);
    if (result != 0)
    {
        fprintf(stderr, "Strings are the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncmp2!\n");
    return 0;
}

// Tests strncmp when the characters differ.
int strncmp3()
{
    char *s1 = "Harvey";
    char *s2 = "Mudd";
    long n = 6;

    int result = strncmp(s1, s2, n);
    if (result != 'H' - 'M')
    {
        fprintf(stderr, "Strings are not the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncmp3!\n");
    return 0;
}

// Tests strncmp when the first n characters match.
int strncmp4()
{
    char *s1 = "Harvey";
    char *s2 = "Harvard";
    long n = 4;

    int result = strncmp(s1, s2, n);
    if (result != 0)
    {
        fprintf(stderr, "First four characters are the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncmp4!\n");
    return 0;
}

// Tests strncmp when strings differ after n characters.
int strncmp5()
{
    char *s1 = "Harvey";
    char *s2 = "Harvard";
    long n = 7;

    int result = strncmp(s1, s2, n);
    if (result != 'e' - 'a')
    {
        fprintf(stderr, "Strings are not the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncmp5!\n");
    return 0;
}

// Tests strncmp on a longer string with one differing character.
int strncmp6()
{
    char *s1 = "What additional background information could you find to help understand the organization's business/competitors/etc?";
    char *s2 = "What additional background information could you find to hepp understand the organization's business/competitors/etc?";
    long n = 125;

    int result = strncmp(s1, s2, n);
    if (result != 'l' - 'p')
    {
        fprintf(stderr, "Strings are not the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncmp6!\n");
    return 0;
}

// Tests strncmp when one string ends before n characters.
int strncmp7()
{
    char *s1 = "Harvey";
    char *s2 = "HarveyMudd";
    long n = 250;

    int result = strncmp(s1, s2, n);
    if (result != '\0' - 'M')
    {
        fprintf(stderr, "Strings are not the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncmp7!\n");
    return 0;
}

// Tests strncat on two standard strings.
int strncat1()
{
    char dest[100] = "france";
    char src[] = "italy";
    long n = 5;

    char *result = strncat(dest, src, n);
    char *expected = "franceitaly";
    if (strncmp(result, expected, strlen(result)) != 0)
    {
        fprintf(stderr, "Result is %s\n", result);
        fprintf(stderr, "Expected is %s\n", expected);
        fprintf(stderr, "Strings are the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncat1!\n");
    return 0;
}

// Tests strncat on two empty strings.
int strncat2()
{
    char dest[100] = "";
    char src[] = "";
    long n = 5;

    char *result = strncat(dest, src, n);
    char *expected = "";
    if (strncmp(result, expected, strlen(result)) != 0)
    {
        fprintf(stderr, "Result is %s\n", result);
        fprintf(stderr, "Expected is %s\n", expected);
        fprintf(stderr, "Strings are the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncat2!\n");
    return 0;
}

// Tests strncat when n limits the number of characters appended.
int strncat3()
{
    char dest[100] = "harvey"; // make sure to reserve enough space
    char src[] = " mudders";
    long n = 5;

    char *result = strncat(dest, src, n);
    char *expected = "harvey mudd";
    if (strncmp(result, expected, strlen(result)) != 0)
    {
        fprintf(stderr, "Result is %s\n", result);
        fprintf(stderr, "Expected is %s\n", expected);
        fprintf(stderr, "Strings are the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncat3!\n");
    return 0;
}

// Tests strncat when the destination string is empty.
int strncat4()
{
    char dest[100] = ""; // make sure to reserve enough space
    char src[] = " mudders";
    long n = 5;

    char *result = strncat(dest, src, n);
    char *expected = " mudd";
    if (strncmp(result, expected, strlen(result)) != 0)
    {
        fprintf(stderr, "Result is %s\n", result);
        fprintf(stderr, "Expected is %s\n", expected);
        fprintf(stderr, "Strings are the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncat4!\n");
    return 0;
}

// Tests strncat when n is larger than the source string.
int strncat5()
{
    char dest[100] = "france";
    char src[] = "italy";
    long n = 25252525525252525;

    char *result = strncat(dest, src, n);
    char *expected = "franceitaly";
    if (strncmp(result, expected, strlen(result)) != 0)
    {
        fprintf(stderr, "Result is %s\n", result);
        fprintf(stderr, "Expected is %s\n", expected);
        fprintf(stderr, "Strings are the same.\n");
        return -1;
    }
    fprintf(stdout, "Success for strncat5!\n");
    return 0;
}

int main(int argc, char **argv)
{
    strlentest1();
    strlentest2();
    strlentestempty();
    strstrtest1();
    strstrtest2();
    strstrtest3();
    strstrtest4();
    strncmp1();
    strncmp2();
    strncmp3();
    strncmp4();
    strncmp5();
    strncmp6();
    strncmp7();
    strncat1();
    strncat2();
    strncat3();
    strncat4();
    strncat5();
}