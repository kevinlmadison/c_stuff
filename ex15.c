#include <stdio.h>

int main(int argc, char *argv[])
{
    //create two arrays we care about
    int ages[] = { 23, 43};//, 12, 89, 2, 22, 24 };
    char *names[] = {"Alan","Frank"};//,"Mary","John","Lisa","Jack","Kent"};
    //ok so this really is a pointer to a pointer
    //and a pointer is 8 bytes on the system i'm currently using

    //safely get the size of ages
    int count = sizeof(ages)/sizeof(int);
    printf("count: %d \n", count);
    int i = 0;
    
    //first way using indexing
    for (i = 0; i < count; i++){
        printf("%s has %d years alive.\n", names[i], ages[i]);
    }

    printf("---\n");
    //setup pointers to the start of arrays

    int *cur_age = ages;
    char **cur_name = names;
    printf("cur_age: %ld ages: %ld \n", sizeof(cur_age), sizeof(ages));
    printf("cur_name: %ld names: %ld \n", sizeof(cur_name), sizeof(names));
    printf("int: %ld char: %ld \n", sizeof(int), sizeof(char));
    printf("---\n");

    //second way using pointers
    for (i = 0; i < count; i++){
        printf("%s is %d years old.\n", *(cur_name + i),*(cur_age + i));
    }

    printf("---\n");

    //third away, pointers are just arrays 
    for (i = 0; i < count; i++){
        printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
    }
    printf("---\n");

    //fourth way with pointers in a stupid complex way
    for (cur_name = names, cur_age = ages; (cur_age - ages) < count; cur_name++, cur_age++){
        printf("%s lived %d  years so far.\n", *cur_name, *cur_age);
    }

    return 0;
}
