#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DISPLAY_LIMIT 1000

#define ARRAY_SIZE 250
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

void shell_sort(int* arr, size_t size) {
    if (size >= DISPLAY_LIMIT) {
        printf("Array size is 100 or larger. Skipping visualization.\n");
        // Perform regular shell sort without visualization
        for (int gap = size / 2; gap > 0; gap /= 2) {
            if (gap % 2 == 0) gap++;
            for (int i = gap; i < size; i++) {
                int temp = arr[i];
                int j;
                for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                    arr[j] = arr[j - gap];
                }
                arr[j] = temp;
            }
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

    for (int gap = size / 2; gap > 0; gap /= 2) {
        // Display current gap
        printf("\033[20;1H"); // Move cursor to the 5th line
        printf("Current gap: %d   \n", gap);

        for (int i = gap; i < size; i++) {
            // Display cycle index
            printf("\033[21;1H"); // Move cursor to the 6th line
            printf("Current cycle index: %d   \n", i);

            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                visualize_array(arr, size, j, j - gap);
                arr[j] = arr[j - gap];
                visualize_array(arr, size, j, j - gap);
            }
            arr[j] = temp;
            visualize_array(arr, size, j, i);
        }
    }

    // Show final sorted array
    visualize_array(arr, size, -1, -1);
    printf("Sorting complete.\n");
}

// 배열이 정렬되어 있는지 확인
int is_sorted(int* arr, size_t size) {
    for (int i = 0; i < size - 1; i++) {
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
    if (ARRAY_SIZE <= DISPLAY_LIMIT) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } else {
        printf("Too many elements to print");
    }
    printf("\n");

    shell_sort(arr, ARRAY_SIZE);

    printf("After sorting: ");
    if (ARRAY_SIZE <= DISPLAY_LIMIT) {
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