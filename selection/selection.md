# 선택 정렬 (Selection Sort)

선택 정렬은 간단하고 직관적인 정렬 알고리즘이다. 배열을 순회하면서 가장 작은 원소를 선택하여 앞으로 이동시키는 방식으로 동작한다.

## 알고리즘 작동 방식

1. 정렬되지 않은 부분에서 최소값을 찾는다.
2. 찾은 최소값을 정렬되지 않은 부분의 첫 번째 원소와 교환한다.
3. 정렬된 부분을 한 칸 뒤로 늘린다.
4. 배열의 모든 원소가 정렬될 때까지 1-3 과정을 반복한다.

## 시각화

아래는 선택 정렬의 과정을 보여주는 시각화이다:

```
초기 배열: [64, 25, 12, 22, 11]

1단계: [11, 25, 12, 22, 64]  // 11을 선택하여 첫 번째 위치로 이동
2단계: [11, 12, 25, 22, 64]  // 12를 선택하여 두 번째 위치로 이동
3단계: [11, 12, 22, 25, 64]  // 22를 선택하여 세 번째 위치로 이동
4단계: [11, 12, 22, 25, 64]  // 25는 이미 올바른 위치에 있음
5단계: [11, 12, 22, 25, 64]  // 64는 이미 올바른 위치에 있음

최종 정렬된 배열: [11, 12, 22, 25, 64]
```

## 시간 복잡도

최악의 경우, 평균의 경우, 최선의 경우 모두 동일하다. 이는 선택 정렬이 항상 전체 배열을 순회하며 최소값을 찾기 때문이다.

시간 복잡도는 $O(n^2)$이다.

- 비교 횟수는 $\frac{n(n-1)}{2}$이다.
- 교환 횟수는 최대 $n-1$이다.

## 공간 복잡도

선택 정렬은 추가적인 메모리 공간을 거의 사용하지 않는 제자리 정렬 알고리즘이다. 따라서 공간 복잡도는 $O(1)$이다.

## 구현 세부

선택 정렬은 두 개의 중첩된 루프를 사용하여 구현된다. 외부 루프는 정렬되지 않은 부분의 시작 인덱스를 제어하고, 내부 루프는 최소값을 찾는다.

## 안정성

선택 정렬은 불안정 정렬이다. 동일한 값을 가진 원소들의 상대적 순서가 정렬 과정에서 바뀔 수 있다.

## 장단점

장점:
- 구현이 간단하고 이해하기 쉽다.
- 교환 횟수가 적어 데이터 이동이 많지 않다.
- 추가적인 메모리 공간이 필요하지 않다.

단점:
- 시간 복잡도가 $O(n^2)$로 대규모 데이터에 비효율적이다.
- 불안정 정렬이다.
- 입력 데이터의 초기 상태와 관계없이 항상 동일한 수의 비교를 수행한다.

## 코드

```c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define ELEMENT_RANGE 1024 * 1024

void sort(int* arr, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
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

    sort(arr, ARRAY_SIZE);

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