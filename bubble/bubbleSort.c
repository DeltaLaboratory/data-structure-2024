#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <unistd.h>

#define ARRAY_SIZE 99
#define ELEMENT_RANGE ARRAY_SIZE * 2

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

void visualize_array(int arr[], size_t size, int index1, int index2) {
    // Move cursor to the start of the Array line
    printf("\033[2;1H");

    printf("Array: ");
    for (size_t i = 0; i < size; i++) {
        if (i == index1 || i == index2) {
            printf(ANSI_COLOR_GREEN "%2d " ANSI_COLOR_RESET, arr[i]);
        } else {
            printf("%2d ", arr[i]);
        }
    }

    // Clear the rest of the line
    printf("\033[K");

    // Move cursor to next line
    printf("\n");

    fflush(stdout);
    // usleep(1000); // Sleep for 100ms
}

void bubble_sort(int* arr, size_t size) {
    if (size >= 100) {
        printf("Array size is 100 or larger. Skipping visualization.\n");
        // Perform regular bubble sort without visualization
        int did_swap = 0;
        for (size_t i = 0; i < size - 1; i++) {
            for (size_t j = 0; j < size - i - 1; j++) {
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    did_swap = 1;
                }
            }
            if (!did_swap) {
                break;
            }
            did_swap = 0;
        }
        return;
    }

    // Initial full print
    printf("\033[2J\033[H"); // Clear screen and move cursor to top-left
    visualize_array(arr, size, -1, -1);
    printf("Index: ");
    for (size_t i = 0; i < size; i++) {
        printf("%2zu ", i);
    }
    printf("\n");

    int did_swap = 0;
    for (size_t i = 0; i < size - 1; i++) {
        for (size_t j = 0; j < size - i - 1; j++) {
            visualize_array(arr, size, j, j + 1);

            if (arr[j] > arr[j + 1]) {
                // Swap two elements
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                visualize_array(arr, size, j, j + 1);
                did_swap = 1;
            }
        }

        if (!did_swap) {
            break;
        }

        did_swap = 0;
    }

    // Show final sorted array
    visualize_array(arr, size, -1, -1);
    printf("Sorting complete.\n");
}

// 배열이 정렬되어 있는지 확인
int is_sorted(int* arr, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        visualize_array(arr, size, i, i + 1);
        if (arr[i] > arr[i + 1]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int *arr = malloc(sizeof(int) * ARRAY_SIZE);

    srand(time(NULL));

    for (int i = 0; i < ARRAY_SIZE; i++) {
        arr[i] = rand() % ELEMENT_RANGE;
    }

    printf("Before sorting: ");
    if (ARRAY_SIZE <= 100) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Too many elements to print");
    }
    printf("\n");

    bubble_sort(arr, ARRAY_SIZE);

    printf("After sorting: ");
    if (ARRAY_SIZE <= 100) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Too many elements to print");
    }
    printf("\n");

    if (is_sorted(arr, ARRAY_SIZE)) {
        printf("Sorting is successful\n");
    } else {
        printf("Sorting is failed\n");
    }

    free(arr);
    return 0;
}