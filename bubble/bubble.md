# 버블 정렬 (Bubble Sort)

버블 정렬은 간단하지만 비효율적인 비교 기반 정렬 알고리즘이다. 이 알고리즘은 인접한 두 원소를 반복적으로 비교하고 필요한 경우 교환하여 정렬을 수행한다.

## 알고리즘 작동 방식

1. 배열의 첫 번째 원소부터 시작하여 인접한 두 원소를 비교한다.
2. 왼쪽 원소가 오른쪽 원소보다 크면 두 원소를 교환한다.
3. 다음 쌍의 인접한 원소로 이동하여 1-2 과정을 반복한다.
4. 배열의 끝에 도달하면 한 번의 패스(pass)가 완료된다.
5. 1-4 과정을 배열이 완전히 정렬될 때까지 반복한다.

## 시각화

아래는 버블 정렬의 과정을 보여주는 시각화이다:

```
초기 배열: [5, 2, 4, 6, 1, 3]

1단계: [2, 5, 4, 6, 1, 3]
2단계: [2, 4, 5, 6, 1, 3]
3단계: [2, 4, 5, 1, 6, 3]
4단계: [2, 4, 5, 1, 3, 6]
5단계: [2, 4, 1, 5, 3, 6]
6단계: [2, 4, 1, 3, 5, 6]
7단계: [2, 1, 4, 3, 5, 6]
8단계: [2, 1, 3, 4, 5, 6]
9단계: [1, 2, 3, 4, 5, 6]

최종 정렬된 배열: [1, 2, 3, 4, 5, 6]
```

## 시간 복잡도

최악의 경우는 배열이 역순으로 정렬되어 있을 때이다. 이 경우, 모든 비교와 교환이 수행되어야 한다. 시간 복잡도는 $O(n^2)$이다.

- 비교 횟수는 $\frac{n(n-1)}{2}$이다.
- 교환 횟수도 $\frac{n(n-1)}{2}$이다.

평균적인 경우도 $O(n^2)$의 시간 복잡도를 가진다.

- 비교 횟수는 $\frac{n(n-1)}{2}$이다.
- 교환 횟수는 $\frac{n(n-1)}{4}$이다.

최선의 경우는 배열이 이미 정렬되어 있을 때이다. 이 경우에도 모든 비교는 수행되지만 교환은 일어나지 않는다. 시간 복잡도는 $O(n)$이다.

- 비교 횟수는 $n-1$이다.
- 교환 횟수는 0이다.

## 공간 복잡도

버블 정렬은 추가적인 메모리 공간을 거의 사용하지 않는 in-place 정렬 알고리즘이다. 따라서 공간 복잡도는 $O(1)$이다.

## 구현 세부

두 개의 중첩된 루프를 사용하여 구현할 수 있다. 외부 루프는 패스의 수를 제어하고, 내부 루프는 각 패스에서의 비교와 교환을 수행한다.

## 안정성

버블 정렬은 안정적인 정렬 알고리즘이다. 동일한 값을 가진 원소들의 상대적인 순서가 정렬 후에도 유지된다.

## 장단점

장점:
- 구현이 매우 간단하다.
- 추가적인 메모리 공간을 거의 사용하지 않는다.
- 안정적인 정렬 알고리즘이다. (왜 안정적일까? 정렬을 할 때, 더 작은 값인 경우만 교환하기 때문이다.)

단점:
- 대부분의 경우에 매우 비효율적이다. 특히 큰 데이터셋에 대해서는 성능이 좋지 않다.
- 시간 복잡도가 $O(n^2)$로, 다른 더 효율적인 정렬 알고리즘들에 비해 느리다.
- 데이터의 이동이 많아 교환 연산이 빈번하게 일어난다.

## 코드

```c++
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100000
#define ELEMENT_RANGE 1024 * 1024

void sort(int* arr, size_t size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 두 원소 교환
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
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