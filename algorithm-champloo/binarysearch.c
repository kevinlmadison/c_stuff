#include <stdio.h>
#include <stdlib.h>

int bin(int *list, int l, int h, int k, int m) {
    if(k < list[m]){
        bin(list, l, m, k, (h + l)/2);
    } else if (k > list[m]) {
        bin(list, m + 1, h, k, (h + l)/2);
    }
   return m;
}

void print_array(int *arr, int len)
{
    int i = 0;
    for (i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int num;
    int list[] = {2, 3, 4, 5, 6, 12, 23, 45, 47, 56, 66};
    int arr_len = sizeof(list)/sizeof(list[0]);
    print_array(list, arr_len);
    printf("Enter a number:  ");
    scanf("%d", &num);
    int idx = bin(list, 0, arr_len - 1, num, arr_len/2);
    printf("%d ", idx);
    return 0;
}
