#include "exec.h"
#include "input.h"

#include "util/string.h"

#include <errno.h>    // to dump error message
#include <stdio.h>    // to print output
#include <stdlib.h>   // for malloc, realloc, free
#include <sys/wait.h> // for waitpid

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

int strncat1()
{
    char *dest = malloc(20 * sizeof(char));
    dest = "";
    char *src = "";
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
    fprintf(stdout, "Success for strncat1!\n");
    free(dest);
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
    strncat1();
}