# 셸 정렬 (Shell Sort)

셸 정렬은 삽입 정렬을 개선한 알고리즘이다. 이 알고리즘은 Donald Shell이 1959년에 제안했으며, 큰 간격으로 정렬을 시작하여 점차 간격을 줄여가며 정렬을 수행한다.

## 알고리즘 작동 방식

1. 정렬할 배열의 요소를 일정한 간격(gap)으로 나눈다.
2. 각 간격별로 부분 리스트를 만들어 삽입 정렬을 수행한다.
3. 간격을 줄이면서 2번 과정을 반복한다.
4. 간격이 1이 될 때까지 2-3번 과정을 반복한다.

간격(gap) 시퀀스는 알고리즘의 성능에 큰 영향을 미친다. 일반적으로 사용되는 간격 시퀀스로는 $N/2$, $N/4$, ..., 1 ($N$은 배열의 크기) 또는 커누스의 시퀀스 $(3^k - 1) / 2$ 등이 있다. (이 양반은 TeX를 만든 사람이다)

## 시각화

아래는 셸 정렬의 과정을 보여주는 시각화이다:

```
초기 배열: [8, 9, 1, 7, 2, 3, 5, 4, 6, 0]

간격 5로 시작:
1단계: [3, 0, 1, 4, 2, 8, 5, 9, 6, 7]

간격 3:
2단계: [1, 0, 3, 2, 4, 5, 6, 7, 8, 9]

간격 1 (일반 삽입 정렬):
3단계: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]

최종 정렬된 배열: [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
```

## 시간 복잡도

최악의 경우: 정확한 시간 복잡도는 사용된 간격 시퀀스에 따라 다르다. 일반적으로 O(n^2)이지만, 특정 간격 시퀀스를 사용하면 O(n log^2 n)까지 개선될 수 있다. 정말 최적의 경우에는 O(n log n)까지 개선될 수 있다.

- 비교 횟수는 $O(n^2)$에서 $O(n \log^2 n)$까지 변화한다.
- 교환 횟수는 $O(n \log n)$이다.

평균의 경우: 대부분의 간격 시퀀스에 대해 $O(n^{1.3})$ ~ $O(n^{1.5})$이다.

- 비교 횟수는 $O(n^{1.3})$ ~ $O(n^{1.5})$이다.
- 교환 횟수는 $O(n \log n)$이다.

최선의 경우: 이미 정렬된 배열에 대해 O(n log n)이다.

- 비교 횟수는 $O(n \log n)$이다.
- 교환 횟수는 $O(n)$이다.

## 공간 복잡도

셸 정렬은 추가적인 메모리를 거의 사용하지 않는 제자리 정렬 알고리즘이다. 따라서 공간 복잡도는 O(1)이다.

## 구현 세부

셸 정렬의 핵심은 간격 시퀀스의 선택이다. 다양한 간격 시퀀스가 제안되었으며, 그 중 일부는 다음과 같다:

1. Shell의 원래 시퀀스: $N/2$, $N/4$, ..., 1
2. Knuth의 시퀀스: 1, 4, 13, 40, 121, ... $(3^k - 1) / 2$
3. Sedgewick의 시퀀스: 1, 8, 23, 77, 281, 1073, 4193, 16577, ...

구현 시 이러한 간격 시퀀스 중 하나를 선택하여 사용한다.

## 안정성

셸 정렬은 불안정 정렬이다. 즉, 동일한 값을 가진 요소들의 상대적인 순서가 정렬 과정에서 바뀔 수 있다.

## 장단점

장점:
- 삽입 정렬보다 대체로 빠르다.
- 작은 부분 리스트에 대해 효율적으로 동작한다.
- 제자리 정렬이므로 추가 메모리가 거의 필요 없다.

단점:
- 최적의 간격 시퀀스를 결정하기 어렵다.
- 불안정 정렬이다.
- 매우 큰 데이터셋에 대해서는 다른 $O(n \log n)$ 알고리즘들보다 느릴 수 있다.

## 코드

```c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define ELEMENT_RANGE 1024 * 1024

void shell_sort(int* arr, size_t size) {
    for (int gap = size / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
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
    if (ARRAY_SIZE <= 100) {
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
```