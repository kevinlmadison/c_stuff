#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int left, int mid, int right)
{
    int len_left = mid - left + 1;
    int len_right = right - mid;

    int left_temp[len_left], right_temp[len_right];

    int i, j, k;

    for (i = 0; i < len_left; i++) {
        left_temp[i] = array[left + i];
    }
    for (j = 0; j < len_right; j++) {
        right_temp[j] = array[j + mid + 1];
    }
    i = 0;
    j = 0;
    k = left;

    while (i < len_left && j < len_right) {
        if (left_temp[i] <= right_temp[j]) {
            array[k] = left_temp[i];
            i++;
        } else {
            array[k] = right_temp[j];
            j++;
        }
        k++;
    }
    while (i < len_left) {
        array[k] = left_temp[i];
        i++;
        k++;
    }
    while (j < len_right) {
        array[k] = right_temp[j];
        j++;
        k++;
    }
}

void merge_sort(int array[], int start, int end)
{
    if (start < end) {
        int midpoint = start + (end - start) / 2;
        merge_sort(array, start, midpoint);
        merge_sort(array, midpoint + 1, end);

        merge(array, start, midpoint, end);
    }
}

void print_array(int arr[], int len)
{
    int i = 0;
    for (i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

}

int main()
{
    int test[] = {2, 5, 3, 11, 56, 36, 8, 9};
    int arr_len = sizeof(test) / sizeof(test[0]);
    print_array(test, arr_len);
    merge_sort(test, 0, arr_len - 1);
    printf("now sorted\n");
    print_array(test, arr_len);

    return 0;
}
