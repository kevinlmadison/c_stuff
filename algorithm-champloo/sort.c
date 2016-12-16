#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void merge_sort(int *array, int orig[], int z)
{
    int arr_len = sizeof(array) / sizeof(int);
    if (arr_len < 2) 
        return;
    int mid = arr_len / 2;
    int left[mid], right[mid];
    int i = 0;

    for (i = 0; i < mid; i++) {
        left[i] = array[i];
        right[i] = array[mid + i];
    }
    int left_len = sizeof(left) / sizeof(int);
    int right_len = sizeof(right) / sizeof(int);
    
    merge_sort(left, array, z);
    merge_sort(right, array, z);

    int x, y = 0;
    while (x < left_len && y < right_len) {
        if (left[x] < right[y]) {
            orig[z] = left[x];
            x++;
        } else {
            array[z] = right[y];
            y++;
        }
        z++;
    }
    while (x < left_len) {
        array[z] = left[x];
        x++;
        z++;
    }
    while (y < right_len) {
        array[z] = right[y];
        y++;
        z++;
    }
    return;
}

int main()
{
    int test[] = {4, 6, 1, 9, 2, 3, 5, 4};
    merge_sort(test, test, 0);
    int i = 0;
    for (i = 0; i < 8; i++) {
        printf("%d", test[i]);
    }
    return 0;
}
