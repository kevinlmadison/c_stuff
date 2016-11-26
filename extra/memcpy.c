#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
    int i = 7;
    char chars[4] = {'a','b','c','\0'};
    memcpy(chars, i, 4);
    printf("%d \n", i);
    printf("%s \n", chars);

    return 0;
}
